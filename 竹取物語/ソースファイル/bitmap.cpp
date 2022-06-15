//==========================================
//								  bitmap.cpp
//�@�����:AT11B192 No.17 ������G
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
//2020/02/07
// �v���O��������J�n
//2020/02/10
// RGB�f�[�^����16�F�֕ϊ�����֐����쐬
//2020/02/17
// RGB�f�[�^����̕ϊ��̊֐����s�^�S���X�̒藝���g���������ɕύX
// �r�b�g�}�b�v�t�@�C����ǂݍ��ݎ��ɃT�C�Y��ύX�\��
//2020/02/18
// �֐��R�����g�̋L�q
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

//===== �C���N���[�h�� =====
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"

//===== �萔�E�}�N����` =====
#define MAX_COLOR_NUM	(16)	// �g����F�̎��

//===== �v���g�^�C�v�錾 =====
IMAGE *Create_Image(int, int);
void ColorConversion(IMAGE*);
int sqrt(int);

//===== �O���[�o���ϐ� =====
RGB g_ColorPalette[MAX_COLOR_NUM] = {	// �J���[�p���b�g��RGB
	{   0,   0,   0}, { 255, 255, 255 }, { 106,  76,  12 }, {  69,  13, 184 },
	{  19, 255, 246}, { 255,   0,  16 }, { 246, 255,   0 }, {  15, 169,  10 },
	{ 159, 159, 159}, { 255, 175,  40 }, {  79, 254,   5 }, { 250, 219, 159 },
	{  43,  37,  89}, { 102,  37,  89 }, {  82,  82,  82 }, { 142, 227, 231 },
};

//���ߐF
RGB g_InvisibleColor = { 100, 100, 100 };

IMAGE *Read_Bmp(const char *filename, unsigned int height, unsigned int width)
{
	//===== �ϐ��錾 =====
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

	//----- �t�@�C���I�[�v�� -----
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		fprintf(stderr, "Error: %s could not read.", filename);
		return NULL;
	}

	// �r�b�g�}�b�v�̃f�[�^���ǂ����̊m�F
	fread(header_buf, sizeof(unsigned char), HEADERSIZE, fp);
	if (strncmp(header_buf, "BM", 2))
	{
		fprintf(stderr, "Error: %s is not Bitmap file.", filename);
		return NULL;
	}

	// �摜�̏����擾
	memcpy(&nWidth,  header_buf + 18, sizeof(nWidth));		//�摜�̒����̏����擾
	memcpy(&nHeight, header_buf + 22, sizeof(nHeight));		//�摜�̍����̏����擾
	memcpy(&color,  header_buf + 28, sizeof(unsigned int));	//�摜�̐F�̏����擾

	// 24bit�J���[���ǂ����̊m�F
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

	// �K�v�ȃT�C�Y�̗̈���m��
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
	
	// �F�̃f�[�^��ۑ�
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

	// �摜�̃T�C�Y�ϊ��̔䗦��ݒ�
	fWidthRatio  = (float)nWidth  / width;
	fHeightRatio = (float)nHeight / height;
	
	for (i = 0; i < height; i++)
	{
		for (j = 0; j < width; j++)
		{
			img2->data[i * width + j] = img->data[((int)(i * fHeightRatio) * nWidth) + (int)(j * fWidthRatio)];
		}
	}

	// �F�̃f�[�^��ϊ�
	ColorConversion(img2);

	//===== �㏈�� =====
	free(bmp_line_data);
	Free_Image(img);

	//----- �t�@�C���N���[�Y -----
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
//�֐����FCreate_Image
//���@���Fint, int (�ۑ��������̈�̑傫��(�����A����))
//�߂�l�FIMAGE* (�m�ۂ����̈�̃|�C���^)
//���@�e�F�w�肳�ꂽ�傫���̃r�b�g�}�b�v�f�[�^��
//			�ۑ����邽�߂̃������̈���m�ۂ���
//--------------------------------------
IMAGE *Create_Image(int height, int width)
{
	//===== �ϐ��錾 =====
	IMAGE *img;

	//----- �������̈�̊m�� -----
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

	//===== ���������� =====
	img->width  = width;
	img->height = height;

	//===== �I������ =====
	return img;
}

//--------------------------------------
//�֐����FColorConversion
//���@���FIMAGE* (�F�̏���ϊ��������r�b�g�}�b�v�f�[�^)
//�߂�l�F�Ȃ�
//���@�e�F�w�肳�ꂽ�r�b�g�}�b�v�f�[�^�̐F����
//			RGB����J���[�p���b�g�̔ԍ��ɕϊ�����
//--------------------------------------
void ColorConversion(IMAGE *img)
{
	//===== �ϐ��錾 =====
	unsigned int x, y;
	unsigned char i;
	unsigned char r, g, b;
	unsigned char nColorNum;
	RGB *pData;
	CHAR_INFO *pCell;

	//===== ���������� =====
	pData = img->data;
	pCell = img->cell;

	// RGB�f�[�^���R���\�[���̃p���b�g�i���o�[�ɕϊ�
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

	//===== �㏈�� =====
	free(img->data);
}

//--------------------------------------
//�֐����Fsqrt
//���@���Fint (��悵�������l)
//�߂�l�Fint (��悵�����l)
//���@�e�F�w�肳�ꂽ���l�̓���Ԃ�
//--------------------------------------
int sqrt(int n)
{
	return (n * n);
}
