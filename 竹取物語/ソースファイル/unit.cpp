//------------------------------------------
//									unit.cpp
//　制作者:AT11B192 No.17 小畠大季
//更新履歴～～～～～～～～～～～～～～～～～
//2020/02/28
// プログラム制作開始
//～～～～～～～～～～～～～～～～～～～～～
//===== インクルード部 =====
#include <string.h>
#define CONIOEX
#include "conioex.h"
#include "unit.h"

//===== グローバル変数 =====
JOB_INFO g_JobInfo[JOB_MAX] = {	// ジョブデータ
	{JOB_SWORDMAN, 100, 50, 30, 5, 1},
	{JOB_SPEARMAN, 150, 40, 20, 6, 2},
	{JOB_BOWMAN  ,  70, 30, 10, 6, 3},
};	//ジョブ名　　Life,Atk,Def,Mov,Range

void InitUnit(UNIT *pUnit, const char *szName, JOB Job)
{
	//===== 初期化処理 =====
	strcpy(pUnit->szName, szName);	// 名前の設定
	pUnit->Job = g_JobInfo[Job];	// ステータスの設定
	pUnit->nLife = pUnit->Job.nMaxLife;
	pUnit->bExist = true;
	pUnit->bAction = false;
	pUnit->nAnimeNum = 0;
	pUnit->nAnimeCnt = rand() % UNIT_ANIME_DELAY;
}