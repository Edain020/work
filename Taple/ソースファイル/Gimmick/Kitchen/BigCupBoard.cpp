//==========================================
//									BigCupboard.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.29  ¼–{aŒá
//
//````````XV—š—ð`````````
// 2020/11/** §ìŠJŽn
//		12/06 @HŠí’I
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "BigCupboard.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* BigCupboard::m_pModel = nullptr;


BigCupboard::~BigCupboard()
{
	Uninit();
}


bool BigCupboard::Init()
{
	m_gimmickType = GIMMICK_BIGCUPBOARD;
	m_size.x =BIGCUPBOARD_SIZE_X;
	m_size.y =BIGCUPBOARD_SIZE_Y;
	m_size.z =BIGCUPBOARD_SIZE_Z;

	//m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Kitchen/BigCupBoard/kitchen_tana01.fbx"));
	}
	return true;
}


void BigCupboard::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void BigCupboard::Draw()
{
	//SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();

	SHADER->SetWorld(DirectX::XMMatrixScaling(0.1f, 0.1f,0.1f) *DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
	SHADER->SetTexture(NULL);
}

