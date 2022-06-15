//==========================================
//									Cupboard.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.29  ¼–{aŒá
//
//````````XV—š—ð`````````
// 2020/11/** §ìŠJŽn
//		12/06 @HŠí’I
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Cupboard.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* Cupboard::m_pModel = nullptr;



Cupboard::~Cupboard()
{
	Uninit();
}


bool Cupboard::Init()
{
	m_gimmickType = GIMMICK_CUPBOARD;
	m_size.x = CUPBOARD_SIZE_X;
	m_size.y = CUPBOARD_SIZE_Y;
	m_size.z = CUPBOARD_SIZE_Z;

	//m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Kitchen/Cupboard/kitchen_tana02.fbx"));

	}
	return true;
}


void Cupboard::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void Cupboard::Draw()
{
	//SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();

	SHADER->SetWorld(DirectX::XMMatrixScaling(0.1f, 0.1f,0.1f) *DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
	SHADER->SetTexture(NULL);
}
