//------------------------------------------
//									 field.h
//�@�����:AT11B192 No.17 ������G
//�X�V�����`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
//2020/02/21
// �v���O��������J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
#ifndef _FIELD_H_
#define _FIELD_H_

//===== �C���N���[�h�� =====
#include "buffer.h"

//===== �萔�E�}�N����` =====
#define TILE_SIZE			(16)	// �}�b�v�^�C���̃T�C�Y
#define FIELD_HEIGHT		(20)	// �t�B�[���h�̏c�̑傫��(�^�C����)
#define FIELD_WIDTH			(20)	// �t�B�[���h�̉��̑傫��(�^�C����)
#define FIELD_BUFFER_HEIGHT	(WINDOW_HEIGHT / TILE_SIZE)			// ��ʂɕ\������^�C����(�c)
#define FIELD_BUFFER_WIDTH	(WINDOW_WIDTH  / (TILE_SIZE * 2))	// ��ʂɕ\������^�C����(��)
#define MAX_TERRAIN_NAME	(11)	// �n�`�̖��O�̍ő啶����

//===== �񋓌^�錾 =====

//--------------------------------------
//�n�`����p�񋓌^
//--------------------------------------
typedef enum
{
	TERRAIN_PLAIN,		//���n
	TERRAIN_FOREST,		//�X
	TERRAIN_MOUNTAINS,	//�R
	TERRAIN_RIVER,		//��
	TERRAIN_MAX			//�n�`�̎��
} TERRAIN;

//--------------------------------------
//���j�b�g����p�񋓌^
//--------------------------------------
typedef enum
{
	FIELD_UNIT_NONE,	// ���j�b�g����
	FIELD_UNIT_PLAYER,	// �������j�b�g
	FIELD_UNIT_ENEMY,	// �G���j�b�g
	FIELD_UNIT_MAX		// ���j�b�g�̎��
} FIELD_UNIT;

//===== �\���̐錾 =====

//--------------------------------------
//�n�`���p�\����
//--------------------------------------
typedef struct
{
	TERRAIN Terrain;					// �n�`�ԍ�
	char TerrainName[MAX_TERRAIN_NAME];	// �n�`��
	IMAGE *pImage;						// �摜�f�[�^
	int nPassCost;						// �ʉ߃R�X�g
} TERRAIN_INFO;

//--------------------------------------
//�t�B�[���h�p�\����
//--------------------------------------
typedef struct
{
	int nPosX;				// X���W
	int nPosY;				// Y���W
	TERRAIN_INFO Terrain;	// �n�`���
	FIELD_UNIT UnitType;	// ����Ă��郆�j�b�g�̎��
	bool bPass;				// �ʍs�\���ǂ���
} FIELD;


//===== �v���g�^�C�v�錾 =====

//--------------------------------------
//�֐����FInitField
//���@���F�Ȃ�
//�߂�l�F�Ȃ�
//���@�e�F�t�B�[���h�O����
//--------------------------------------
void InitField(void);
//--------------------------------------
//�֐����FUpdateField
//���@���F�Ȃ�
//�߂�l�F�Ȃ�
//���@�e�F�t�B�[���h�̍X�V
//--------------------------------------
void UpdateField(void);
//--------------------------------------
//�֐����FDrawField
//���@���F�Ȃ�
//�߂�l�F�Ȃ�
//���@�e�F�t�B�[���h��\������
//--------------------------------------
void DrawField(void);
//--------------------------------------
//�֐����FEndField
//���@���F�Ȃ�
//�߂�l�F�Ȃ�
//���@�e�F�t�B�[���h�̌㏈��
//--------------------------------------
void EndField(void);
//--------------------------------------
//�֐����FGetField
//���@���F�Ȃ�
//�߂�l�FFIELD* (�t�B�[���h�f�[�^)
//���@�e�F�ʂ̃t�@�C���Ƀt�B�[���h�̃f�[�^��n��
//--------------------------------------
FIELD* GetField(void);
//--------------------------------------
//�֐����FGetField
//���@���Fint, int (�^�C���̏���ǂݍ��݂������W(x, y))
//�߂�l�FFIELD* (�t�B�[���h�f�[�^)
//���@�e�F�w�肳�ꂽ�ʒu�̃^�C���̃f�[�^��n��
//--------------------------------------
FIELD* GetFieldxy(int, int);
//--------------------------------------
//�֐����FGetFieldBufferX
//���@���F�Ȃ�
//�߂�l�Fint (X���W)
//���@�e�F�ʂ̃t�@�C���Ƀt�B�[���h�̗p�o�b�t�@�̈ʒu��n��
//--------------------------------------
int GetFieldBufferX(void);
//--------------------------------------
//�֐����FGetFieldBufferY
//���@���F�Ȃ�
//�߂�l�Fint (Y���W)
//���@�e�F�ʂ̃t�@�C���Ƀt�B�[���h�̗p�o�b�t�@�̈ʒu��n��
//--------------------------------------
int GetFieldBufferY(void);



void SetFieldBuffer(int, int);
//--------------------------------------
//�֐����FMoveFieldBuffer
//���@���Fint, int (�ړ���(x,y))
//�߂�l�F�Ȃ�
//���@�e�F�t�B�[���h�o�b�t�@���ړ�
//--------------------------------------
void MoveFieldBuffer(int, int);
//--------------------------------------
//�֐����FGetTerrainInfo
//���@���Fint, int (�n�`����ǂݍ��݂������W(x, y))
//�߂�l�FTERRAIN_INFO* (�n�`���)
//���@�e�F�w�肳�ꂽ���W�̒n�`����n��
//--------------------------------------
TERRAIN_INFO* GetTerrainInfo(int, int);

void CheckEnemyUnitMove(int, int, int);


void ResetPass(void);

#endif // !_FIELD_H_
