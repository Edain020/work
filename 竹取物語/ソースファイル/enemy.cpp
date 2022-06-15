//------------------------------------------
//								   enemy.cpp
//　制作者:AT11B192 No.17 小畠大季
//更新履歴～～～～～～～～～～～～～～～～～
//2020/02/28
// プログラム制作開始
//～～～～～～～～～～～～～～～～～～～～～
//===== インクルード部 =====
#include "bitmap.h"
#include "buffer.h"
#include "enemy.h"
#include "unit.h"
#include "field.h"
#include "main.h"
#include "player.h"
#include "battle.h"

//===== 定数・マクロ定義 =====
#define ENEMY_UNIT1_FILE	("bmp/Enemy.bmp")	// 敵キャラの画像のファイル名
#define ENEMY_ANIME_FLAME	(3)					// 敵ユニットのアニメのコマ数
#define ENEMY_SPAWN_WIDTH	(10)				// 敵ユニットのスポーン範囲(横)
#define ENEMY_SPAWN_HEIGHT	(5)					// 敵ユニットのスポーン範囲(縦)
#define ENEMY_SPAWN_POS_X	((FIELD_WIDTH - ENEMY_SPAWN_WIDTH) / 2)	// プレイヤーユニットのスポーン位置のX座標(左上)
#define ENEMY_SPAWN_POS_Y	(FIELD_HEIGHT - ENEMY_SPAWN_HEIGHT - 1)	// プレイヤーユニットのスポーン位置のY座標(左上)
#define ENEMY_MOVE_DELAY	(10)					// 敵ユニットの移動の間隔(フレーム数)

//===== プロトタイプ宣言 =====
void SetEnemySpawnPos(UNIT*);
void ResetEnemyAction(void);

//===== グローバル変数 =====
BUFFER g_EnemyBuffer;
UNIT g_aEnemyUnit[MAX_ENEMY_UNIT_NUM];
IMAGE *g_paEnemyImage[DIRECTION_MAX][ENEMY_ANIME_FLAME];
int g_naMoveScore[FIELD_HEIGHT][FIELD_WIDTH];
int g_nEnemyActionCnt;
bool g_bAction;


void InitEnemy(void)
{
	//===== 変数宣言 =====
	int i, j;
	UNIT *pUnit;
	IMAGE **pImage;

	char szaPlayerUnitAnime[DIRECTION_MAX][ENEMY_ANIME_FLAME][MAX_FILE_NAME] =
	{
	  { { "bmp/ツバメ/ツバメ.bmp" }      , { "bmp/ツバメ/ツバメ1.bmp" }      , { "bmp/ツバメ/ツバメ2.bmp" }		  },
	  { { "bmp/ツバメ/ツバメ.bmp" }      , { "bmp/ツバメ/ツバメ1.bmp" }      , { "bmp/ツバメ/ツバメ2.bmp" }       },
	  { { "bmp/ツバメ/ツバメバック.bmp" }, { "bmp/ツバメ/ツバメバック1.bmp" }, { "bmp/ツバメ/ツバメバック2.bmp" } },
	  { { "bmp/ツバメ/ツバメレフト.bmp" }, { "bmp/ツバメ/ツバメレフト1.bmp" }, { "bmp/ツバメ/ツバメレフト2.bmp" } },
	  { { "bmp/ツバメ/ツバメライト.bmp" }, { "bmp/ツバメ/ツバメライト1.bmp" }, { "bmp/ツバメ/ツバメライト2.bmp" } },
	};// ツバメ

	//===== 初期化処理 =====
	InitBuffer(&g_EnemyBuffer);
	pImage = &g_paEnemyImage[0][0];
	for (i = 0; i < DIRECTION_MAX; i++)
		for (j = 0; j < ENEMY_ANIME_FLAME; j++, pImage++)
			*pImage = Read_Bmp(szaPlayerUnitAnime[i][j], TILE_SIZE, TILE_SIZE * 2);

	InitUnit(&g_aEnemyUnit[0], "ざこA", JOB_SWORDMAN);
	InitUnit(&g_aEnemyUnit[1], "ざこB", JOB_SPEARMAN);
	InitUnit(&g_aEnemyUnit[2], "ざこC", JOB_SPEARMAN);
	InitUnit(&g_aEnemyUnit[3], "ざこD", JOB_BOWMAN);
	InitUnit(&g_aEnemyUnit[4], "ざこE", JOB_BOWMAN);
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
	//===== 変数宣言 =====
	int i, j, x, y;
	int nDisX, nDisY;
	int nMinScore;
	UNIT *pUnit;
	UNIT *pPlayer;
	FIELD *pField;

	//===== 初期化処理 =====
	g_bAction = false;
	nMinScore = 99999;

	for (y = 0, pField = GetField(); y < FIELD_HEIGHT; y++)
	{
		for (x = 0; x < FIELD_WIDTH; x++, pField++)
		{
			g_naMoveScore[y][x] = 0;
		}
	}

	//===== 更新処理 =====
	for (i = 0, pUnit = g_aEnemyUnit; i < MAX_ENEMY_UNIT_NUM; i++, pUnit++)
	{
		if (!pUnit->bExist)	continue;

		// アニメーション更新
		pUnit->nAnimeCnt++;
		if (pUnit->nAnimeCnt > UNIT_ANIME_DELAY)
		{
			pUnit->nAnimeNum = (pUnit->nAnimeNum + 1) % (ENEMY_ANIME_FLAME);
			pUnit->pImage = g_paEnemyImage[pUnit->Dir][pUnit->nAnimeNum];
			pUnit->nAnimeCnt = 0;
		}

		//----- 敵の動き -----
		if (GetMODE() != MODE_ENEMY)		continue;	// エネミーターンじゃないなら門前払い
		if (g_bAction || pUnit->bAction)	continue;	// 行動済みなら門前払い
		g_bAction = true;
		g_nEnemyActionCnt--;
		if (g_nEnemyActionCnt > 0)			continue;	// 一定時間経過していなければ門前払い

		CheckEnemyUnitMove(pUnit->Job.nMove, pUnit->nPosX, pUnit->nPosY);

		for (y = 0, pField = GetField(); y < FIELD_HEIGHT; y++)
		{
			for (x = 0; x < FIELD_WIDTH; x++, pField++)
			{
				if (!pField->bPass) continue;	// 通行不可なら門前払い

				for (j = 0, pPlayer = GetPlayerUnit(); j < MAX_PLAYER_UNIT_NUM; j++, pPlayer++)
				{
					if (!pPlayer->bExist) continue;	// 存在しないなら門前払い

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
				if (!pField->bPass) continue;	// 通行不可なら門前払い

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
	//===== 変数宣言 =====
	int i, x, y, bufx, bufy;
	UNIT *pUnit;
	
	//===== 初期化処理 =====
	bufx = GetFieldBufferX();
	bufy = GetFieldBufferY();

	//===== 描画処理 =====
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
	//===== 更新処理 =====
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
	//===== 変数宣言 =====
	int i;
	UNIT *pUnit;

	//===== 更新処理 =====
	for (i = 0, pUnit = g_aEnemyUnit; i < MAX_PLAYER_UNIT_NUM; i++, pUnit++)
	{
		pUnit->bAction = false;
	}
}
