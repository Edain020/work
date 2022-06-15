//------------------------------------------
//								   title.cpp
//　制作者:AT11B192 No.17 小畠大季
//更新履歴～～～～～～～～～～～～～～～～～
//2020/02/21
// プログラム制作開始
//2020/02/21
// ゲーム選択用の処理を追加
//～～～～～～～～～～～～～～～～～～～～～
//===== インクルード部 =====
#define CONIOEX
#include "conioex.h"
#include "title.h"
#include "main.h"
#include "buffer.h"
#include "bitmap.h"

//===== 定数・マクロ定義 =====
#define SAMPLE_IMAGE_WIDTH	(150)
#define SAMPLE_IMAGE_HEIGHT	(75)
#define SAMPLE_IMAGE_X		(70)
#define SAMPLE_IMAGE_Y		(50)

//===== グローバル変数 =====
BUFFER g_TitleBuffer;				// タイトル用バッファ
IMAGE *g_pTitleImage;				// タイトル画像
IMAGE *g_paSampleImage[GAME_MAX];	// 選択画面用画像
bool g_bEnd;						// 終了フラグ
int g_nGameNum;						// 選択中のゲーム

GAME g_aGame[GAME_MAX] = { GAME_DK };	// ゲームの一覧

void InitTitle(void)
{
	//===== 変数宣言 =====
	int i;
	char szTitleFile[] = { "bmp/Title.bmp" };	// タイトルの画像のファイル名
	char szaSampleFile[GAME_MAX][MAX_FILE_NAME] = {
		{ "bmp/ツバメの子安貝.bmp" },
	};	// ゲーム選択用画像のファイル名

	//===== 初期化処理 =====
	g_bEnd = false;
	InitBuffer(&g_TitleBuffer);
	g_pTitleImage = Read_Bmp(szTitleFile, WINDOW_HEIGHT, WINDOW_WIDTH);
	for (i = 0; i < GAME_MAX; i++)
	{
		g_paSampleImage[i] = Read_Bmp(szaSampleFile[i], SAMPLE_IMAGE_HEIGHT, SAMPLE_IMAGE_WIDTH);
	}
	g_nGameNum = 0;
}

void UpdateTitle(void)
{
	//===== 更新処理 =====
	if (!g_bEnd)
	{
		if (inport(PK_RIGHT))
		{
			g_nGameNum = (g_nGameNum + 1) % GAME_MAX;
		}
		if (inport(PK_LEFT))
		{
			g_nGameNum = g_nGameNum - 1;
			if (g_nGameNum < 0)	g_nGameNum = GAME_MAX - 1;
		}
	}
	if (inport(PK_ENTER))
		g_bEnd = true;
	else if (g_bEnd)
	{
		SetMODE(MODE_PLAYER);	// モード切替
		Update();				// 更新処理
	}
	UpdateBuffer(&g_TitleBuffer, g_pTitleImage, 0, 0);
	UpdateBuffer(&g_TitleBuffer, g_paSampleImage[g_nGameNum], SAMPLE_IMAGE_X, SAMPLE_IMAGE_Y);
}

void DrawTitle(void)
{
	CombineBuffer(&g_TitleBuffer);
}

void EndTitle(void)
{

}