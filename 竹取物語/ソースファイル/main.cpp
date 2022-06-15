//==========================================
//									main.cpp
//	HEW作品制作
//　制作者:AT11B192 No.17 小畠大季
//～～～～～～～～更新履歴～～～～～～～～～
//2020/02/21
// プログラム制作開始
//2020/03/03
// ゲーム選択用の処理を追加
//～～～～～～～～～～～～～～～～～～～～～

//===== インクルード部 =====
#include <Windows.h>
#include "conioex.h"
#include "bitmap.h"
#include "buffer.h"
#include "chara.h"
#include "main.h"
#include "title.h"
#include "field.h"
#include "player.h"
#include "enemy.h"
#include "cursor.h"
#include "window.h"

#include "battle.h"

//===== 定数・マクロ定義 =====
#define FRAME_RATE (1000/30)	// 処理が行われる間隔(ミリ秒)

//===== グローバル変数 =====
MODE g_Mode;	// ゲームのモード管理用
int g_nCountFPS;// FPS用カウンタ
BUFFER g_ClearBuffer;
IMAGE *g_pClearImage;

//--------------------------------------
//関数名：main
//引　数：なし
//戻り値：int (0:成功 1:失敗)
//内　容：プログラム全体の流れを制御する
//--------------------------------------
int main(void)
{
	//===== 変数宣言 =====
	char sTitle[] = GAME_TITLE;
	int nCurrentTime;	// 現在時間
	int nExecLastTime;	// 前回実行時間

	//===== 前処理 =====
	setcursortype(NOCURSOR);// カーソルを非表示
	setcaption(sTitle);		// タイトル
	timeBeginPeriod(1);		// 時間の単位をms(ミリ秒)に変更
	srand(timeGetTime());	// 現在時刻で乱数を再生成
	InitBuffer(&g_ClearBuffer);
	g_pClearImage = Read_Bmp("bmp/ツバメの子安貝.bmp", WINDOW_HEIGHT, WINDOW_HEIGHT * 2);

	//===== 初期化処理 =====
	Init();
	g_Mode = MODE_TITLE;	// ゲームモードをタイトルに変更
	nExecLastTime = nCurrentTime = timeGetTime(); // 現在時刻を取得

	do
	{
		nCurrentTime = timeGetTime(); // 現在時刻を取得

		if (nCurrentTime - nExecLastTime >= FRAME_RATE)
		{
			//SetNum(1000 / (nCurrentTime - nExecLastTime), 0, WINDOW_HEIGHT - CHARA_SIZE);
			nExecLastTime = nCurrentTime;

			//===== 更新処理 =====
			Update();

			//===== 描画処理 =====
			Draw();
		}

	} while (!inport(PK_ESC));

	//===== 終了処理 =====
	return 0;
}

void Init(void)
{
	InitMainBuffer();
	InitChara();
	InitTitle();
	InitField();
	InitPlayer();
	InitEnemy();
	InitCursor();
	InitWindow();

	InitBattle();
}

void Update(void)
{
	switch (g_Mode)
	{
	case MODE_TITLE:	UpdateTitle();
		break;
	case MODE_PLAYER:	UpdateField();
						UpdatePlayer();
						UpdateEnemy();
						UpdateCursor();
						UpdateWindow();
		break;
	case MODE_MOVEUNIT:	UpdateField();
						UpdatePlayer();
						UpdateEnemy();
						UpdateCursor();
						UpdateWindow();
		break;
	case MODE_BATTLE:	UpdateField();
						UpdatePlayer();
						UpdateEnemy();
						UpdateBattle();
		break;
	case MODE_ENEMY:	UpdateField();
						UpdatePlayer();
						UpdateEnemy();
						UpdateWindow();
		break;
	case MODE_CLEAR:
						UpdateBuffer(&g_ClearBuffer, g_pClearImage, WINDOW_WIDTH / 2 - WINDOW_HEIGHT, 0);
		break;
	default:	break;
	}
}

void Draw(void)
{
	switch (g_Mode)
	{
	case MODE_TITLE:	DrawTitle();
		break;
	case MODE_PLAYER:	DrawField();
						DrawPlayer();
						DrawEnemy();
						DrawCursor();
						DrawWindow();
		break;
	case MODE_MOVEUNIT:	DrawField();
						DrawPlayer();
						DrawEnemy();
						DrawCursor();
						DrawWindow();
		break;
	case MODE_BATTLE:	DrawField();
						DrawPlayer();
						DrawEnemy();
						DrawBattle();
		break;
	case MODE_ENEMY:	DrawField();
						DrawPlayer();
						DrawEnemy();
						DrawCursor();
						DrawWindow();
	case MODE_CLEAR:	CombineBuffer(&g_ClearBuffer);
		break;
	case MODE_GAMEOVER:	SetChara("GAMEOVER", WINDOW_WIDTH / 2 - 4 * CHARA_SIZE * 2, WINDOW_HEIGHT / 2 - CHARA_SIZE / 2, 0);
	default:	break;
	}

	DrawChara();
	DrawBuffer();
}

void End(void)
{
	EndBuffer();
	EndChara();
	EndTitle();
	EndField();
	EndPlayer();
	EndEnemy();
	EndCursor();
	EndBattle();
}

void SetMODE(MODE mode)
{
	g_Mode = mode;
}

MODE GetMODE(void)
{
	return g_Mode;
}
