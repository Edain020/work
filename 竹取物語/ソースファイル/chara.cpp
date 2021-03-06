//==========================================
//									char.cpp
//@§ìÒ:AT11B192 No.17 ¬©åG
//````````XVð`````````
//2020/02/29
// vO§ìJn
//`````````````````````
//===== CN[h@=====
#include <stdio.h>
#include <string.h>
#include "bitmap.h"
#include "buffer.h"
#include "chara.h"

//===== èE}Nè` =====
#define CHARA_NUM	(153)					// g¦é¶ÌíÞ
#define CHARA_FILE	("bmp/Chara.bmp")	// ¶f[^ÌæÌt@C¼

//===== vg^Cvé¾ =====
IMAGE* CreateCharaImage(int height, int width);
int CheckCharaByte(char);

//===== O[oÏ =====
BUFFER g_CharaBuffer;
IMAGE *g_pCharaImage;
IMAGE *g_paCharaImage[CHARA_NUM];

void InitChara(void)
{
	//===== Ïé¾ =====
	int nCharanum, x, y;
	CHAR_INFO *pCell;

	//===== ú» =====
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
	//===== Ïé¾ =====
	int i;
	int nStringLength;
	int nCharaNum;
	char szChara[100];
	char cSampleCode[3] = "";
	char *pChara;

	//===== ú» =====
	pChara = szChara;
	strcpy(szChara, String);
	nStringLength = strlen(szChara);

	//===== XV =====
	for (i = 0; i < nStringLength && *pChara != '\0'; i++)
	{
		if (CheckCharaByte(*pChara))	//2byte¶
		{
			pChara++;
			nCharaNum = *pChara - cSampleCode[1] + 62;
		}
		else							//1byte¶
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
	//===== Ïé¾ =====
	int i;
	int nNum;
	int nDigit;

	//===== ú» =====
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

	//===== XV =====
	for (nDigit += i - 1; i > 0; i--, nDigit--, nNum /= 10)
	{
		UpdateBuffer(&g_CharaBuffer, g_paCharaImage[nNum % 10], x + (CHARA_SIZE * 2) * nDigit, y);
	}
}

// --------------------------------------
//Ö¼FCreateCharImage
//ø@Fint, int (Û¶µ½¢ÌæÌå«³(³A·³))
//ßèlFIMAGE* (mÛµ½ÌæÌ|C^)
//à@eFwè³ê½å«³Ì¶Ìf[^ð
//			Û¶·é½ßÌÌæðmÛ·é
//--------------------------------------
IMAGE* CreateCharaImage(int height, int width)
{
	//===== Ïé¾ =====
	IMAGE *img;

	//----- ÌæÌmÛ -----
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

	//===== ú» =====
	img->width  = width;
	img->height = height;

	//===== ã =====
	return img;
}

// --------------------------------------
//Ö¼FCheckCharaByte
//ø@Fchar (»èµ½¢¶Ì¶R[h)
//ßèlFint (oCg@0:1byte 1:2byte)
//à@eFwèµ½¶ª1byte¶©2byte¶©ð»è·é
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