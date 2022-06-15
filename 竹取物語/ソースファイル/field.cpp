//------------------------------------------
//								   field.cpp
//　制作者:AT11B192 No.17 小畠大季
//更新履歴～～～～～～～～～～～～～～～～～
//2020/02/21
// プログラム制作開始
//2020/02/29
// 地形を生成する関数を作成
//～～～～～～～～～～～～～～～～～～～～～
//===== インクルード部 =====
#include <Windows.h>
#define CONIOEX
#include "conioex.h"
#include "buffer.h"
#include "bitmap.h"
#include "field.h"
#include "cursor.h"
#include "main.h"

//===== 定数・マクロ定義 =====
#define TERRAIN_PLAIN_FILE		("bmp/Plain.bmp")		// 平地の画像のファイル名
#define TERRAIN_FOREST_FILE		("bmp/Forest.bmp")		// 森の画像のファイル名
#define TERRAIN_MOUNTAINS_FILE	("bmp/Mountins.bmp")	// 山の画像のファイル名
#define TERRAIN_RIVER_FILE		("bmp/River.bmp")		// 川の画像のファイル名
#define MOVETILE_FILE			("bmp/MoveTile.bmp")	// 移動可能タイルの画像のファイル名
#define INVISIBLE_FILE			("bmp/Invisible.bmp")	// 透過タイルの画像のファイル名
#define MAX_FOREST_NUM			(10)	// 森の最大数
#define MIN_FOREST_NUM			(5)		// 森の最低数
#define MAX_FOREST_SIZE			(4)		// 森の最大半径
#define MIN_FOREST_SIZE			(2)		// 森の最低半径
#define MAX_MOUNTAINS_NUM		(5)		// 山の最大数
#define MIN_MOUNTAINS_NUM		(3)		// 山の最大数
#define MAX_MOUNTAINS_SIZE		(3)		// 山の最大半径
#define MIN_MOUNTAINS_SIZE		(1)		// 山の最低半径
#define MAX_MOUNTAINS_LENGTH	(7)		// 山脈の最大長
#define MIN_MOUNTAINS_LENGTH	(3)		// 山脈の最低長
#define MAX_RIVER_NUM			(8)		// 川の最大本数
#define MIN_RIVER_NUM			(4)		// 川の最低本数
#define MAX_RIVER_LENGTH		(10)	// 川の最大流域
#define MIN_RIVER_LENGTH		(5)		// 川の最低流域
#define TURN_PROBABILITY		(5)		// 山や川が曲がる確率(分の1)
#define TILE_ANIME_FRAME		(2)		// 移動可能表示のアニメのコマ数
#define TILE_ANIME_DELAY		(10)	// 移動可能表示のアニメの間隔(フレーム)

//===== プロトタイプ宣言 =====
void GenerateForest(int);
void GenerateMountains(int);
bool ExtendMountains(int, int, int, int, int);
void GenerateRiver(int);
bool ExtendRiver(int, int, int, int, int);
void CheckPlayerUnitMove(int, int, int);

//===== グローバル変数 =====
BUFFER g_FieldBuffer;	// フィールド用バッファ
TERRAIN_INFO g_aTerrainInfo[TERRAIN_MAX] = {	// 地形データ
	{ TERRAIN_PLAIN    , "へいち", Read_Bmp(TERRAIN_PLAIN_FILE    , TILE_SIZE, TILE_SIZE * 2),  1 },	// 平地
	{ TERRAIN_FOREST   , "もり"  , Read_Bmp(TERRAIN_FOREST_FILE   , TILE_SIZE, TILE_SIZE * 2),  2 },	// 森
	{ TERRAIN_MOUNTAINS, "やま"  , Read_Bmp(TERRAIN_MOUNTAINS_FILE, TILE_SIZE, TILE_SIZE * 2), -1 },	// 山
	{ TERRAIN_RIVER    , "かわ"  , Read_Bmp(TERRAIN_RIVER_FILE    , TILE_SIZE, TILE_SIZE * 2), -1 },	// 川
};	// 地形名			地形タイル　　　　　　　　　　　　　　　　　　　　　　　　必要移動力
FIELD g_aField[FIELD_HEIGHT][FIELD_WIDTH];	// フィールドデータ
COORD g_Buffer;	//フィールドバッファの座標
IMAGE *g_paMoveImage[TILE_ANIME_FRAME];
int g_nMoveCnt;

void InitField(void)
{
	//===== 変数宣言 =====
	int i, j;
	FIELD *pField;

	//===== 初期化処理 =====
	pField = &g_aField[0][0];
	InitBuffer(&g_FieldBuffer);	// バッファの初期化
	g_paMoveImage[0] = Read_Bmp(MOVETILE_FILE, TILE_SIZE, TILE_SIZE * 2);
	g_paMoveImage[1] = Read_Bmp(INVISIBLE_FILE, TILE_SIZE, TILE_SIZE * 2);
	for (i = 0; i < FIELD_HEIGHT; i++)
	{
		for (j = 0; j < FIELD_WIDTH; j++, pField++)
		{
			pField->nPosX = j;	// 座標設定
			pField->nPosY = i;	// 座標設定
			pField->Terrain = g_aTerrainInfo[TERRAIN_PLAIN];
			pField->UnitType = FIELD_UNIT_NONE;	// タイル上にユニットが存在しない
		}
	}
	GenerateForest(MAX_FOREST_NUM);
	GenerateMountains(MAX_MOUNTAINS_NUM);
	GenerateRiver(MAX_RIVER_NUM);
	g_Buffer.X = 0;
	g_Buffer.Y = 0;
	g_nMoveCnt = 0;
}

void UpdateField(void)
{
	//===== 変数宣言 =====
	int i, j;
	FIELD *pField;
	CURSOR *pCursor;

	//===== 更新処理 =====
	for (i = 0; i < FIELD_BUFFER_HEIGHT; i++)
	{
		pField = &g_aField[g_Buffer.Y + i][g_Buffer.X];
		for (j = 0; j < FIELD_BUFFER_WIDTH; j++, pField++)
		{
			UpdateBuffer(&g_FieldBuffer, g_aTerrainInfo[pField->Terrain.Terrain].pImage, j * TILE_SIZE * 2, i * TILE_SIZE);
		}
	}

	if (GetMODE() == MODE_MOVEUNIT)
	{
		g_nMoveCnt++;
		pCursor = GetCursor_DK();
		CheckPlayerUnitMove(pCursor->pSelectUnit->Job.nMove, pCursor->pSelectUnit->nPosX, pCursor->pSelectUnit->nPosY);
		for (i = 0; i < FIELD_BUFFER_HEIGHT; i++)
		{
			pField = &g_aField[g_Buffer.Y + i][g_Buffer.X];
			for (j = 0; j < FIELD_BUFFER_WIDTH; j++, pField++)
			{
				if (!pField->bPass) continue;

				if (g_nMoveCnt < TILE_ANIME_DELAY)	UpdateBuffer(&g_FieldBuffer, g_paMoveImage[0], j * TILE_SIZE * 2, i * TILE_SIZE);
				else								UpdateBuffer(&g_FieldBuffer, g_paMoveImage[1], j * TILE_SIZE * 2, i * TILE_SIZE);
			}
		}
		if (g_nMoveCnt > TILE_ANIME_DELAY * 2)	g_nMoveCnt = 0;
	}
}

void DrawField(void)
{
	CombineBuffer(&g_FieldBuffer);
}

void EndField(void)
{

}


void GenerateForest(int GeneratePer)
{
	//===== 変数宣言 =====
	int i, j;
	int nRange;
	int nPosX, nPosY;
	int nDifX, nDifY;

	//===== 初期化処理 =====
	nRange = rand() % (MAX_FOREST_SIZE - MIN_FOREST_SIZE + 1) + MIN_FOREST_SIZE;
	nPosX  = rand() % FIELD_WIDTH;
	nPosY  = rand() % FIELD_HEIGHT;

	//===== 更新処理 =====
	for (i = 0; i < FIELD_HEIGHT; i++)
	{
		for (j = 0; j < FIELD_WIDTH; j++)
		{
			nDifX = j - nPosX;
			nDifY = i - nPosY;
			if (nDifX < 0)	nDifX *= -1;
			if (nDifY < 0)	nDifY *= -1;

			if (nDifX + nDifY <= nRange)
				g_aField[i][j].Terrain = g_aTerrainInfo[TERRAIN_FOREST];
		}
	}
	
	if (GeneratePer + MIN_FOREST_NUM > MAX_FOREST_NUM)	GenerateForest(GeneratePer - 1);
	else if (rand() % GeneratePer)	GenerateForest(GeneratePer - 1);
}

void GenerateMountains(int GeneratePer)
{
	//===== 変数宣言 =====
	int i, j;
	int nRange;
	int nPosX, nPosY;
	int nDifX, nDifY;
	int nDirX, nDirY;
	int nLength;

	//----- 山と山脈で分岐 -----
	if (rand() % 2)	//大きめの山を生成
	{
		//===== 初期化処理 =====
		nRange = rand() % (MAX_MOUNTAINS_SIZE - MIN_MOUNTAINS_SIZE + 1) + MIN_MOUNTAINS_SIZE;
		nPosX = rand() % FIELD_WIDTH;
		nPosY = rand() % FIELD_HEIGHT;

		//===== 更新処理 =====
		for (i = 0; i < FIELD_HEIGHT; i++)
		{
			for (j = 0; j < FIELD_WIDTH; j++)
			{
				nDifX = j - nPosX;
				nDifY = i - nPosY;
				if (nDifX < 0)	nDifX *= -1;
				if (nDifY < 0)	nDifY *= -1;

				if (nDifX + nDifY <= nRange)
					g_aField[i][j].Terrain = g_aTerrainInfo[TERRAIN_MOUNTAINS];
			}
		}
	}
	else //山脈を生成
	{
		//===== 初期化処理 =====
		nPosX = rand() % FIELD_WIDTH;
		nPosY = rand() % FIELD_HEIGHT;
		do
		{
			nDirX = rand() % 3 - 1;
			nDirY = rand() % 3 - 1;
		} while (nDirX == 0 && nDirY == 0);
		nLength = rand() % (MAX_MOUNTAINS_LENGTH - MIN_MOUNTAINS_LENGTH + 1) + MIN_MOUNTAINS_LENGTH;

		//===== 更新処理 =====
		if (ExtendMountains(nLength, nPosX + nDirX, nPosY + nDirY, nDirX, nDirY))
		{
			g_aField[nPosY][nPosY].Terrain = g_aTerrainInfo[TERRAIN_MOUNTAINS];
		}
	}

	if (GeneratePer + MIN_MOUNTAINS_NUM > MAX_MOUNTAINS_NUM)	GenerateMountains(GeneratePer - 1);
	else if (rand() % GeneratePer)	GenerateMountains(GeneratePer - 1);
}

bool ExtendMountains(int Length, int PosX, int PosY, int DirX, int DirY)
{
	//===== 変数宣言 =====
	int nDirX, nDirY;

	//===== 初期化処理 =====
	nDirX = DirX;
	nDirY = DirY;

	//===== 更新処理 =====
	if (!(rand() % TURN_PROBABILITY))	nDirX = rand() % 3 - 1;
	if (!(rand() % TURN_PROBABILITY))	nDirY = rand() % 3 - 1;

	if (Length > 0)
	{
		if (PosY < 0 || PosY >= FIELD_HEIGHT || PosX < 0 || PosX >= FIELD_WIDTH)	return false;
		if (g_aField[PosY][PosX].Terrain.Terrain == TERRAIN_RIVER || g_aField[PosY][PosX].Terrain.Terrain == TERRAIN_MOUNTAINS)	return false;

		if (ExtendMountains(Length - 1, PosX + nDirX, PosY + nDirY, nDirX, nDirY))
		{
			g_aField[PosY][PosX].Terrain = g_aTerrainInfo[TERRAIN_MOUNTAINS];
		}
	}

	return true;
}

void GenerateRiver(int GeneratePer)
{
	//===== 変数宣言 =====
	int nPosX, nPosY;
	int nDirX, nDirY;
	int nLength;

	//===== 初期化処理 =====
	nPosX = rand() % FIELD_WIDTH;
	nPosY = rand() % FIELD_HEIGHT;
	do
	{
		nDirX = rand() % 3 - 1;
		nDirY = rand() % 3 - 1;
	} while (nDirX == 0 && nDirY == 0);
	nLength = rand() % (MAX_RIVER_LENGTH - MIN_RIVER_LENGTH + 1) + MIN_RIVER_LENGTH;

	//===== 更新処理 =====
	if (ExtendRiver(nLength, nPosX + nDirX, nPosY + nDirY, nDirX, nDirY))
	{
		g_aField[nPosY][nPosY].Terrain = g_aTerrainInfo[TERRAIN_RIVER];
	}

	if (GeneratePer + MIN_RIVER_NUM > MAX_RIVER_NUM)	GenerateRiver(GeneratePer - 1);
	else if (rand() % GeneratePer)	GenerateRiver(GeneratePer - 1);
}

bool ExtendRiver(int Length, int PosX, int PosY, int DirX, int DirY)
{
	//===== 変数宣言 =====
	int nDirX, nDirY;

	//===== 初期化処理 =====
	nDirX = DirX;
	nDirY = DirY;

	//===== 更新処理 =====
	if (!(rand() % TURN_PROBABILITY))	nDirX = rand() % 3 - 1;
	if (!(rand() % TURN_PROBABILITY))	nDirY = rand() % 3 - 1;

	if (Length > 0)
	{
		if (PosY < 0 || PosY >= FIELD_HEIGHT || PosX < 0 || PosX >= FIELD_WIDTH)	return false;
		if (g_aField[PosY][PosX].Terrain.Terrain == TERRAIN_RIVER || g_aField[PosY][PosX].Terrain.Terrain == TERRAIN_MOUNTAINS)	return false;

		if (ExtendRiver(Length - 1, PosX + nDirX, PosY + nDirY, nDirX, nDirY))
		{
			g_aField[PosY][PosX].Terrain = g_aTerrainInfo[TERRAIN_RIVER];
		}
	}

	return true;
}

void CheckPlayerUnitMove(int UnitCost, int x, int y)
{
	if (UnitCost < 0 || x < 0 || y < 0 || FIELD_WIDTH <= x || FIELD_HEIGHT <= y)	return;
	
	if (g_aField[y][x].Terrain.nPassCost > 0)
	{
		switch (g_aField[y][x].UnitType)
		{
		case FIELD_UNIT_NONE:	g_aField[y][x].bPass = true;
			CheckPlayerUnitMove(UnitCost - g_aField[y][x].Terrain.nPassCost, x + 1, y	 );
			CheckPlayerUnitMove(UnitCost - g_aField[y][x].Terrain.nPassCost, x    , y + 1);
			CheckPlayerUnitMove(UnitCost - g_aField[y][x].Terrain.nPassCost, x - 1, y	 );
			CheckPlayerUnitMove(UnitCost - g_aField[y][x].Terrain.nPassCost, x    , y - 1);
			break;
		case FIELD_UNIT_PLAYER:	CheckPlayerUnitMove(UnitCost - g_aField[y][x].Terrain.nPassCost, x + 1, y    );
			CheckPlayerUnitMove(UnitCost - g_aField[y][x].Terrain.nPassCost, x    , y + 1);
			CheckPlayerUnitMove(UnitCost - g_aField[y][x].Terrain.nPassCost, x - 1, y    );
			CheckPlayerUnitMove(UnitCost - g_aField[y][x].Terrain.nPassCost, x    , y - 1);
			break;
		case FIELD_UNIT_ENEMY:
			break;
		default:
			break;
		}
	}
}

void CheckEnemyUnitMove(int UnitCost, int x, int y)
{
	if (UnitCost <= 0 || x < 0 || y < 0 || FIELD_WIDTH <= x || FIELD_HEIGHT <= y)	return;

	switch (g_aField[y][x].UnitType)
	{
	case FIELD_UNIT_NONE:	g_aField[y][x].bPass = true;
		CheckPlayerUnitMove(UnitCost - 1, x + 1, y);
		CheckPlayerUnitMove(UnitCost - 1, x, y + 1);
		CheckPlayerUnitMove(UnitCost - 1, x - 1, y);
		CheckPlayerUnitMove(UnitCost - 1, x, y - 1);
		break;
	case FIELD_UNIT_PLAYER:	
		break;
	case FIELD_UNIT_ENEMY:
		CheckPlayerUnitMove(UnitCost - 1, x + 1, y);
		CheckPlayerUnitMove(UnitCost - 1, x, y + 1);
		CheckPlayerUnitMove(UnitCost - 1, x - 1, y);
		CheckPlayerUnitMove(UnitCost - 1, x, y - 1);
		break;
	default:
		break;
	}
}

FIELD* GetField(void)
{
	return &g_aField[0][0];
}

FIELD* GetFieldxy(int x, int y)
{
	return &g_aField[y][x];
}

int GetFieldBufferX(void)
{
	return g_Buffer.X;
}

int GetFieldBufferY(void)
{
	return g_Buffer.Y;
}

void SetFieldBuffer(int x, int y)
{
	g_Buffer.X = x;
	if (g_Buffer.X < 0)									g_Buffer.X = 0;
	if (g_Buffer.X + FIELD_BUFFER_WIDTH > FIELD_WIDTH)	g_Buffer.X = FIELD_WIDTH - FIELD_BUFFER_WIDTH;

	g_Buffer.Y = y;
	if (g_Buffer.Y < 0)										g_Buffer.Y = 0;
	if (g_Buffer.Y + FIELD_BUFFER_HEIGHT > FIELD_HEIGHT)	g_Buffer.Y = FIELD_HEIGHT - FIELD_BUFFER_HEIGHT;
}

void MoveFieldBuffer(int x, int y)
{
	g_Buffer.X += x;
	if (g_Buffer.X < 0)									g_Buffer.X = 0;
	if (g_Buffer.X + FIELD_BUFFER_WIDTH > FIELD_WIDTH)	g_Buffer.X = FIELD_WIDTH - FIELD_BUFFER_WIDTH;

	g_Buffer.Y += y;
	if (g_Buffer.Y < 0)										g_Buffer.Y = 0;
	if (g_Buffer.Y + FIELD_BUFFER_HEIGHT > FIELD_HEIGHT)	g_Buffer.Y = FIELD_HEIGHT - FIELD_BUFFER_HEIGHT;
}

TERRAIN_INFO* GetTerrainInfo(int x, int y)
{
	return &g_aField[y][x].Terrain;
}

void ResetPass(void)
{
	//===== 変数宣言 =====
	int i, j;

	//===== 初期化処理 =====
	for (i = 0; i < FIELD_HEIGHT; i++)
	{
		for (j = 0; j < FIELD_WIDTH; j++)
		{
			g_aField[i][j].bPass = false;
		}
	}
}
