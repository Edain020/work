//==========================================
//									char.cpp
//�@�����:AT11B192 No.17 ������G
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
//2020/02/29
// �v���O��������J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
//===== �C���N���[�h���@=====
#include <stdio.h>
#include <string.h>
#include "bitmap.h"
#include "buffer.h"
#include "chara.h"

//===== �萔�E�}�N����` =====
#define CHARA_NUM	(153)					// �g���镶���̎��
#define CHARA_FILE	("bmp/Chara.bmp")	// �����f�[�^�̉摜�̃t�@�C����

//===== �v���g�^�C�v�錾 =====
IMAGE* CreateCharaImage(int height, int width);
int CheckCharaByte(char);

//===== �O���[�o���ϐ� =====
BUFFER g_CharaBuffer;
IMAGE *g_pCharaImage;
IMAGE *g_paCharaImage[CHARA_NUM];

void InitChara(void)
{
	//===== �ϐ��錾 =====
	int nCharanum, x, y;
	CHAR_INFO *pCell;

	//===== ���������� =====
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
	//===== �ϐ��錾 =====
	int i;
	int nStringLength;
	int nCharaNum;
	char szChara[100];
	char cSampleCode[3] = "��";
	char *pChara;

	//===== ���������� =====
	pChara = szChara;
	strcpy(szChara, String);
	nStringLength = strlen(szChara);

	//===== �X�V���� =====
	for (i = 0; i < nStringLength && *pChara != '\0'; i++)
	{
		if (CheckCharaByte(*pChara))	//2byte����
		{
			pChara++;
			nCharaNum = *pChara - cSampleCode[1] + 62;
		}
		else							//1byte����
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
	//===== �ϐ��錾 =====
	int i;
	int nNum;
	int nDigit;

	//===== ���������� =====
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

	//===== �X�V���� =====
	for (nDigit += i - 1; i > 0; i--, nDigit--, nNum /= 10)
	{
		UpdateBuffer(&g_CharaBuffer, g_paCharaImage[nNum % 10], x + (CHARA_SIZE * 2) * nDigit, y);
	}
}

// --------------------------------------
//�֐����FCreateCharImage
//���@���Fint, int (�ۑ��������̈�̑傫��(�����A����))
//�߂�l�FIMAGE* (�m�ۂ����̈�̃|�C���^)
//���@�e�F�w�肳�ꂽ�傫���̕����̃f�[�^��
//			�ۑ����邽�߂̃������̈���m�ۂ���
//--------------------------------------
IMAGE* CreateCharaImage(int height, int width)
{
	//===== �ϐ��錾 =====
	IMAGE *img;

	//----- �������̈�̊m�� -----
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

	//===== ���������� =====
	img->width  = width;
	img->height = height;

	//===== �㏈�� =====
	return img;
}

// --------------------------------------
//�֐����FCheckCharaByte
//���@���Fchar (���肵���������̕����R�[�h)
//�߂�l�Fint (�o�C�g���@0:1byte 1:2byte)
//���@�e�F�w�肵��������1byte������2byte�������𔻒肷��
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