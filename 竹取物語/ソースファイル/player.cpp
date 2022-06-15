//------------------------------------------
//								  player.cpp
//　制作者:AT11B192 No.17 小畠大季
//更新履歴～～～～～～～～～～～～～～～～～
//2020/02/28
// プログラム制作開始
//～～～～～～～～～～～～～～～～～～～～～
//===== インクルード部 =====
#define CONIOEX
#include "conioex.h"
#include "bitmap.h"
#include "buffer.h"
#include "player.h"
#include "unit.h"
#include "field.h"
#include "main.h"

//===== 定数・マクロ定義 =====
#define PLAYER_ANIME_FLAME	(3)					// プレイヤーのアニメのコマ数
#define PLAYER_SPAWN_WIDTH	(10)				// プレイヤーユニットのスポーン範囲(横)
#define PLAYER_SPAWN_HEIGHT	(5)					// プレイヤーユニットのスポーン範囲(縦)
#define PLAYER_SPAWN_POS_X	((FIELD_WIDTH - PLAYER_SPAWN_WIDTH) / 2)	// プレイヤーユニットのスポーン位置のX座標(左上)
#define PLAYER_SPAWN_POS_Y	(0)					// プレイヤーユニットのスポーン位置のY座標(左上)

//===== プロトタイプ宣言 =====
void SetPlayerSpawnPos(UNIT*);

//===== グローバル変数 =====
BUFFER g_PlayerBuffer;
UNIT g_aPlayerUnit[MAX_PLAYER_UNIT_NUM];
IMAGE *g_paPlayerImage[JOB_MAX][DIRECTION_MAX][PLAYER_ANIME_FLAME];

int g_nPlayerActionCnt;

void InitPlayer(void)
{
	//===== 変数宣言 =====
	int i, j, k;
	UNIT *pUnit;
	IMAGE **pImage;

	char szaPlayerUnitAnime[JOB_MAX][DIRECTION_MAX][PLAYER_ANIME_FLAME][MAX_FILE_NAME] =
	{
	  { { { "bmp/ブシドー/ブシドー.bmp" }	     , { "bmp/ブシドー/ブシドー1.bmp" }	       , { "bmp/ブシドー/ブシドー2.bmp" }         },
		{ { "bmp/ブシドー/ブシドーバック.bmp" }  , { "bmp/ブシドー/ブシドーバック1.bmp" }  , { "bmp/ブシドー/ブシドーバック2.bmp" }   },
		{ { "bmp/ブシドー/ブシドーフロント.bmp" }, { "bmp/ブシドー/ブシドーフロント1.bmp" }, { "bmp/ブシドー/ブシドーフロント2.bmp" } },
		{ { "bmp/ブシドー/ブシドーレフト.bmp" }  , { "bmp/ブシドー/ブシドーレフト1.bmp" }  , { "bmp/ブシドー/ブシドーレフト2.bmp" }   },
		{ { "bmp/ブシドー/ブシドーライト.bmp" }  , { "bmp/ブシドー/ブシドーライト1.bmp" }  , { "bmp/ブシドー/ブシドーライト2.bmp" }   }
	  },// SWORDMAN
		{ { { "bmp/ブシドー/ブシドー.bmp" }	     , { "bmp/ブシドー/ブシドー1.bmp" }	       , { "bmp/ブシドー/ブシドー2.bmp" }         },
		{ { "bmp/ブシドー/ブシドーバック.bmp" }  , { "bmp/ブシドー/ブシドーバック1.bmp" }  , { "bmp/ブシドー/ブシドーバック2.bmp" }   },
		{ { "bmp/ブシドー/ブシドーフロント.bmp" }, { "bmp/ブシドー/ブシドーフロント1.bmp" }, { "bmp/ブシドー/ブシドーフロント2.bmp" } },
		{ { "bmp/ブシドー/ブシドーレフト.bmp" }  , { "bmp/ブシドー/ブシドーレフト1.bmp" }  , { "bmp/ブシドー/ブシドーレフト2.bmp" }   },
		{ { "bmp/ブシドー/ブシドーライト.bmp" }  , { "bmp/ブシドー/ブシドーライト1.bmp" }  , { "bmp/ブシドー/ブシドーライト2.bmp" }   }
	  },// SPEARMAN
	{ { { "bmp/ブシドー/ブシドー.bmp" }	         , { "bmp/ブシドー/ブシドー1.bmp" }	       , { "bmp/ブシドー/ブシドー2.bmp" }         },
		{ { "bmp/ブシドー/ブシドーバック.bmp" }  , { "bmp/ブシドー/ブシドーバック1.bmp" }  , { "bmp/ブシドー/ブシドーバック2.bmp" }   },
		{ { "bmp/ブシドー/ブシドーフロント.bmp" }, { "bmp/ブシドー/ブシドーフロント1.bmp" }, { "bmp/ブシドー/ブシドーフロント2.bmp" } },
		{ { "bmp/ブシドー/ブシドーレフト.bmp" }  , { "bmp/ブシドー/ブシドーレフト1.bmp" }  , { "bmp/ブシドー/ブシドーレフト2.bmp" }   },
		{ { "bmp/ブシドー/ブシドーライト.bmp" }  , { "bmp/ブシドー/ブシドーライト1.bmp" }  , { "bmp/ブシドー/ブシドーライト2.bmp" }   }
	  },// BOWMAN
	};

	//===== 初期化処理 =====
	InitBuffer(&g_PlayerBuffer);
	pImage = &g_paPlayerImage[0][0][0];
	for (i = 0; i < JOB_MAX; i++)
		for (j = 0; j < DIRECTION_MAX; j++)
			for (k = 0; k < PLAYER_ANIME_FLAME; k++, pImage++)
				*pImage = Read_Bmp(szaPlayerUnitAnime[i][j][k], TILE_SIZE, TILE_SIZE * 2);

	g_nPlayerActionCnt = 0;
	InitUnit(&g_aPlayerUnit[0], "いその" , JOB_SWORDMAN);
	InitUnit(&g_aPlayerUnit[1], "へいしA", JOB_SPEARMAN);
	InitUnit(&g_aPlayerUnit[2], "へいしB", JOB_SPEARMAN);
	InitUnit(&g_aPlayerUnit[3], "へいしC", JOB_BOWMAN);
	InitUnit(&g_aPlayerUnit[4], "へいしD", JOB_BOWMAN);
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
	//===== 変数宣言 =====
	int i, x, y, bufx, bufy;
	UNIT *pUnit;

	//===== 初期化処理 =====
	bufx = GetFieldBufferX();
	bufy = GetFieldBufferY();

	//===== 更新処理 =====
	if (g_nPlayerActionCnt == MAX_PLAYER_UNIT_NUM)
	{
		SetMODE(MODE_ENEMY);
	}

	for (i = 0, pUnit = g_aPlayerUnit; i < MAX_PLAYER_UNIT_NUM; i++, pUnit++)
	{
		if (!pUnit->bExist)	continue;	// 存在しなければ門前払い
		
		if (!pUnit->bAction)	pUnit->nAnimeCnt++;	// 行動済みならアニメーションOFF

		if (pUnit->nAnimeCnt > UNIT_ANIME_DELAY) // アニメーション更新
		{
			pUnit->nAnimeNum = (pUnit->nAnimeNum + 1) % (PLAYER_ANIME_FLAME);
			pUnit->pImage = g_paPlayerImage[pUnit->Job.Job][pUnit->Dir][pUnit->nAnimeNum];
			pUnit->nAnimeCnt = 0;
		}
		
		for (y = 0; y < FIELD_BUFFER_HEIGHT; y++)
		{
			for (x = 0; x < FIELD_BUFFER_WIDTH; x++)
			{
				if (pUnit->nPosY != bufy + y || pUnit->nPosX != bufx + x) continue;	// 画面内にユニットがいなければ門前払い

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
	//===== 更新処理 =====
	do
	{
		pUnit->nNextPosX = pUnit->nPosX = rand() % PLAYER_SPAWN_WIDTH + PLAYER_SPAWN_POS_X;
		pUnit->nNextPosY = pUnit->nPosY = rand() % PLAYER_SPAWN_HEIGHT + PLAYER_SPAWN_POS_Y;
	} while (GetTerrainInfo(pUnit->nPosX, pUnit->nPosY)->nPassCost == (-1) || GetFieldxy(pUnit->nPosX, pUnit->nPosY)->UnitType != FIELD_UNIT_NONE);
	GetFieldxy(pUnit->nPosX, pUnit->nPosY)->UnitType = FIELD_UNIT_PLAYER;
}

void ResetPlayerAction(void)
{
	//===== 変数宣言 =====
	int i;
	UNIT *pUnit;

	//===== 更新処理 =====
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