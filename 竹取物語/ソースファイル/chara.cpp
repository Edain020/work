//==========================================
//									char.cpp
//　制作者:AT11B192 No.17 小畠大季
//～～～～～～～～更新履歴～～～～～～～～～
//2020/02/29
// プログラム制作開始
//～～～～～～～～～～～～～～～～～～～～～
//===== インクルード部　=====
#include <stdio.h>
#include <string.h>
#include "bitmap.h"
#include "buffer.h"
#include "chara.h"

//===== 定数・マクロ定義 =====
#define CHARA_NUM	(153)					// 使える文字の種類
#define CHARA_FILE	("bmp/Chara.bmp")	// 文字データの画像のファイル名

//===== プロトタイプ宣言 =====
IMAGE* CreateCharaImage(int height, int width);
int CheckCharaByte(char);

//===== グローバル変数 =====
BUFFER g_CharaBuffer;
IMAGE *g_pCharaImage;
IMAGE *g_paCharaImage[CHARA_NUM];

void InitChara(void)
{
	//===== 変数宣言 =====
	int nCharanum, x, y;
	CHAR_INFO *pCell;

	//===== 初期化処理 =====
	InitBuffer(&g_CharaBuffer);
	g_pCharaImage = Read_Bmp(CHARA_FILE, CHARA_SIZE, CHARA_SIZE * 2 * CHARA_NUM);
	for (nCharanum = 0; nCharanum < CHARA_NUM; nCharanum++)
	{
		g_paCharaImage[nCharanum] = CreateCharaImage(CHARA_SIZE, CHARA_SIZE * 2);
		pCell = g_paCharaImage[nCharanum]->cell;
		for (y = 0; y < CHARA_SIZE; y++)
		{
			for (x = 0; x < CHARA_SIZE * 2; x++, pCell++)
			{
				*pCell = g_pCharaImage->cell[(CHARA_SIZE * 2 * CHARA_NUM * y) + ((CHARA_SIZE * 2 * nCharanum) + x)];
			}
		}
	}
}

void DrawChara(void)
{
	CombineBuffer(&g_CharaBuffer);
}

void EndChara(void)
{

}

void SetChara(const char *String, int x, int y, int space)
{
	//===== 変数宣言 =====
	int i;
	int nStringLength;
	int nCharaNum;
	char szChara[100];
	char cSampleCode[3] = "ぁ";
	char *pChara;

	//===== 初期化処理 =====
	pChara = szChara;
	strcpy(szChara, String);
	nStringLength = strlen(szChara);

	//===== 更新処理 =====
	for (i = 0; i < nStringLength && *pChara != '\0'; i++)
	{
		if (CheckCharaByte(*pChara))	//2byte文字
		{
			pChara++;
			nCharaNum = *pChara - cSampleCode[1] + 62;
		}
		else							//1byte文字
		{
			if (*pChara >= '0' && '9' >= *pChara)		nCharaNum = *pChara - '0';
			else if (*pChara >= 'A' && 'Z' >= *pChara)	nCharaNum = *pChara - 'A' + 10;
			else if (*pChara >= 'a' && 'z' >= *pChara)	nCharaNum = *pChara - 'a' + 36;
			else if (*pChara == '!')					nCharaNum = 145;
			else if (*pChara == '?')					nCharaNum = 146;
			else if (*pChara == '+')					nCharaNum = 147;
			else if (*pChara == '-')					nCharaNum = 148;
			else if (*pChara == '*')					nCharaNum = 149;
			else if (*pChara == '/')					nCharaNum = 150;
			else if (*pChara == '=')					nCharaNum = 151;
			else if (*pChara == ':')					nCharaNum = 152;
		}

		UpdateBuffer(&g_CharaBuffer, g_paCharaImage[nCharaNum], x + (CHARA_SIZE * 2 + space) * i, y);
		pChara++;
	}
}

void SetNum(int num, int x, int y)
{
	//===== 変数宣言 =====
	int i;
	int nNum;
	int nDigit;

	//===== 初期化処理 =====
	nDigit = 0;
	for (nNum = num, i = 0; nNum; nNum /= 10, i++);
	if (num < 0)
	{
		UpdateBuffer(&g_CharaBuffer, g_paCharaImage[148], x + (CHARA_SIZE * 2) * nDigit, y);
		nDigit++;
		nNum = -num;
	}
	else if (num == 0)	UpdateBuffer(&g_CharaBuffer, g_paCharaImage[num], x + (CHARA_SIZE * 2) * nDigit, y);
	else nNum = num;

	//===== 更新処理 =====
	for (nDigit += i - 1; i > 0; i--, nDigit--, nNum /= 10)
	{
		UpdateBuffer(&g_CharaBuffer, g_paCharaImage[nNum % 10], x + (CHARA_SIZE * 2) * nDigit, y);
	}
}

// --------------------------------------
//関数名：CreateCharImage
//引　数：int, int (保存したい領域の大きさ(高さ、長さ))
//戻り値：IMAGE* (確保した領域のポインタ)
//内　容：指定された大きさの文字のデータを
//			保存するためのメモリ領域を確保する
//--------------------------------------
IMAGE* CreateCharaImage(int height, int width)
{
	//===== 変数宣言 =====
	IMAGE *img;

	//----- メモリ領域の確保 -----
	if ((img = (IMAGE *)malloc(sizeof(IMAGE))) == NULL)
	{
		fprintf(stderr, "Allocation error\n");
		return NULL;
	}
	if ((img->cell = (CHAR_INFO*)malloc(sizeof(CHAR_INFO) * width * height)) == NULL)
	{
		fprintf(stderr, "Allocation error\n");
		Free_Image(img);
		return NULL;
	}

	//===== 初期化処理 =====
	img->width  = width;
	img->height = height;

	//===== 後処理 =====
	return img;
}

// --------------------------------------
//関数名：CheckCharaByte
//引　数：char (判定したい文字の文字コード)
//戻り値：int (バイト数　0:1byte 1:2byte)
//内　容：指定した文字が1byte文字か2byte文字かを判定する
//--------------------------------------
int CheckCharaByte(char chara)
{
	if (chara & 0x80)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}