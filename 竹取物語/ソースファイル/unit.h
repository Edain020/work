//------------------------------------------
//									  unit.h
//�@�����:AT11B192 No.17 ������G
//�X�V�����`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
//2020/02/28
// �v���O��������J�n
//2020/02/29
// UNIT�\���̂̒��g���ꕔJOB_INFO�\���̂Ɉړ�
//2020/03/02
// ���j�b�g�̌������Ǘ�����񋓌^(UNIT_DIRECTION)��ǉ�
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
#ifndef _UNIT_H_
#define _UNIT_H_

//===== �C���N���[�h�� =====
#include "bitmap.h"

//===== �萔�E�}�N����` =====
#define MAX_NAME			(21)	// ���O�̍ő啶����
#define UNIT_ANIME_DELAY	(5)	// ���j�b�g�̃A�j���̊Ԋu(�t���[��)

//===== �񋓌^�錾 =====

//--------------------------------------
//��������p�񋓌^
//--------------------------------------
typedef enum
{
	DIRECTION_NONE,		// �ҋ@
	DIRECTION_UP,		// �����
	DIRECTION_DOWN,		// ������
	DIRECTION_LEFT,		// ������
	DIRECTION_RIGHT,	// �E����
	DIRECTION_MAX		// 4����
} UNIT_DIRECTION;

//--------------------------------------
//�W���u�ݒ�p�񋓌^
//--------------------------------------
typedef enum
{
	JOB_SWORDMAN,	//����
	JOB_SPEARMAN,	//����
	JOB_BOWMAN,		//�|��
	JOB_MAX
} JOB;

//--------------------------------------
//�w�c���ʗp�񋓌^
//--------------------------------------
typedef enum
{
	TEAM_PLAYER,	// �v���C���[�`�[��
	TEAM_ENEMY,		// �G�`�[��
	TEAM_MAX		// �`�[���̎��
} TEAM;


//===== �\���̐錾 =====

//--------------------------------------
//�W���u���p�\����
//--------------------------------------
typedef struct
{
	JOB Job;		//�E��
	int nMaxLife;	//�ő�̗�
	int nAtk;		//�U����
	int nDef;		//�h���
	int nMove;		//�ړ���
	int nAtkRange;	//�˒�
} JOB_INFO;

//--------------------------------------
//���j�b�g�p�\����
//--------------------------------------
typedef struct
{
	char szName[MAX_NAME];	// ���O
	TEAM Team;				// �w�c
	JOB_INFO Job;			// �W���u���
	int nLife;				// �̗�
	int nPosX;				// ���g��X���W
	int nPosY;				// ���g��Y���W
	int nNextPosX;			// �ړ����X���W
	int nNextPosY;			// �ړ����Y���W
	UNIT_DIRECTION Dir;		// �����Ă������
	bool bExist;			// ���݂��邩�ǂ���
	bool bAction;			// �s���ς݂��ǂ���
	IMAGE *pImage;			// ���j�b�g�̉摜�f�[�^
	int nAnimeNum;			// �A�j���[�V�����̔ԍ�
	int nAnimeCnt;			// �A�j���[�V�����p�̃J�E���^�[
} UNIT;


//===== �v���g�^�C�v�錾 =====
//--------------------------------------
//�֐����FInitUnit
//���@���FUNIT*, const char*, JOB
//		(���������郆�j�b�g�A���j�b�g�̖��O�A�W���u)
//�߂�l�F�Ȃ�
//���@�e�F���j�b�g�̏��������s��
//--------------------------------------
void InitUnit(UNIT*, const char*, JOB);

#endif // !_UNIT_H_
