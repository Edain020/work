//------------------------------------------
//								   title.cpp
//�@�����:AT11B192 No.17 ������G
//�X�V�����`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
//2020/02/21
// �v���O��������J�n
//2020/02/21
// �Q�[���I��p�̏�����ǉ�
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
//===== �C���N���[�h�� =====
#define CONIOEX
#include "conioex.h"
#include "title.h"
#include "main.h"
#include "buffer.h"
#include "bitmap.h"

//===== �萔�E�}�N����` =====
#define SAMPLE_IMAGE_WIDTH	(150)
#define SAMPLE_IMAGE_HEIGHT	(75)
#define SAMPLE_IMAGE_X		(70)
#define SAMPLE_IMAGE_Y		(50)

//===== �O���[�o���ϐ� =====
BUFFER g_TitleBuffer;				// �^�C�g���p�o�b�t�@
IMAGE *g_pTitleImage;				// �^�C�g���摜
IMAGE *g_paSampleImage[GAME_MAX];	// �I����ʗp�摜
bool g_bEnd;						// �I���t���O
int g_nGameNum;						// �I�𒆂̃Q�[��

GAME g_aGame[GAME_MAX] = { GAME_DK };	// �Q�[���̈ꗗ

void InitTitle(void)
{
	//===== �ϐ��錾 =====
	int i;
	char szTitleFile[] = { "bmp/Title.bmp" };	// �^�C�g���̉摜�̃t�@�C����
	char szaSampleFile[GAME_MAX][MAX_FILE_NAME] = {
		{ "bmp/�c�o���̎q���L.bmp" },
	};	// �Q�[���I��p�摜�̃t�@�C����

	//===== ���������� =====
	g_bEnd = false;
	InitBuffer(&g_TitleBuffer);
	g_pTitleImage = Read_Bmp(szTitleFile, WINDOW_HEIGHT, WINDOW_WIDTH);
	for (i = 0; i < GAME_MAX; i++)
	{
		g_paSampleImage[i] = Read_Bmp(szaSampleFile[i], SAMPLE_IMAGE_HEIGHT, SAMPLE_IMAGE_WIDTH);
	}
	g_nGameNum = 0;
}

void UpdateTitle(void)
{
	//===== �X�V���� =====
	if (!g_bEnd)
	{
		if (inport(PK_RIGHT))
		{
			g_nGameNum = (g_nGameNum + 1) % GAME_MAX;
		}
		if (inport(PK_LEFT))
		{
			g_nGameNum = g_nGameNum - 1;
			if (g_nGameNum < 0)	g_nGameNum = GAME_MAX - 1;
		}
	}
	if (inport(PK_ENTER))
		g_bEnd = true;
	else if (g_bEnd)
	{
		SetMODE(MODE_PLAYER);	// ���[�h�ؑ�
		Update();				// �X�V����
	}
	UpdateBuffer(&g_TitleBuffer, g_pTitleImage, 0, 0);
	UpdateBuffer(&g_TitleBuffer, g_paSampleImage[g_nGameNum], SAMPLE_IMAGE_X, SAMPLE_IMAGE_Y);
}

void DrawTitle(void)
{
	CombineBuffer(&g_TitleBuffer);
}

void EndTitle(void)
{

}