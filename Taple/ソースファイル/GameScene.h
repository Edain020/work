
// �C���N���[�h��
#pragma once


//===== �C���N���[�h�� =====
#include "Player.h"
#include "Defines.h"
#include "GimmickManager.h"
#include "Player.h"
#include "Timer.h"
#include "back_wall.h"
#include "Gimmick\Box.h"
#include "Sound.h"
#include "Image.h"
#include "Balloon.h"
#include "KidsRoom.h"
#include "Study.h"
#include "Kitchen.h"


//===== �萔�E�}�N����` =====
#define BALLOON_NUM	(20)

enum ModeKind
{
	MODE_GAME,		// �Q�[����
	MODE_CLEAR,		// �N���A
	MODE_GAMEOVER,	// �Q�[���I�[�o�[
};


//===== �N���X��` =====
class GameScene
{
public:
	GameScene(void) {}
	~GameScene(void) {}

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetStage(StageKind stage);

private:
	StageKind m_stage;
	ModeKind m_mode;

	Player		*m_pPlayer;		// �v���C���[
	BackWall	*m_pBackWall;	// �w�i
	Box			*m_pGoal;		// �S�[��
	Timer		*m_pTimer;		// �^�C�}�[

	// �N���A&�Q�[���I�[�o�[���
	Image *m_pBlack;	// ��ʂ��Â�����
	Image *m_pClear;	// �N���A�\��
	Image *m_pGameOver;	// �Q�[���I�[�o�[
	Balloon *m_pBalloons[BALLOON_NUM];	// ���D(�N���A���o)
	float m_fCnt;

	Sound *m_pSE;		// ���艹
	Sound *m_pClearSE;	// �N���A��
	Sound *m_pGameOverSE;

	//----- �X�e�[�W -----
	KidsRoom	m_kidsRoom;	// �q������
	Study		m_study;	// ����
	Kitchen		m_kitchen;	// �L�b�`��
};
