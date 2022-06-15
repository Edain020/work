//------------------------------------------
//								   enemy.cpp
//�@�����:AT11B192 No.17 ������G
//�X�V�����`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
//2020/02/28
// �v���O��������J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
//===== �C���N���[�h�� =====
#include "bitmap.h"
#include "buffer.h"
#include "enemy.h"
#include "unit.h"
#include "field.h"
#include "main.h"
#include "player.h"
#include "battle.h"

//===== �萔�E�}�N����` =====
#define ENEMY_UNIT1_FILE	("bmp/Enemy.bmp")	// �G�L�����̉摜�̃t�@�C����
#define ENEMY_ANIME_FLAME	(3)					// �G���j�b�g�̃A�j���̃R�}��
#define ENEMY_SPAWN_WIDTH	(10)				// �G���j�b�g�̃X�|�[���͈�(��)
#define ENEMY_SPAWN_HEIGHT	(5)					// �G���j�b�g�̃X�|�[���͈�(�c)
#define ENEMY_SPAWN_POS_X	((FIELD_WIDTH - ENEMY_SPAWN_WIDTH) / 2)	// �v���C���[���j�b�g�̃X�|�[���ʒu��X���W(����)
#define ENEMY_SPAWN_POS_Y	(FIELD_HEIGHT - ENEMY_SPAWN_HEIGHT - 1)	// �v���C���[���j�b�g�̃X�|�[���ʒu��Y���W(����)
#define ENEMY_MOVE_DELAY	(10)					// �G���j�b�g�̈ړ��̊Ԋu(�t���[����)

//===== �v���g�^�C�v�錾 =====
void SetEnemySpawnPos(UNIT*);
void ResetEnemyAction(void);

//===== �O���[�o���ϐ� =====
BUFFER g_EnemyBuffer;
UNIT g_aEnemyUnit[MAX_ENEMY_UNIT_NUM];
IMAGE *g_paEnemyImage[DIRECTION_MAX][ENEMY_ANIME_FLAME];
int g_naMoveScore[FIELD_HEIGHT][FIELD_WIDTH];
int g_nEnemyActionCnt;
bool g_bAction;


void InitEnemy(void)
{
	//===== �ϐ��錾 =====
	int i, j;
	UNIT *pUnit;
	IMAGE **pImage;

	char szaPlayerUnitAnime[DIRECTION_MAX][ENEMY_ANIME_FLAME][MAX_FILE_NAME] =
	{
	  { { "bmp/�c�o��/�c�o��.bmp" }      , { "bmp/�c�o��/�c�o��1.bmp" }      , { "bmp/�c�o��/�c�o��2.bmp" }		  },
	  { { "bmp/�c�o��/�c�o��.bmp" }      , { "bmp/�c�o��/�c�o��1.bmp" }      , { "bmp/�c�o��/�c�o��2.bmp" }       },
	  { { "bmp/�c�o��/�c�o���o�b�N.bmp" }, { "bmp/�c�o��/�c�o���o�b�N1.bmp" }, { "bmp/�c�o��/�c�o���o�b�N2.bmp" } },
	  { { "bmp/�c�o��/�c�o�����t�g.bmp" }, { "bmp/�c�o��/�c�o�����t�g1.bmp" }, { "bmp/�c�o��/�c�o�����t�g2.bmp" } },
	  { { "bmp/�c�o��/�c�o�����C�g.bmp" }, { "bmp/�c�o��/�c�o�����C�g1.bmp" }, { "bmp/�c�o��/�c�o�����C�g2.bmp" } },
	};// �c�o��

	//===== ���������� =====
	InitBuffer(&g_EnemyBuffer);
	pImage = &g_paEnemyImage[0][0];
	for (i = 0; i < DIRECTION_MAX; i++)
		for (j = 0; j < ENEMY_ANIME_FLAME; j++, pImage++)
			*pImage = Read_Bmp(szaPlayerUnitAnime[i][j], TILE_SIZE, TILE_SIZE * 2);

	InitUnit(&g_aEnemyUnit[0], "����A", JOB_SWORDMAN);
	InitUnit(&g_aEnemyUnit[1], "����B", JOB_SPEARMAN);
	InitUnit(&g_aEnemyUnit[2], "����C", JOB_SPEARMAN);
	InitUnit(&g_aEnemyUnit[3], "����D", JOB_BOWMAN);
	InitUnit(&g_aEnemyUnit[4], "����E", JOB_BOWMAN);
	for (i = 0, pUnit = g_aEnemyUnit; i < MAX_ENEMY_UNIT_NUM; i++, pUnit++)
	{
		pUnit->Team = TEAM_ENEMY;
		pUnit->Dir = DIRECTION_UP;
		SetEnemySpawnPos(pUnit);
		pUnit->pImage = g_paEnemyImage[pUnit->Dir][0];
	}
	g_nEnemyActionCnt = ENEMY_MOVE_DELAY;
	g_bAction = false;

	for (i = 0; i < FIELD_HEIGHT; i++)
	{
		for (j = 0; j < FIELD_WIDTH; j++)
		{
			g_naMoveScore[i][j] = 0;
		}
	}
}
void UpdateEnemy(void)
{
	//===== �ϐ��錾 =====
	int i, j, x, y;
	int nDisX, nDisY;
	int nMinScore;
	UNIT *pUnit;
	UNIT *pPlayer;
	FIELD *pField;

	//===== ���������� =====
	g_bAction = false;
	nMinScore = 99999;

	for (y = 0, pField = GetField(); y < FIELD_HEIGHT; y++)
	{
		for (x = 0; x < FIELD_WIDTH; x++, pField++)
		{
			g_naMoveScore[y][x] = 0;
		}
	}

	//===== �X�V���� =====
	for (i = 0, pUnit = g_aEnemyUnit; i < MAX_ENEMY_UNIT_NUM; i++, pUnit++)
	{
		if (!pUnit->bExist)	continue;

		// �A�j���[�V�����X�V
		pUnit->nAnimeCnt++;
		if (pUnit->nAnimeCnt > UNIT_ANIME_DELAY)
		{
			pUnit->nAnimeNum = (pUnit->nAnimeNum + 1) % (ENEMY_ANIME_FLAME);
			pUnit->pImage = g_paEnemyImage[pUnit->Dir][pUnit->nAnimeNum];
			pUnit->nAnimeCnt = 0;
		}

		//----- �G�̓��� -----
		if (GetMODE() != MODE_ENEMY)		continue;	// �G�l�~�[�^�[������Ȃ��Ȃ��O����
		if (g_bAction || pUnit->bAction)	continue;	// �s���ς݂Ȃ��O����
		g_bAction = true;
		g_nEnemyActionCnt--;
		if (g_nEnemyActionCnt > 0)			continue;	// ��莞�Ԍo�߂��Ă��Ȃ���Ζ�O����

		CheckEnemyUnitMove(pUnit->Job.nMove, pUnit->nPosX, pUnit->nPosY);

		for (y = 0, pField = GetField(); y < FIELD_HEIGHT; y++)
		{
			for (x = 0; x < FIELD_WIDTH; x++, pField++)
			{
				if (!pField->bPass) continue;	// �ʍs�s�Ȃ��O����

				for (j = 0, pPlayer = GetPlayerUnit(); j < MAX_PLAYER_UNIT_NUM; j++, pPlayer++)
				{
					if (!pPlayer->bExist) continue;	// ���݂��Ȃ��Ȃ��O����

					nDisX = x - pPlayer->nPosX;
					nDisY = y - pPlayer->nPosY;

					if (nDisX < 0)	nDisX = -nDisX;
					if (nDisY < 0)	nDisY = -nDisY;

					g_naMoveScore[y][x] += nDisX + nDisY;
				}
			}
		}

		for (y = 0, pField = GetField(); y < FIELD_HEIGHT; y++)
		{
			for (x = 0; x < FIELD_WIDTH; x++, pField++)
			{
				if (!pField->bPass) continue;	// �ʍs�s�Ȃ��O����

				if (nMinScore > g_naMoveScore[y][x])
				{
					nMinScore = g_naMoveScore[y][x];
					pUnit->nNextPosX = x;
					pUnit->nNextPosY = y;
				}
			}
		}
		GetFieldxy(pUnit->nPosX, pUnit->nPosY)->UnitType = FIELD_UNIT_NONE;
		GetFieldxy(pUnit->nNextPosX, pUnit->nNextPosY)->UnitType = FIELD_UNIT_ENEMY;
		pUnit->nPosX = pUnit->nNextPosX;
		pUnit->nPosY = pUnit->nNextPosY;
		Battle(pUnit);
		pUnit->bAction = true;
		ResetPass();
		g_nEnemyActionCnt = ENEMY_MOVE_DELAY;
		SetFieldBuffer(pUnit->nPosX - FIELD_BUFFER_WIDTH / 2, pUnit->nPosY - FIELD_BUFFER_HEIGHT / 2);
	}

	if (GetMODE() == MODE_ENEMY && !g_bAction)
	{
		SetMODE(MODE_PLAYER);
		SetFieldBuffer(GetPlayerUnit()->nPosX - FIELD_BUFFER_WIDTH / 2, GetPlayerUnit()->nPosY - FIELD_BUFFER_HEIGHT / 2);
		ResetPlayerAction();
		ResetEnemyAction();
		for (i = 0, pUnit = GetPlayerUnit(); i < MAX_PLAYER_UNIT_NUM; i++, pUnit++)
			if (pUnit->bExist)	return;
		SetMODE(MODE_GAMEOVER);
	}
}

void DrawEnemy(void)
{
	//===== �ϐ��錾 =====
	int i, x, y, bufx, bufy;
	UNIT *pUnit;
	
	//===== ���������� =====
	bufx = GetFieldBufferX();
	bufy = GetFieldBufferY();

	//===== �`�揈�� =====
	for (y = 0; y < FIELD_BUFFER_HEIGHT; y++)
	{
		for (x = 0; x < FIELD_BUFFER_WIDTH; x++, pUnit++)
		{
			for (i = 0, pUnit = g_aEnemyUnit; i < MAX_ENEMY_UNIT_NUM; i++, pUnit++)
			{
				if (pUnit->nPosY != bufy + y || pUnit->nPosX != bufx + x || !pUnit->bExist) continue;

				UpdateBuffer(&g_EnemyBuffer, pUnit->pImage, x * TILE_SIZE * 2, y * TILE_SIZE);
			}
		}
	}

	CombineBuffer(&g_EnemyBuffer);
}

void EndEnemy(void)
{

}

void SetEnemySpawnPos(UNIT *pUnit)
{
	//===== �X�V���� =====
	do
	{
		pUnit->nPosX = rand() % ENEMY_SPAWN_WIDTH  + ENEMY_SPAWN_POS_X;
		pUnit->nPosY = rand() % ENEMY_SPAWN_HEIGHT + ENEMY_SPAWN_POS_Y;
	} while (GetFieldxy(pUnit->nPosX, pUnit->nPosY)->UnitType != FIELD_UNIT_NONE);
	GetFieldxy(pUnit->nPosX, pUnit->nPosY)->UnitType = FIELD_UNIT_ENEMY;
}

UNIT* GetEnemyUnit(void)
{
	return g_aEnemyUnit;
}

void ResetEnemyAction(void)
{
	//===== �ϐ��錾 =====
	int i;
	UNIT *pUnit;

	//===== �X�V���� =====
	for (i = 0, pUnit = g_aEnemyUnit; i < MAX_PLAYER_UNIT_NUM; i++, pUnit++)
	{
		pUnit->bAction = false;
	}
}
