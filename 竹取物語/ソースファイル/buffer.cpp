//==========================================
//								  buffer.cpp
//�@�����:AT11B192 No.17 ������G
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
//2020/01/31
// �v���O��������J�n
//2020/02/10
//  �o�b�t�@�̍X�V�E�������֐���
//2020/02/18
// �֐��R�����g�̋L�q
//2020/02/26
// �o�b�t�@�̍���������֐�(CombineBuffer)���C��(���ߐF�ɑΉ�)
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
//===== �C���N���[�h�� =====
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "bitmap.h"
#include "buffer.h"

//===== �O���[�o���ϐ� =====
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
	//===== �ϐ��錾 =====
	int i, j;
	CHAR_INFO *pAttr;

	//===== �����o�̏����� =====
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
	//===== �ϐ��錾 =====
	unsigned int i, j;
	CHAR_INFO *pBufferAttr;
	CHAR_INFO *pImageAttr;

	//===== ���������� =====
	pImageAttr = pImage->cell;
	
	//===== �X�V���� =====
	for (i = 0; i < pImage->height; i++)
	{
		if (y + i < 0 || WINDOW_HEIGHT <= y + i)
		{
			pImageAttr += pImage->width;
			continue;	// �`��͈͊O�Ȃ��O����
		}

		pBufferAttr = &pBuffer->Cell[y + i][x];
		
		for (j = 0; j < pImage->width; j++, pBufferAttr++, pImageAttr++)
		{
			if (x + j < 0 || WINDOW_WIDTH <= x + j)	continue;	// �`��͈͊O�Ȃ��O����
			
			//���ߐF�Ȃ��O����
			if (pImageAttr->Attributes == 16) continue;
			
			//�o�b�t�@���X�V
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
	//===== �ϐ��錾 =====
	int i, j;
	CHAR_INFO *pMainAttr;
	CHAR_INFO *pAttr;

	//===== ���������� =====
	pMainAttr = &g_MainBuffer.Cell[0][0];
	pAttr = &pBuffer->Cell[0][0];

	//===== �X�V���� =====
	for (i = 0; i < WINDOW_HEIGHT; i++)
	{
		for (j = 0; j < WINDOW_WIDTH; j++, pMainAttr++, pAttr++)
		{
			//���ߐF�Ȃ��O����
			if (pAttr->Attributes == 16 << 4) continue;

			//���C���̃o�b�t�@���X�V
			*pMainAttr = *pAttr;
		}
	}

	//===== �㏈�� =====
	for (i = 0, pAttr = &pBuffer->Cell[0][0]; i < WINDOW_HEIGHT; i++)
	{
		for (j = 0; j < WINDOW_WIDTH; j++, pAttr++)
		{
			pAttr->Attributes = 16 << 4;
		}
	}
}
