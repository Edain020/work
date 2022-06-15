//==========================================
//							Stove.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.29 ¼–{aŒá
//
//````````XV—š—ð`````````
// 2020/11/** §ìŠJŽn
//		12/11 ƒRƒ“ƒ
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Stove.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* Stove::m_pModel = nullptr;



Stove::~Stove()
{
	Uninit();
}

bool Stove::Init(void)
{
	m_gimmickType = GIMMICK_STOVE;
	m_size.x = STOVE_SIZE_X;
	m_size.y = STOVE_SIZE_Y;
	m_size.z = STOVE_SIZE_Z;

	//m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Kitchen/Stove/konnro.fbx"));
	}
	return true;
}

void Stove::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void Stove::Draw()
{
	//SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();

	SHADER->SetWorld(DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
	SHADER->SetTexture(NULL);
}
