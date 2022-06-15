//------------------------------------------
//								  player.cpp
//�@�����:AT11B192 No.17 ������G
//�X�V�����`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
//2020/02/28
// �v���O��������J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
//===== �C���N���[�h�� =====
#define CONIOEX
#include "conioex.h"
#include "bitmap.h"
#include "buffer.h"
#include "player.h"
#include "unit.h"
#include "field.h"
#include "main.h"

//===== �萔�E�}�N����` =====
#define PLAYER_ANIME_FLAME	(3)					// �v���C���[�̃A�j���̃R�}��
#define PLAYER_SPAWN_WIDTH	(10)				// �v���C���[���j�b�g�̃X�|�[���͈�(��)
#define PLAYER_SPAWN_HEIGHT	(5)					// �v���C���[���j�b�g�̃X�|�[���͈�(�c)
#define PLAYER_SPAWN_POS_X	((FIELD_WIDTH - PLAYER_SPAWN_WIDTH) / 2)	// �v���C���[���j�b�g�̃X�|�[���ʒu��X���W(����)
#define PLAYER_SPAWN_POS_Y	(0)					// �v���C���[���j�b�g�̃X�|�[���ʒu��Y���W(����)

//===== �v���g�^�C�v�錾 =====
void SetPlayerSpawnPos(UNIT*);

//===== �O���[�o���ϐ� =====
BUFFER g_PlayerBuffer;
UNIT g_aPlayerUnit[MAX_PLAYER_UNIT_NUM];
IMAGE *g_paPlayerImage[JOB_MAX][DIRECTION_MAX][PLAYER_ANIME_FLAME];

int g_nPlayerActionCnt;

void InitPlayer(void)
{
	//===== �ϐ��錾 =====
	int i, j, k;
	UNIT *pUnit;
	IMAGE **pImage;

	char szaPlayerUnitAnime[JOB_MAX][DIRECTION_MAX][PLAYER_ANIME_FLAME][MAX_FILE_NAME] =
	{
	  { { { "bmp/�u�V�h�[/�u�V�h�[.bmp" }	     , { "bmp/�u�V�h�[/�u�V�h�[1.bmp" }	       , { "bmp/�u�V�h�[/�u�V�h�[2.bmp" }         },
		{ { "bmp/�u�V�h�[/�u�V�h�[�o�b�N.bmp" }  , { "bmp/�u�V�h�[/�u�V�h�[�o�b�N1.bmp" }  , { "bmp/�u�V�h�[/�u�V�h�[�o�b�N2.bmp" }   },
		{ { "bmp/�u�V�h�[/�u�V�h�[�t�����g.bmp" }, { "bmp/�u�V�h�[/�u�V�h�[�t�����g1.bmp" }, { "bmp/�u�V�h�[/�u�V�h�[�t�����g2.bmp" } },
		{ { "bmp/�u�V�h�[/�u�V�h�[���t�g.bmp" }  , { "bmp/�u�V�h�[/�u�V�h�[���t�g1.bmp" }  , { "bmp/�u�V�h�[/�u�V�h�[���t�g2.bmp" }   },
		{ { "bmp/�u�V�h�[/�u�V�h�[���C�g.bmp" }  , { "bmp/�u�V�h�[/�u�V�h�[���C�g1.bmp" }  , { "bmp/�u�V�h�[/�u�V�h�[���C�g2.bmp" }   }
	  },// SWORDMAN
		{ { { "bmp/�u�V�h�[/�u�V�h�[.bmp" }	     , { "bmp/�u�V�h�[/�u�V�h�[1.bmp" }	       , { "bmp/�u�V�h�[/�u�V�h�[2.bmp" }         },
		{ { "bmp/�u�V�h�[/�u�V�h�[�o�b�N.bmp" }  , { "bmp/�u�V�h�[/�u�V�h�[�o�b�N1.bmp" }  , { "bmp/�u�V�h�[/�u�V�h�[�o�b�N2.bmp" }   },
		{ { "bmp/�u�V�h�[/�u�V�h�[�t�����g.bmp" }, { "bmp/�u�V�h�[/�u�V�h�[�t�����g1.bmp" }, { "bmp/�u�V�h�[/�u�V�h�[�t�����g2.bmp" } },
		{ { "bmp/�u�V�h�[/�u�V�h�[���t�g.bmp" }  , { "bmp/�u�V�h�[/�u�V�h�[���t�g1.bmp" }  , { "bmp/�u�V�h�[/�u�V�h�[���t�g2.bmp" }   },
		{ { "bmp/�u�V�h�[/�u�V�h�[���C�g.bmp" }  , { "bmp/�u�V�h�[/�u�V�h�[���C�g1.bmp" }  , { "bmp/�u�V�h�[/�u�V�h�[���C�g2.bmp" }   }
	  },// SPEARMAN
	{ { { "bmp/�u�V�h�[/�u�V�h�[.bmp" }	         , { "bmp/�u�V�h�[/�u�V�h�[1.bmp" }	       , { "bmp/�u�V�h�[/�u�V�h�[2.bmp" }         },
		{ { "bmp/�u�V�h�[/�u�V�h�[�o�b�N.bmp" }  , { "bmp/�u�V�h�[/�u�V�h�[�o�b�N1.bmp" }  , { "bmp/�u�V�h�[/�u�V�h�[�o�b�N2.bmp" }   },
		{ { "bmp/�u�V�h�[/�u�V�h�[�t�����g.bmp" }, { "bmp/�u�V�h�[/�u�V�h�[�t�����g1.bmp" }, { "bmp/�u�V�h�[/�u�V�h�[�t�����g2.bmp" } },
		{ { "bmp/�u�V�h�[/�u�V�h�[���t�g.bmp" }  , { "bmp/�u�V�h�[/�u�V�h�[���t�g1.bmp" }  , { "bmp/�u�V�h�[/�u�V�h�[���t�g2.bmp" }   },
		{ { "bmp/�u�V�h�[/�u�V�h�[���C�g.bmp" }  , { "bmp/�u�V�h�[/�u�V�h�[���C�g1.bmp" }  , { "bmp/�u�V�h�[/�u�V�h�[���C�g2.bmp" }   }
	  },// BOWMAN
	};

	//===== ���������� =====
	InitBuffer(&g_PlayerBuffer);
	pImage = &g_paPlayerImage[0][0][0];
	for (i = 0; i < JOB_MAX; i++)
		for (j = 0; j < DIRECTION_MAX; j++)
			for (k = 0; k < PLAYER_ANIME_FLAME; k++, pImage++)
				*pImage = Read_Bmp(szaPlayerUnitAnime[i][j][k], TILE_SIZE, TILE_SIZE * 2);

	g_nPlayerActionCnt = 0;
	InitUnit(&g_aPlayerUnit[0], "������" , JOB_SWORDMAN);
	InitUnit(&g_aPlayerUnit[1], "�ւ���A", JOB_SPEARMAN);
	InitUnit(&g_aPlayerUnit[2], "�ւ���B", JOB_SPEARMAN);
	InitUnit(&g_aPlayerUnit[3], "�ւ���C", JOB_BOWMAN);
	InitUnit(&g_aPlayerUnit[4], "�ւ���D", JOB_BOWMAN);
	for (i = 0, pUnit = g_aPlayerUnit; i < MAX_PLAYER_UNIT_NUM; i++, pUnit++)
	{
		pUnit->Team = TEAM_PLAYER;
		pUnit->Dir = DIRECTION_NONE;
		SetPlayerSpawnPos(pUnit);
		pUnit->pImage = g_paPlayerImage[pUnit->Job.Job][pUnit->Dir][pUnit->nAnimeNum];
	}
}

void UpdatePlayer(void)
{
	//===== �ϐ��錾 =====
	int i, x, y, bufx, bufy;
	UNIT *pUnit;

	//===== ���������� =====
	bufx = GetFieldBufferX();
	bufy = GetFieldBufferY();

	//===== �X�V���� =====
	if (g_nPlayerActionCnt == MAX_PLAYER_UNIT_NUM)
	{
		SetMODE(MODE_ENEMY);
	}

	for (i = 0, pUnit = g_aPlayerUnit; i < MAX_PLAYER_UNIT_NUM; i++, pUnit++)
	{
		if (!pUnit->bExist)	continue;	// ���݂��Ȃ���Ζ�O����
		
		if (!pUnit->bAction)	pUnit->nAnimeCnt++;	// �s���ς݂Ȃ�A�j���[�V����OFF

		if (pUnit->nAnimeCnt > UNIT_ANIME_DELAY) // �A�j���[�V�����X�V
		{
			pUnit->nAnimeNum = (pUnit->nAnimeNum + 1) % (PLAYER_ANIME_FLAME);
			pUnit->pImage = g_paPlayerImage[pUnit->Job.Job][pUnit->Dir][pUnit->nAnimeNum];
			pUnit->nAnimeCnt = 0;
		}
		
		for (y = 0; y < FIELD_BUFFER_HEIGHT; y++)
		{
			for (x = 0; x < FIELD_BUFFER_WIDTH; x++)
			{
				if (pUnit->nPosY != bufy + y || pUnit->nPosX != bufx + x) continue;	// ��ʓ��Ƀ��j�b�g�����Ȃ���Ζ�O����

				UpdateBuffer(&g_PlayerBuffer, pUnit->pImage, x * TILE_SIZE * 2, y * TILE_SIZE);
			}
		}

	}
}

void DrawPlayer(void)
{
	CombineBuffer(&g_PlayerBuffer);
}

void EndPlayer(void)
{

}

void SetPlayerSpawnPos(UNIT *pUnit)
{
	//===== �X�V���� =====
	do
	{
		pUnit->nNextPosX = pUnit->nPosX = rand() % PLAYER_SPAWN_WIDTH + PLAYER_SPAWN_POS_X;
		pUnit->nNextPosY = pUnit->nPosY = rand() % PLAYER_SPAWN_HEIGHT + PLAYER_SPAWN_POS_Y;
	} while (GetTerrainInfo(pUnit->nPosX, pUnit->nPosY)->nPassCost == (-1) || GetFieldxy(pUnit->nPosX, pUnit->nPosY)->UnitType != FIELD_UNIT_NONE);
	GetFieldxy(pUnit->nPosX, pUnit->nPosY)->UnitType = FIELD_UNIT_PLAYER;
}

void ResetPlayerAction(void)
{
	//===== �ϐ��錾 =====
	int i;
	UNIT *pUnit;

	//===== �X�V���� =====
	for (i = 0, pUnit = g_aPlayerUnit; i < MAX_PLAYER_UNIT_NUM; i++, pUnit++)
	{
		pUnit->bAction = false;
	}
	g_nPlayerActionCnt = 0;
}

UNIT* GetPlayerUnit(void)
{
	return g_aPlayerUnit;
}

void AddActionCnt(void)
{
	g_nPlayerActionCnt++;
}