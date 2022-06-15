#define CONIOEX
#include "conioex.h"
#include "battle.h"
#include "bitmap.h"
#include "buffer.h"
#include "chara.h"

#include "unit.h"
#include "player.h"
#include "enemy.h"
#include "field.h"
#include "main.h"

#include <stdio.h>

BUFFER g_BattleBuffer;
IMAGE *g_pBattleWindow;

UNIT *g_pUnit;
UNIT *g_pUnit2;

IMAGE *g_paPlayerMotion[6];
IMAGE *g_paEnemyMotion[6];
int g_nFlameCnt;

bool g_bBattleEnd;

void InitBattle(void)
{
	InitBuffer(&g_BattleBuffer);
	g_pBattleWindow = Read_Bmp("Bmp/UnitWindow.bmp", WINDOW_HEIGHT / 5 * 4, WINDOW_WIDTH / 5 * 4);
	g_paEnemyMotion[0] = Read_Bmp("bmp/ツバメ/ツバメライト.bmp", 32, 64);
	g_paEnemyMotion[1] = Read_Bmp("bmp/ツバメ/ツバメモーション.bmp", 32, 128);
	g_paEnemyMotion[2] = Read_Bmp("bmp/ツバメ/ツバメモーション1.bmp", 32, 128);
	g_paEnemyMotion[3] = Read_Bmp("bmp/ツバメ/ツバメモーション2.bmp", 32, 128);
	g_paEnemyMotion[4] = Read_Bmp("bmp/ツバメ/ツバメモーション3.bmp", 32, 128);
	g_paEnemyMotion[5] = Read_Bmp("bmp/ツバメ/ツバメモーション3.bmp", 32, 128);

	g_paPlayerMotion[0] = Read_Bmp("bmp/ブシドー/ブシドーモーション.bmp", 32, 128);
	g_paPlayerMotion[1] = Read_Bmp("bmp/ブシドー/ブシドーモーション1.bmp", 32, 128);
	g_paPlayerMotion[2] = Read_Bmp("bmp/ブシドー/ブシドーモーション2.bmp", 32, 128);
	g_paPlayerMotion[3] = Read_Bmp("bmp/ブシドー/ブシドーモーション3.bmp", 32, 128);
	g_paPlayerMotion[4] = Read_Bmp("bmp/ブシドー/ブシドーモーション4.bmp", 32, 128);
	g_paPlayerMotion[5] = Read_Bmp("bmp/ブシドー/ブシドーモーション5.bmp", 32, 128);
	g_nFlameCnt = 0;
	g_bBattleEnd = false;
}

void UpdateBattle(void)
{
	g_nFlameCnt++;
	if (g_nFlameCnt >= 5)
	{
		g_nFlameCnt = 5;
		if (inport(PK_ENTER) && !g_bBattleEnd)
		{
			SetMODE(MODE_PLAYER);
			g_pUnit2->nLife -= g_pUnit->Job.nAtk;
			if (g_pUnit2->nLife <= 0)
			{
				g_pUnit2->bExist = false;
				GetFieldxy(g_pUnit2->nPosX, g_pUnit2->nPosY)->UnitType = FIELD_UNIT_NONE;
			}
			g_bBattleEnd = true;
		}
		else if (g_bBattleEnd)
		{
			if (g_pUnit->Team == TEAM_PLAYER)
				SetMODE(MODE_PLAYER);
			else
				SetMODE(MODE_ENEMY);
		}
	}
}
void DrawBattle(void)
{
	// ウィンドウ描画
	UpdateBuffer(&g_BattleBuffer, g_pBattleWindow, WINDOW_WIDTH / 10, WINDOW_HEIGHT / 10);
		
	// ユニット描画
	if (g_pUnit->Team == TEAM_PLAYER)
	{
		UpdateBuffer(&g_BattleBuffer, g_paEnemyMotion[0], WINDOW_WIDTH / 10 + 50, WINDOW_HEIGHT / 10 + 50);
		UpdateBuffer(&g_BattleBuffer, g_paPlayerMotion[g_nFlameCnt], WINDOW_WIDTH / 10 + 150, WINDOW_HEIGHT / 10 + 50);
		SetNum(g_pUnit->Job.nAtk, WINDOW_WIDTH / 10 + 140, WINDOW_HEIGHT / 10 + 30);
	}
	else
	{
		UpdateBuffer(&g_BattleBuffer, g_paEnemyMotion[g_nFlameCnt], WINDOW_WIDTH / 10 + 50, WINDOW_HEIGHT / 10 + 50);
		UpdateBuffer(&g_BattleBuffer, g_paPlayerMotion[0], WINDOW_WIDTH / 10 + 150, WINDOW_HEIGHT / 10 + 50);
		SetNum(g_pUnit->Job.nAtk, WINDOW_WIDTH / 10 + 140, WINDOW_HEIGHT / 10 + 30);
	}
	CombineBuffer(&g_BattleBuffer);
}

void EndBattle(void)
{

}

void Battle(UNIT *pUnit)
{
	//===== 変数宣言 =====
	int i;
	int nDefx, nDefy;

	UNIT *pUnit2;
	
	//===== 初期化処理 =====
	if (pUnit->Team == TEAM_PLAYER)
	{
		pUnit2 = GetEnemyUnit();
	}
	else
	{
		pUnit2 = GetPlayerUnit();
	}

	//===== 更新処理 =====
	for (i = 0; i < MAX_ENEMY_UNIT_NUM; i++, pUnit2++)
	{
		if (!pUnit2->bExist)	continue;	// 存在しなければ門前払い

		nDefx = pUnit->nPosX - pUnit2->nPosX;
		nDefy = pUnit->nPosY - pUnit2->nPosY;
		if (nDefx < 0) nDefx = -nDefx;
		if (nDefy < 0) nDefy = -nDefy;

		if (nDefx + nDefy > pUnit->Job.nAtkRange)	continue;	// 射程外なら門前払い

		g_pUnit = pUnit;
		g_pUnit2 = pUnit2;
		SetMODE(MODE_BATTLE);
		g_nFlameCnt = 0;
		g_bBattleEnd = false;
		break;
	}
}