//------------------------------------------
//								  window.cpp
//　制作者:AT11B192 No.17 小畠大季
//更新履歴～～～～～～～～～～～～～～～～～
//2020/03/01
// プログラム制作開始
//～～～～～～～～～～～～～～～～～～～～～
//===== インクルード部 =====
#include "bitmap.h"
#include "buffer.h"
#include "window.h"
#include "chara.h"
#include "cursor.h"
#include "field.h"
#include "unit.h"
#include "player.h"
#include "enemy.h"

//===== 定数・マクロ定義 =====
#define TERRAIN_WINDOW_FILE		("bmp/TerrainWindow.bmp")	// 地形情報ウィンドウの画像のファイル名
#define CIRCLE_FILE				("bmp/Circle.bmp")			// ○の画像のファイル名
#define CROSS_FILE				("bmp/Cross.bmp")			// ×の画像のファイル名
#define UNIT_WINDOW_FILE		("bmp/UnitWindow.bmp")		// ユニットウィンドウの画像のファイル名
#define TERRAIN_WINDOW_RIGHT_X	(WINDOW_WIDTH - TERRAIN_WINDOW_WIDTH)	// 地形情報ウィンドウを右側に表示する場合の座標
#define TERRAIN_STRING_Y_1		(3)		// 地形情報ウィンドウの1行目の文字を表示する高さ
#define TERRAIN_STRING_Y_2		(15)	// 地形情報ウィンドウの2行目の文字を表示する高さ
#define TERRAIN_STRING_X		(10)	// 地形情報ウィンドウの文字を表示し始めるX座標
#define TERRAIN_STRING_SPACE	(5)		// 地形情報ウィンドウの文字と文字の間隔
#define UNIT_WINDOW_Y			(WINDOW_HEIGHT - UNIT_WINDOW_HEIGHT)	// ユニットウィンドウを表示するY座標
#define UNIT_WINDOW_RIGHT_X		(WINDOW_WIDTH - UNIT_WINDOW_WIDTH)		// ユニットウィンドウを右側に表示する場合のX座標
#define UNIT_NAME_X				(CHARA_SIZE * 2)		// ユニットウィンドウにユニットの名前を表示し始めるX座標
#define UNIT_STRING_X_1			(5)						// ユニットウィンドウの文字を表示し始めるX座標(左側)
#define UNIT_STRING_X_2			(UNIT_STRING_X_1 + 100)	// ユニットウィンドウの文字を表示し始めるX座標(右側)
#define UNIT_STRING_X_3			(UNIT_STRING_X_2 + 70)	// ユニットウィンドウの文字を表示し始めるX座標(MaxLife)
#define UNIT_SLASH_X			(UNIT_STRING_X_2 + 56)	// ユニットウィンドウのLife欄に/を表示するX座標
#define UNIT_STRING_Y_1			(UNIT_WINDOW_Y + 3)		// ユニットウィンドウの1行目の文字を表示し始めるY座標
#define UNIT_STRING_Y_2			(UNIT_STRING_Y_1 + 12)	// ユニットウィンドウの2行目の文字を表示し始めるY座標
#define UNIT_STRING_Y_3			(UNIT_STRING_Y_2 + 12)	// ユニットウィンドウの3行目の文字を表示し始めるY座標
#define UNIT_STRING_Y_4			(UNIT_STRING_Y_3 + 12)	// ユニットウィンドウの4行目の文字を表示し始めるY座標
#define UNIT_STRING_Y_5			(UNIT_STRING_Y_4 + 12)	// ユニットウィンドウの5行目の文字を表示し始めるY座標
#define UNIT_STRING_Y_6			(UNIT_STRING_Y_5 + 12)	// ユニットウィンドウの6行目の文字を表示し始めるY座標
#define UNIT_STRING_SPACE		(0)		// ユニットウィンドウの文字と文字の間隔

//===== グローバル変数 =====
BUFFER g_WindowBuffer;
IMAGE *g_pTerrainWindowImage;
IMAGE *g_pCircleImage;
IMAGE *g_pCrossImage;
IMAGE *g_pUnitWindowImage;
bool g_bCursorLeft;

void InitWindow(void)
{
	InitBuffer(&g_WindowBuffer);
	g_pTerrainWindowImage = Read_Bmp(TERRAIN_WINDOW_FILE, TERRAIN_WINDOW_HEIGHT, TERRAIN_WINDOW_WIDTH);
	g_pCircleImage = Read_Bmp(CIRCLE_FILE, CHARA_SIZE, CHARA_SIZE * 2);
	g_pCrossImage  = Read_Bmp(CROSS_FILE , CHARA_SIZE, CHARA_SIZE * 2);
	g_pUnitWindowImage = Read_Bmp(UNIT_WINDOW_FILE, UNIT_WINDOW_HEIGHT, UNIT_WINDOW_WIDTH);
	g_bCursorLeft = false;
}

void UpdateWindow(void)
{
	//===== 変数宣言 =====
	CURSOR *pCursor;
	UNIT *pUnit;
	int nFieldBufferX, nFieldBufferY;

	//===== 初期化処理 =====
	pCursor = GetCursor_DK();
	nFieldBufferX = GetFieldBufferX();
	nFieldBufferY = GetFieldBufferY();

	//===== 更新処理 =====
	if (pCursor->Pos.X < FIELD_BUFFER_WIDTH / 2)	g_bCursorLeft = true;
	else											g_bCursorLeft = false;
	
	if (g_bCursorLeft)
	{
		UpdateBuffer(&g_WindowBuffer, g_pTerrainWindowImage, WINDOW_WIDTH - TERRAIN_WINDOW_WIDTH, 0);
		SetChara(GetTerrainInfo(pCursor->Pos.X + nFieldBufferX, pCursor->Pos.Y + nFieldBufferY)->TerrainName, TERRAIN_WINDOW_RIGHT_X + TERRAIN_STRING_X, TERRAIN_STRING_Y_1, TERRAIN_STRING_SPACE);
		SetChara("いどう:", TERRAIN_WINDOW_RIGHT_X + TERRAIN_STRING_X, TERRAIN_STRING_Y_2,0);
		if (GetTerrainInfo(pCursor->Pos.X + nFieldBufferX, pCursor->Pos.Y + nFieldBufferY)->nPassCost > 0)	UpdateBuffer(&g_WindowBuffer, g_pCircleImage, TERRAIN_WINDOW_RIGHT_X + TERRAIN_STRING_X + CHARA_SIZE * 2 * 4, TERRAIN_STRING_Y_2);
		else																								UpdateBuffer(&g_WindowBuffer, g_pCrossImage , TERRAIN_WINDOW_RIGHT_X + TERRAIN_STRING_X + CHARA_SIZE * 2 * 4, TERRAIN_STRING_Y_2);
		
		switch(GetFieldxy(pCursor->Pos.X + nFieldBufferX, pCursor->Pos.Y + nFieldBufferY)->UnitType)
		{
		case FIELD_UNIT_NONE:	return;
		case FIELD_UNIT_PLAYER:	UpdateBuffer(&g_WindowBuffer, g_pUnitWindowImage, UNIT_WINDOW_RIGHT_X, UNIT_WINDOW_Y);
								pUnit = GetPlayerUnit();
								break;
		case FIELD_UNIT_ENEMY:	UpdateBuffer(&g_WindowBuffer, g_pUnitWindowImage, UNIT_WINDOW_RIGHT_X, UNIT_WINDOW_Y);
								pUnit = GetEnemyUnit();
								break;
		default:
			break;
		}
		while (pUnit->nPosY != pCursor->Pos.Y + nFieldBufferY || pUnit->nPosX != pCursor->Pos.X + nFieldBufferX)	pUnit++;

		SetChara(pUnit->szName, UNIT_WINDOW_RIGHT_X + UNIT_NAME_X                     , UNIT_STRING_Y_1, 0);
		SetChara("せいめい:"  , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_1                 , UNIT_STRING_Y_2, 0);	SetNum(pUnit->nLife        , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_2, UNIT_STRING_Y_2);
		SetChara("/"          , UNIT_WINDOW_RIGHT_X + UNIT_SLASH_X                    , UNIT_STRING_Y_2, 0);	SetNum(pUnit->Job.nMaxLife , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_3, UNIT_STRING_Y_2);
		SetChara("こうげき:"  , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_1                 , UNIT_STRING_Y_3, 0);	SetNum(pUnit->Job.nAtk     , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_2, UNIT_STRING_Y_3);
		SetChara("ぼうぎょ:"  , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_1                 , UNIT_STRING_Y_4, 0);	SetNum(pUnit->Job.nDef     , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_2, UNIT_STRING_Y_4);
		SetChara(  "いどう:"  , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_1 + CHARA_SIZE * 2, UNIT_STRING_Y_5, 0);	SetNum(pUnit->Job.nMove    , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_2, UNIT_STRING_Y_5);
		SetChara("しゃてい:"  , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_1                 , UNIT_STRING_Y_6, 0);	SetNum(pUnit->Job.nAtkRange, UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_2, UNIT_STRING_Y_6);
	}
	else
	{
		UpdateBuffer(&g_WindowBuffer, g_pTerrainWindowImage, 0, 0);
		SetChara(GetTerrainInfo(pCursor->Pos.X + nFieldBufferX, pCursor->Pos.Y + nFieldBufferY)->TerrainName, TERRAIN_STRING_X, TERRAIN_STRING_Y_1, TERRAIN_STRING_SPACE);
		SetChara("いどう:", TERRAIN_STRING_X, TERRAIN_STRING_Y_2, 0);
		if (GetTerrainInfo(pCursor->Pos.X + nFieldBufferX, pCursor->Pos.Y + nFieldBufferY)->nPassCost > 0)	UpdateBuffer(&g_WindowBuffer, g_pCircleImage, TERRAIN_STRING_X + CHARA_SIZE * 2 * 4, TERRAIN_STRING_Y_2);
		else																								UpdateBuffer(&g_WindowBuffer, g_pCrossImage , TERRAIN_STRING_X + CHARA_SIZE * 2 * 4, TERRAIN_STRING_Y_2);
	
		switch (GetFieldxy(pCursor->Pos.X + nFieldBufferX, pCursor->Pos.Y + nFieldBufferY)->UnitType)
		{
		case FIELD_UNIT_NONE:	return;
		case FIELD_UNIT_PLAYER:	UpdateBuffer(&g_WindowBuffer, g_pUnitWindowImage, 0, UNIT_WINDOW_Y);
			pUnit = GetPlayerUnit();
			break;
		case FIELD_UNIT_ENEMY:	UpdateBuffer(&g_WindowBuffer, g_pUnitWindowImage, 0, UNIT_WINDOW_Y);
			pUnit = GetEnemyUnit();
			break;
		default:
			break;
		}
		while (pUnit->nPosY != pCursor->Pos.Y + nFieldBufferY || pUnit->nPosX != pCursor->Pos.X + nFieldBufferX)	pUnit++;

		SetChara(pUnit->szName, UNIT_NAME_X                     , UNIT_STRING_Y_1, 0);
		SetChara("せいめい:"  , UNIT_STRING_X_1                 , UNIT_STRING_Y_2, 0);	SetNum(pUnit->nLife        , UNIT_STRING_X_2, UNIT_STRING_Y_2);
		SetChara("/"          , UNIT_SLASH_X                    , UNIT_STRING_Y_2, 0);	SetNum(pUnit->Job.nMaxLife , UNIT_STRING_X_3, UNIT_STRING_Y_2);
		SetChara("こうげき:"  , UNIT_STRING_X_1                 , UNIT_STRING_Y_3, 0);	SetNum(pUnit->Job.nAtk     , UNIT_STRING_X_2, UNIT_STRING_Y_3);
		SetChara("ぼうぎょ:"  , UNIT_STRING_X_1                 , UNIT_STRING_Y_4, 0);	SetNum(pUnit->Job.nDef     , UNIT_STRING_X_2, UNIT_STRING_Y_4);
		SetChara(  "いどう:"  , UNIT_STRING_X_1 + CHARA_SIZE * 2, UNIT_STRING_Y_5, 0);	SetNum(pUnit->Job.nMove    , UNIT_STRING_X_2, UNIT_STRING_Y_5);
		SetChara("しゃてい:"  , UNIT_STRING_X_1                 , UNIT_STRING_Y_6, 0);	SetNum(pUnit->Job.nAtkRange, UNIT_STRING_X_2, UNIT_STRING_Y_6);
	}
}

void DrawWindow(void)
{
	CombineBuffer(&g_WindowBuffer);
}

void EndWindow(void)
{

}
