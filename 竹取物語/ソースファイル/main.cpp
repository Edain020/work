//==========================================
//									main.cpp
//	HEW��i����
//�@�����:AT11B192 No.17 ������G
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
//2020/02/21
// �v���O��������J�n
//2020/03/03
// �Q�[���I��p�̏�����ǉ�
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

//===== �C���N���[�h�� =====
#include <Windows.h>
#include "conioex.h"
#include "bitmap.h"
#include "buffer.h"
#include "chara.h"
#include "main.h"
#include "title.h"
#include "field.h"
#include "player.h"
#include "enemy.h"
#include "cursor.h"
#include "window.h"

#include "battle.h"

//===== �萔�E�}�N����` =====
#define FRAME_RATE (1000/30)	// �������s����Ԋu(�~���b)

//===== �O���[�o���ϐ� =====
MODE g_Mode;	// �Q�[���̃��[�h�Ǘ��p
int g_nCountFPS;// FPS�p�J�E���^
BUFFER g_ClearBuffer;
IMAGE *g_pClearImage;

//--------------------------------------
//�֐����Fmain
//���@���F�Ȃ�
//�߂�l�Fint (0:���� 1:���s)
//���@�e�F�v���O�����S�̗̂���𐧌䂷��
//--------------------------------------
int main(void)
{
	//===== �ϐ��錾 =====
	char sTitle[] = GAME_TITLE;
	int nCurrentTime;	// ���ݎ���
	int nExecLastTime;	// �O����s����

	//===== �O���� =====
	setcursortype(NOCURSOR);// �J�[�\�����\��
	setcaption(sTitle);		// �^�C�g��
	timeBeginPeriod(1);		// ���Ԃ̒P�ʂ�ms(�~���b)�ɕύX
	srand(timeGetTime());	// ���ݎ����ŗ������Đ���
	InitBuffer(&g_ClearBuffer);
	g_pClearImage = Read_Bmp("bmp/�c�o���̎q���L.bmp", WINDOW_HEIGHT, WINDOW_HEIGHT * 2);

	//===== ���������� =====
	Init();
	g_Mode = MODE_TITLE;	// �Q�[�����[�h���^�C�g���ɕύX
	nExecLastTime = nCurrentTime = timeGetTime(); // ���ݎ������擾

	do
	{
		nCurrentTime = timeGetTime(); // ���ݎ������擾

		if (nCurrentTime - nExecLastTime >= FRAME_RATE)
		{
			//SetNum(1000 / (nCurrentTime - nExecLastTime), 0, WINDOW_HEIGHT - CHARA_SIZE);
			nExecLastTime = nCurrentTime;

			//===== �X�V���� =====
			Update();

			//===== �`�揈�� =====
			Draw();
		}

	} while (!inport(PK_ESC));

	//===== �I������ =====
	return 0;
}

void Init(void)
{
	InitMainBuffer();
	InitChara();
	InitTitle();
	InitField();
	InitPlayer();
	InitEnemy();
	InitCursor();
	InitWindow();

	InitBattle();
}

void Update(void)
{
	switch (g_Mode)
	{
	case MODE_TITLE:	UpdateTitle();
		break;
	case MODE_PLAYER:	UpdateField();
						UpdatePlayer();
						UpdateEnemy();
						UpdateCursor();
						UpdateWindow();
		break;
	case MODE_MOVEUNIT:	UpdateField();
						UpdatePlayer();
						UpdateEnemy();
						UpdateCursor();
						UpdateWindow();
		break;
	case MODE_BATTLE:	UpdateField();
						UpdatePlayer();
						UpdateEnemy();
						UpdateBattle();
		break;
	case MODE_ENEMY:	UpdateField();
						UpdatePlayer();
						UpdateEnemy();
						UpdateWindow();
		break;
	case MODE_CLEAR:
						UpdateBuffer(&g_ClearBuffer, g_pClearImage, WINDOW_WIDTH / 2 - WINDOW_HEIGHT, 0);
		break;
	default:	break;
	}
}

void Draw(void)
{
	switch (g_Mode)
	{
	case MODE_TITLE:	DrawTitle();
		break;
	case MODE_PLAYER:	DrawField();
						DrawPlayer();
						DrawEnemy();
						DrawCursor();
						DrawWindow();
		break;
	case MODE_MOVEUNIT:	DrawField();
						DrawPlayer();
						DrawEnemy();
						DrawCursor();
						DrawWindow();
		break;
	case MODE_BATTLE:	DrawField();
						DrawPlayer();
						DrawEnemy();
						DrawBattle();
		break;
	case MODE_ENEMY:	DrawField();
						DrawPlayer();
						DrawEnemy();
						DrawCursor();
						DrawWindow();
	case MODE_CLEAR:	CombineBuffer(&g_ClearBuffer);
		break;
	case MODE_GAMEOVER:	SetChara("GAMEOVER", WINDOW_WIDTH / 2 - 4 * CHARA_SIZE * 2, WINDOW_HEIGHT / 2 - CHARA_SIZE / 2, 0);
	default:	break;
	}

	DrawChara();
	DrawBuffer();
}

void End(void)
{
	EndBuffer();
	EndChara();
	EndTitle();
	EndField();
	EndPlayer();
	EndEnemy();
	EndCursor();
	EndBattle();
}

void SetMODE(MODE mode)
{
	g_Mode = mode;
}

MODE GetMODE(void)
{
	return g_Mode;
}
