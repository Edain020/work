//------------------------------------------
//								  window.cpp
//�@�����:AT11B192 No.17 ������G
//�X�V�����`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
//2020/03/01
// �v���O��������J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
//===== �C���N���[�h�� =====
#include "bitmap.h"
#include "buffer.h"
#include "window.h"
#include "chara.h"
#include "cursor.h"
#include "field.h"
#include "unit.h"
#include "player.h"
#include "enemy.h"

//===== �萔�E�}�N����` =====
#define TERRAIN_WINDOW_FILE		("bmp/TerrainWindow.bmp")	// �n�`���E�B���h�E�̉摜�̃t�@�C����
#define CIRCLE_FILE				("bmp/Circle.bmp")			// ���̉摜�̃t�@�C����
#define CROSS_FILE				("bmp/Cross.bmp")			// �~�̉摜�̃t�@�C����
#define UNIT_WINDOW_FILE		("bmp/UnitWindow.bmp")		// ���j�b�g�E�B���h�E�̉摜�̃t�@�C����
#define TERRAIN_WINDOW_RIGHT_X	(WINDOW_WIDTH - TERRAIN_WINDOW_WIDTH)	// �n�`���E�B���h�E���E���ɕ\������ꍇ�̍��W
#define TERRAIN_STRING_Y_1		(3)		// �n�`���E�B���h�E��1�s�ڂ̕�����\�����鍂��
#define TERRAIN_STRING_Y_2		(15)	// �n�`���E�B���h�E��2�s�ڂ̕�����\�����鍂��
#define TERRAIN_STRING_X		(10)	// �n�`���E�B���h�E�̕�����\�����n�߂�X���W
#define TERRAIN_STRING_SPACE	(5)		// �n�`���E�B���h�E�̕����ƕ����̊Ԋu
#define UNIT_WINDOW_Y			(WINDOW_HEIGHT - UNIT_WINDOW_HEIGHT)	// ���j�b�g�E�B���h�E��\������Y���W
#define UNIT_WINDOW_RIGHT_X		(WINDOW_WIDTH - UNIT_WINDOW_WIDTH)		// ���j�b�g�E�B���h�E���E���ɕ\������ꍇ��X���W
#define UNIT_NAME_X				(CHARA_SIZE * 2)		// ���j�b�g�E�B���h�E�Ƀ��j�b�g�̖��O��\�����n�߂�X���W
#define UNIT_STRING_X_1			(5)						// ���j�b�g�E�B���h�E�̕�����\�����n�߂�X���W(����)
#define UNIT_STRING_X_2			(UNIT_STRING_X_1 + 100)	// ���j�b�g�E�B���h�E�̕�����\�����n�߂�X���W(�E��)
#define UNIT_STRING_X_3			(UNIT_STRING_X_2 + 70)	// ���j�b�g�E�B���h�E�̕�����\�����n�߂�X���W(MaxLife)
#define UNIT_SLASH_X			(UNIT_STRING_X_2 + 56)	// ���j�b�g�E�B���h�E��Life����/��\������X���W
#define UNIT_STRING_Y_1			(UNIT_WINDOW_Y + 3)		// ���j�b�g�E�B���h�E��1�s�ڂ̕�����\�����n�߂�Y���W
#define UNIT_STRING_Y_2			(UNIT_STRING_Y_1 + 12)	// ���j�b�g�E�B���h�E��2�s�ڂ̕�����\�����n�߂�Y���W
#define UNIT_STRING_Y_3			(UNIT_STRING_Y_2 + 12)	// ���j�b�g�E�B���h�E��3�s�ڂ̕�����\�����n�߂�Y���W
#define UNIT_STRING_Y_4			(UNIT_STRING_Y_3 + 12)	// ���j�b�g�E�B���h�E��4�s�ڂ̕�����\�����n�߂�Y���W
#define UNIT_STRING_Y_5			(UNIT_STRING_Y_4 + 12)	// ���j�b�g�E�B���h�E��5�s�ڂ̕�����\�����n�߂�Y���W
#define UNIT_STRING_Y_6			(UNIT_STRING_Y_5 + 12)	// ���j�b�g�E�B���h�E��6�s�ڂ̕�����\�����n�߂�Y���W
#define UNIT_STRING_SPACE		(0)		// ���j�b�g�E�B���h�E�̕����ƕ����̊Ԋu

//===== �O���[�o���ϐ� =====
BUFFER g_WindowBuffer;
IMAGE *g_pTerrainWindowImage;
IMAGE *g_pCircleImage;
IMAGE *g_pCrossImage;
IMAGE *g_pUnitWindowImage;
bool g_bCursorLeft;

void InitWindow(void)
{
	InitBuffer(&g_WindowBuffer);
	g_pTerrainWindowImage = Read_Bmp(TERRAIN_WINDOW_FILE, TERRAIN_WINDOW_HEIGHT, TERRAIN_WINDOW_WIDTH);
	g_pCircleImage = Read_Bmp(CIRCLE_FILE, CHARA_SIZE, CHARA_SIZE * 2);
	g_pCrossImage  = Read_Bmp(CROSS_FILE , CHARA_SIZE, CHARA_SIZE * 2);
	g_pUnitWindowImage = Read_Bmp(UNIT_WINDOW_FILE, UNIT_WINDOW_HEIGHT, UNIT_WINDOW_WIDTH);
	g_bCursorLeft = false;
}

void UpdateWindow(void)
{
	//===== �ϐ��錾 =====
	CURSOR *pCursor;
	UNIT *pUnit;
	int nFieldBufferX, nFieldBufferY;

	//===== ���������� =====
	pCursor = GetCursor_DK();
	nFieldBufferX = GetFieldBufferX();
	nFieldBufferY = GetFieldBufferY();

	//===== �X�V���� =====
	if (pCursor->Pos.X < FIELD_BUFFER_WIDTH / 2)	g_bCursorLeft = true;
	else											g_bCursorLeft = false;
	
	if (g_bCursorLeft)
	{
		UpdateBuffer(&g_WindowBuffer, g_pTerrainWindowImage, WINDOW_WIDTH - TERRAIN_WINDOW_WIDTH, 0);
		SetChara(GetTerrainInfo(pCursor->Pos.X + nFieldBufferX, pCursor->Pos.Y + nFieldBufferY)->TerrainName, TERRAIN_WINDOW_RIGHT_X + TERRAIN_STRING_X, TERRAIN_STRING_Y_1, TERRAIN_STRING_SPACE);
		SetChara("���ǂ�:", TERRAIN_WINDOW_RIGHT_X + TERRAIN_STRING_X, TERRAIN_STRING_Y_2,0);
		if (GetTerrainInfo(pCursor->Pos.X + nFieldBufferX, pCursor->Pos.Y + nFieldBufferY)->nPassCost > 0)	UpdateBuffer(&g_WindowBuffer, g_pCircleImage, TERRAIN_WINDOW_RIGHT_X + TERRAIN_STRING_X + CHARA_SIZE * 2 * 4, TERRAIN_STRING_Y_2);
		else																								UpdateBuffer(&g_WindowBuffer, g_pCrossImage , TERRAIN_WINDOW_RIGHT_X + TERRAIN_STRING_X + CHARA_SIZE * 2 * 4, TERRAIN_STRING_Y_2);
		
		switch(GetFieldxy(pCursor->Pos.X + nFieldBufferX, pCursor->Pos.Y + nFieldBufferY)->UnitType)
		{
		case FIELD_UNIT_NONE:	return;
		case FIELD_UNIT_PLAYER:	UpdateBuffer(&g_WindowBuffer, g_pUnitWindowImage, UNIT_WINDOW_RIGHT_X, UNIT_WINDOW_Y);
								pUnit = GetPlayerUnit();
								break;
		case FIELD_UNIT_ENEMY:	UpdateBuffer(&g_WindowBuffer, g_pUnitWindowImage, UNIT_WINDOW_RIGHT_X, UNIT_WINDOW_Y);
								pUnit = GetEnemyUnit();
								break;
		default:
			break;
		}
		while (pUnit->nPosY != pCursor->Pos.Y + nFieldBufferY || pUnit->nPosX != pCursor->Pos.X + nFieldBufferX)	pUnit++;

		SetChara(pUnit->szName, UNIT_WINDOW_RIGHT_X + UNIT_NAME_X                     , UNIT_STRING_Y_1, 0);
		SetChara("�����߂�:"  , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_1                 , UNIT_STRING_Y_2, 0);	SetNum(pUnit->nLife        , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_2, UNIT_STRING_Y_2);
		SetChara("/"          , UNIT_WINDOW_RIGHT_X + UNIT_SLASH_X                    , UNIT_STRING_Y_2, 0);	SetNum(pUnit->Job.nMaxLife , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_3, UNIT_STRING_Y_2);
		SetChara("��������:"  , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_1                 , UNIT_STRING_Y_3, 0);	SetNum(pUnit->Job.nAtk     , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_2, UNIT_STRING_Y_3);
		SetChara("�ڂ�����:"  , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_1                 , UNIT_STRING_Y_4, 0);	SetNum(pUnit->Job.nDef     , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_2, UNIT_STRING_Y_4);
		SetChara(  "���ǂ�:"  , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_1 + CHARA_SIZE * 2, UNIT_STRING_Y_5, 0);	SetNum(pUnit->Job.nMove    , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_2, UNIT_STRING_Y_5);
		SetChara("����Ă�:"  , UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_1                 , UNIT_STRING_Y_6, 0);	SetNum(pUnit->Job.nAtkRange, UNIT_WINDOW_RIGHT_X + UNIT_STRING_X_2, UNIT_STRING_Y_6);
	}
	else
	{
		UpdateBuffer(&g_WindowBuffer, g_pTerrainWindowImage, 0, 0);
		SetChara(GetTerrainInfo(pCursor->Pos.X + nFieldBufferX, pCursor->Pos.Y + nFieldBufferY)->TerrainName, TERRAIN_STRING_X, TERRAIN_STRING_Y_1, TERRAIN_STRING_SPACE);
		SetChara("���ǂ�:", TERRAIN_STRING_X, TERRAIN_STRING_Y_2, 0);
		if (GetTerrainInfo(pCursor->Pos.X + nFieldBufferX, pCursor->Pos.Y + nFieldBufferY)->nPassCost > 0)	UpdateBuffer(&g_WindowBuffer, g_pCircleImage, TERRAIN_STRING_X + CHARA_SIZE * 2 * 4, TERRAIN_STRING_Y_2);
		else																								UpdateBuffer(&g_WindowBuffer, g_pCrossImage , TERRAIN_STRING_X + CHARA_SIZE * 2 * 4, TERRAIN_STRING_Y_2);
	
		switch (GetFieldxy(pCursor->Pos.X + nFieldBufferX, pCursor->Pos.Y + nFieldBufferY)->UnitType)
		{
		case FIELD_UNIT_NONE:	return;
		case FIELD_UNIT_PLAYER:	UpdateBuffer(&g_WindowBuffer, g_pUnitWindowImage, 0, UNIT_WINDOW_Y);
			pUnit = GetPlayerUnit();
			break;
		case FIELD_UNIT_ENEMY:	UpdateBuffer(&g_WindowBuffer, g_pUnitWindowImage, 0, UNIT_WINDOW_Y);
			pUnit = GetEnemyUnit();
			break;
		default:
			break;
		}
		while (pUnit->nPosY != pCursor->Pos.Y + nFieldBufferY || pUnit->nPosX != pCursor->Pos.X + nFieldBufferX)	pUnit++;

		SetChara(pUnit->szName, UNIT_NAME_X                     , UNIT_STRING_Y_1, 0);
		SetChara("�����߂�:"  , UNIT_STRING_X_1                 , UNIT_STRING_Y_2, 0);	SetNum(pUnit->nLife        , UNIT_STRING_X_2, UNIT_STRING_Y_2);
		SetChara("/"          , UNIT_SLASH_X                    , UNIT_STRING_Y_2, 0);	SetNum(pUnit->Job.nMaxLife , UNIT_STRING_X_3, UNIT_STRING_Y_2);
		SetChara("��������:"  , UNIT_STRING_X_1                 , UNIT_STRING_Y_3, 0);	SetNum(pUnit->Job.nAtk     , UNIT_STRING_X_2, UNIT_STRING_Y_3);
		SetChara("�ڂ�����:"  , UNIT_STRING_X_1                 , UNIT_STRING_Y_4, 0);	SetNum(pUnit->Job.nDef     , UNIT_STRING_X_2, UNIT_STRING_Y_4);
		SetChara(  "���ǂ�:"  , UNIT_STRING_X_1 + CHARA_SIZE * 2, UNIT_STRING_Y_5, 0);	SetNum(pUnit->Job.nMove    , UNIT_STRING_X_2, UNIT_STRING_Y_5);
		SetChara("����Ă�:"  , UNIT_STRING_X_1                 , UNIT_STRING_Y_6, 0);	SetNum(pUnit->Job.nAtkRange, UNIT_STRING_X_2, UNIT_STRING_Y_6);
	}
}

void DrawWindow(void)
{
	CombineBuffer(&g_WindowBuffer);
}

void EndWindow(void)
{

}
