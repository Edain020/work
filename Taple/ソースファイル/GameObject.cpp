//==========================================
//							  GameObject.cpp
//�@�Q�[���I�u�W�F�N�g�֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/10/28 ����J�n
//		12/12 �Փˎ��̏������s���֐�OnCollision��ǉ�
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

//===== �C���N���[�h�� =====
#include "GameObject.h"
#include "Shader.h"
#include "Defines.h"



// �R���X�g���N�^
GameObject::GameObject(void)
	: m_pCube(nullptr)
	, m_pos(0, 0, 0)
	, m_size(1, 1, 1)
	, m_move(0, 0, 0)
	, m_rot(0, 0, 0)
	, m_collisionType(COLLISION_STATIC)
{
}


// �f�X�g���N�^
GameObject::~GameObject(void)
{
	Uninit();
}


bool GameObject::Init(void)
{
	// �L���[�u�̐���
	m_pCube = new Cube();
	m_pCube->SetSize(m_size.x, m_size.y, m_size.z);
	m_pCube->SetPos(m_pos.x, m_pos.y, m_pos.z);

	return true;
}


void GameObject::Uninit(void)
{
	SAFE_DELETE(m_pCube);
}


void GameObject::Draw(void)
{
	SHADER->SetWorld(
		DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z)
		* DirectX::XMMatrixRotationRollPitchYaw(m_rot.x, m_rot.y, m_rot.z)
		* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	);

	m_pCube->Draw();
}
