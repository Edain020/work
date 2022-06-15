//==========================================
//									Faucet.cpp
//	�{�֘A
//�@�����:AT12D171 No.29  ���{�a��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/11/** ����J�n
//		12/06 
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

//===== �C���N���[�h�� =====
#include "Faucet.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* Faucet::m_pModel = nullptr;


Faucet::~Faucet()
{
	Uninit();
}


bool Faucet::Init()
{
	m_gimmickType = GIMMICK_FAUCET;
	m_size.x = FAUCET_SIZE_X;
	m_size.y = FAUCET_SIZE_Y;
	m_size.z = FAUCET_SIZE_Z;

	//m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Kitchen/Faucet/jaguchi.fbx"));
	}
	return true;
}


void Faucet::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void Faucet::Draw()
{
	//SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();

	SHADER->SetWorld(
		DirectX::XMMatrixScaling(0.1f,0.2f,0.2f)						// �g�k
		* DirectX::XMMatrixRotationY(180 * 3.141592f / 180)				// ��]
		* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y-1,m_pos.z+3));	// �ړ�
	m_pModel->Draw();
	SHADER->SetTexture(NULL);
}
