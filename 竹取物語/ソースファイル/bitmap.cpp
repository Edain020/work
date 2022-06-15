//==========================================
//								  bitmap.cpp
//　制作者:AT11B192 No.17 小畠大季
//～～～～～～～～更新履歴～～～～～～～～～
//2020/02/07
// プログラム制作開始
//2020/02/10
// RGBデータから16色へ変換する関数を作成
//2020/02/17
// RGBデータからの変換の関数をピタゴラスの定理を使った方式に変更
// ビットマップファイルを読み込み時にサイズを変更可能に
//2020/02/18
// 関数コメントの記述
//～～～～～～～～～～～～～～～～～～～～～

//===== インクルード部 =====
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"

//===== 定数・マクロ定義 =====
#define MAX_COLOR_NUM	(16)	// 使える色の種類

//===== プロトタイプ宣言 =====
IMAGE *Create_Image(int, int);
void ColorConversion(IMAGE*);
int sqrt(int);

//===== グローバル変数 =====
RGB g_ColorPalette[MAX_COLOR_NUM] = {	// カラーパレットのRGB
	{   0,   0,   0}, { 255, 255, 255 }, { 106,  76,  12 }, {  69,  13, 184 },
	{  19, 255, 246}, { 255,   0,  16 }, { 246, 255,   0 }, {  15, 169,  10 },
	{ 159, 159, 159}, { 255, 175,  40 }, {  79, 254,   5 }, { 250, 219, 159 },
	{  43,  37,  89}, { 102,  37,  89 }, {  82,  82,  82 }, { 142, 227, 231 },
};

//透過色
RGB g_InvisibleColor = { 100, 100, 100 };

IMAGE *Read_Bmp(const char *filename, unsigned int height, unsigned int width)
{
	//===== 変数宣言 =====
	unsigned int i, j;
	unsigned int real_width;
	unsigned int nWidth, nHeight;
	unsigned int color;
	float fWidthRatio, fHeightRatio;
	FILE *fp;
	char header_buf[HEADERSIZE];
	unsigned char *bmp_line_data;
	IMAGE *img;
	IMAGE *img2;

	//----- ファイルオープン -----
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		fprintf(stderr, "Error: %s could not read.", filename);
		return NULL;
	}

	// ビットマップのデータかどうかの確認
	fread(header_buf, sizeof(unsigned char), HEADERSIZE, fp);
	if (strncmp(header_buf, "BM", 2))
	{
		fprintf(stderr, "Error: %s is not Bitmap file.", filename);
		return NULL;
	}

	// 画像の情報を取得
	memcpy(&nWidth,  header_buf + 18, sizeof(nWidth));		//画像の長さの情報を取得
	memcpy(&nHeight, header_buf + 22, sizeof(nHeight));		//画像の高さの情報を取得
	memcpy(&color,  header_buf + 28, sizeof(unsigned int));	//画像の色の情報を取得

	// 24bitカラーかどうかの確認
	if (color != 24)
	{
		fprintf(stderr, "Error: %s is not 24bit color image", filename);
		return NULL;
	}

	real_width = nWidth*3 + nWidth%4;

	if ((bmp_line_data = (unsigned char *)malloc(sizeof(unsigned char)*real_width)) == NULL)
	{
		fprintf(stderr, "Error: Allocation error.\n");
		return NULL;
	}

	// 必要なサイズの領域を確保
	if ((img = Create_Image(nHeight, nWidth)) == NULL)
	{
		free(bmp_line_data);
		fclose(fp);
		return NULL;
	}
	if ((img2 = Create_Image(height, width)) == NULL)
	{
		free(bmp_line_data);
		fclose(fp);
		return NULL;
	}
	
	// 色のデータを保存
	for (i = 0; i < nHeight; i++)
	{
		fread(bmp_line_data, 1, real_width, fp);
		for (j = 0; j < nWidth; j++)
		{
			img->data[(nHeight - i - 1)*nWidth + j].b = bmp_line_data[j * 3];
			img->data[(nHeight - i - 1)*nWidth + j].g = bmp_line_data[j * 3 + 1];
			img->data[(nHeight - i - 1)*nWidth + j].r = bmp_line_data[j * 3 + 2];
		}
	}

	// 画像のサイズ変換の比率を設定
	fWidthRatio  = (float)nWidth  / width;
	fHeightRatio = (float)nHeight / height;
	
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			img2->data[i * width + j] = img->data[((int)(i * fHeightRatio) * nWidth) + (int)(j * fWidthRatio)];
		}
	}

	// 色のデータを変換
	ColorConversion(img2);

	//===== 後処理 =====
	free(bmp_line_data);
	Free_Image(img);

	//----- ファイルクローズ -----
	fclose(fp);
	
	return img2;
}

void Free_Image(IMAGE *img)
{
	free(img->data);
	free(img->cell);
	free(img);
}

//--------------------------------------
//関数名：Create_Image
//引　数：int, int (保存したい領域の大きさ(高さ、長さ))
//戻り値：IMAGE* (確保した領域のポインタ)
//内　容：指定された大きさのビットマップデータを
//			保存するためのメモリ領域を確保する
//--------------------------------------
IMAGE *Create_Image(int height, int width)
{
	//===== 変数宣言 =====
	IMAGE *img;

	//----- メモリ領域の確保 -----
	if ((img = (IMAGE *)malloc(sizeof(IMAGE))) == NULL)
	{
		fprintf(stderr, "Allocation error\n");
		return NULL;
	}
	if ((img->data = (RGB*)malloc(sizeof(RGB) * width * height)) == NULL)
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

	//===== 終了処理 =====
	return img;
}

//--------------------------------------
//関数名：ColorConversion
//引　数：IMAGE* (色の情報を変換したいビットマップデータ)
//戻り値：なし
//内　容：指定されたビットマップデータの色情報を
//			RGBからカラーパレットの番号に変換する
//--------------------------------------
void ColorConversion(IMAGE *img)
{
	//===== 変数宣言 =====
	unsigned int x, y;
	unsigned char i;
	unsigned char r, g, b;
	unsigned char nColorNum;
	RGB *pData;
	CHAR_INFO *pCell;

	//===== 初期化処理 =====
	pData = img->data;
	pCell = img->cell;

	// RGBデータをコンソールのパレットナンバーに変換
	for (y = 0; y < img->height; y++)
	{
		for (x = 0; x < img->width; x++, pData++, pCell++)
		{
			r = pData->r;
			g = pData->g;
			b = pData->b;

			nColorNum = 0;
			for (i = 1; i < MAX_COLOR_NUM; i++)
			{
				if ((sqrt(r - g_ColorPalette[i].r) + sqrt(g - g_ColorPalette[i].g) + sqrt(b - g_ColorPalette[i].b)) < (sqrt(r - g_ColorPalette[nColorNum].r) + sqrt(g - g_ColorPalette[nColorNum].g) + sqrt(b - g_ColorPalette[nColorNum].b)))
					nColorNum = i;
			}

			if (r == g_InvisibleColor.r && g == g_InvisibleColor.g && b == g_InvisibleColor.b)
			{
				nColorNum = 16;
			}

			pCell->Attributes = nColorNum;
		}
	}

	//===== 後処理 =====
	free(img->data);
}

//--------------------------------------
//関数名：sqrt
//引　数：int (二乗したい数値)
//戻り値：int (二乗した数値)
//内　容：指定された数値の二乗を返す
//--------------------------------------
int sqrt(int n)
{
	return (n * n);
}
