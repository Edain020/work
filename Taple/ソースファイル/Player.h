//==========================================
//								  Player.cpp
//	�v���C���[�֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/10/30 ����J�n
//		12/10 �����o�ϐ��ɏ�Ԃ�\���t���O�𕡐��ǉ�
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include <list>
#include "CharacterBase.h"
#include "Model.h"
#include "Gimmick/Gimmick.h"
#include "Sound.h"


//===== �O���錾 =====
class Tape;


//===== �N���X��` =====
class Player : public CharacterBase
{
public:
	//===== �����o�֐� =====
	Player(void);
	virtual ~Player(void);

	//----- �l�又�� -----
	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void ReSpawn(void);
	void Roll(float rollSpeed);
	
	virtual bool isPlayer(void) { return true; }

	//----- �Z�b�^�[ -----
	void SetTarget(Gimmick *pTarget) { m_pTarget = pTarget; }
	void SetGround(bool isGround) { m_isGround = isGround; }
	void SetGrab(bool isGrab) { m_isGrab = isGrab; }
	void SetExtendTape(bool isExtend) { m_isExtendTape = isExtend; }
	void SetRoll(bool isRoll) { m_isRoll = isRoll; }
	void SetCanRoll(bool canRoll) { m_canRoll = canRoll; }


	//----- �Q�b�^�[ -----
	Gimmick* GetTarget(void) { return m_pTarget; }
	float GetDir(void) { return m_fDir; }
	bool isGround(void) { return m_isGround; }

private:
	//===== �����o�ϐ� =====
	Gimmick *m_pTarget;	// �^�[�Q�b�g

	float m_fRotSpeed;		// ��]���x
	float m_fDir;			// ����
	float m_fYaw;			// y�����̉�](�ڕW�l)
	float m_fTargetSizeCnt;	// �^�[�Q�b�g�̖ڈ�̃T�C�Y
	bool m_isGround;		// �ڒn����
	bool m_isGrab;			// ��������ł��邩�ǂ���
	bool m_isExtendTape;	// �e�[�v��L�΂��Ă��邩�ǂ���
	bool m_isRoll;			// �e�[�v�������Ă��邩�ǂ���
	bool m_canRoll;			// �e�[�v�𗣂��邩�ǂ���

	Model *m_pBodyModel;	// �e�[�v�{�̂̃��f��
	Model *m_pEyeModel;		// �e�[�v�̖ڂ̃��f��
	Model *m_pMouthModel;	// �e�[�v�̌��̃��f��
	Tape *m_pTape;			// �e�[�v

	Sound *m_pTapeSE;	// �T�E���h

	DirectX::XMFLOAT3 m_targetRange;
	std::list<Gimmick*> m_pTargetList;

	//===== �����o�֐� =====
	void Move(void);		// �ړ��֌W
	void ControlTape(void);	// �e�[�v�֌W
};
