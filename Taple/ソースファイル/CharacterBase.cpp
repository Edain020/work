//==========================================
//						   CharacterBase.cpp
//�@�L�����N�^�[�֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/10/28 ����J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

//===== �C���N���[�h�� =====
#include "CharacterBase.h"
#include "Texture.h"
#include "Defines.h"



// �R���X�g���N�^
CharacterBase::CharacterBase(void)
	: m_fYaw(0)
	, m_fPitch(0)
	, m_fRoll(0)
{
	// �L�����N�^�[�͓����I�u�W�F�N�g���낤
	m_collisionType = COLLISION_DYNAMIC;
}


// �f�X�g���N�^
CharacterBase::~CharacterBase(void)
{
	Uninit();
}


void CharacterBase::Draw(void)
{
	SHADER->SetWorld(
		DirectX::XMMatrixRotationRollPitchYaw(m_fPitch, m_fYaw, m_fRoll)
		* DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z)
		* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pCube->Draw();
}
