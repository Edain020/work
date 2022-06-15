//==========================================
//							 CharacterBase.h
//�@�L�����N�^�[�֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/10/28 ����J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "GameObject.h"


//===== �N���X��` =====
class CharacterBase : public GameObject
{
public:
	//===== �����o�֐� =====
	CharacterBase();
	virtual ~CharacterBase();

	// �L�����N�^�[�̉摜�f�[�^�������ɂȂ�悤�ɕ`��ŕ␳���s��
	void Draw();

protected:
	float m_fYaw;
	float m_fPitch;
	float m_fRoll;
};
