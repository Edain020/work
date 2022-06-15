//==========================================
//								  buffer.cpp
//　制作者:AT11B192 No.17 小畠大季
//～～～～～～～～更新履歴～～～～～～～～～
//2020/01/31
// プログラム制作開始
//2020/02/10
//  バッファの更新・合成を関数化
//2020/02/18
// 関数コメントの記述
//2020/02/26
// バッファの合成をする関数(CombineBuffer)を修正(透過色に対応)
//～～～～～～～～～～～～～～～～～～～～～
//===== インクルード部 =====
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include "buffer.h"

//===== グローバル変数 =====
BUFFER g_MainBuffer;

void InitMainBuffer(void)
{
	g_MainBuffer.Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	g_MainBuffer.BufferSize = { WINDOW_WIDTH,WINDOW_HEIGHT };
	g_MainBuffer.Start_Coord = { 0,0 };
	g_MainBuffer.SR = { 0,0,WINDOW_WIDTH - 1,WINDOW_HEIGHT - 1 };
	memset(g_MainBuffer.Cell, 0, sizeof(g_MainBuffer.Cell));
}

void InitBuffer(BUFFER *pBuffer)
{
	//===== 変数宣言 =====
	int i, j;
	CHAR_INFO *pAttr;

	//===== メンバの初期化 =====
	pBuffer->Handle = GetStdHandle(STD_OUTPUT_HANDLE);
	pBuffer->BufferSize = { WINDOW_WIDTH,WINDOW_HEIGHT };
	pBuffer->Start_Coord = { 0,0 };
	pBuffer->SR = { 0,0,WINDOW_WIDTH - 1,WINDOW_HEIGHT - 1 };
	memset(pBuffer->Cell, 0, sizeof(pBuffer->Cell));
	for (i = 0, pAttr = &pBuffer->Cell[0][0]; i < WINDOW_HEIGHT; i++)
	{
		for (j = 0; j < WINDOW_WIDTH; j++, pAttr++)
		{
			pAttr->Attributes = 16 << 4;
		}
	}
}

void UpdateBuffer(BUFFER *pBuffer, IMAGE *pImage, int x, int y)
{
	//===== 変数宣言 =====
	unsigned int i, j;
	CHAR_INFO *pBufferAttr;
	CHAR_INFO *pImageAttr;

	//===== 初期化処理 =====
	pImageAttr = pImage->cell;
	
	//===== 更新処理 =====
	for (i = 0; i < pImage->height; i++)
	{
		if (y + i < 0 || WINDOW_HEIGHT <= y + i)
		{
			pImageAttr += pImage->width;
			continue;	// 描画範囲外なら門前払い
		}

		pBufferAttr = &pBuffer->Cell[y + i][x];
		
		for (j = 0; j < pImage->width; j++, pBufferAttr++, pImageAttr++)
		{
			if (x + j < 0 || WINDOW_WIDTH <= x + j)	continue;	// 描画範囲外なら門前払い
			
			//透過色なら門前払い
			if (pImageAttr->Attributes == 16) continue;
			
			//バッファを更新
			pBufferAttr->Attributes = pImageAttr->Attributes << 4;
		}
	}
}

void DrawBuffer(void)
{
	WriteConsoleOutput(g_MainBuffer.Handle, (CHAR_INFO*)g_MainBuffer.Cell, g_MainBuffer.BufferSize, g_MainBuffer.Start_Coord, &g_MainBuffer.SR);
	memset(g_MainBuffer.Cell, 0, sizeof(g_MainBuffer.Cell));
}

void EndBuffer(void)
{
}

void CombineBuffer(BUFFER *pBuffer)
{
	//===== 変数宣言 =====
	int i, j;
	CHAR_INFO *pMainAttr;
	CHAR_INFO *pAttr;

	//===== 初期化処理 =====
	pMainAttr = &g_MainBuffer.Cell[0][0];
	pAttr = &pBuffer->Cell[0][0];

	//===== 更新処理 =====
	for (i = 0; i < WINDOW_HEIGHT; i++)
	{
		for (j = 0; j < WINDOW_WIDTH; j++, pMainAttr++, pAttr++)
		{
			//透過色なら門前払い
			if (pAttr->Attributes == 16 << 4) continue;

			//メインのバッファを更新
			*pMainAttr = *pAttr;
		}
	}

	//===== 後処理 =====
	for (i = 0, pAttr = &pBuffer->Cell[0][0]; i < WINDOW_HEIGHT; i++)
	{
		for (j = 0; j < WINDOW_WIDTH; j++, pAttr++)
		{
			pAttr->Attributes = 16 << 4;
		}
	}
}
