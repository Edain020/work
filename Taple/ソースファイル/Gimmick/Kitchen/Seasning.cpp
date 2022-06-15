//==========================================
//							Seasning.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.29 ¼–{aŒá
//		  
//
//````````XV—š—ð`````````
// 2020/11/** §ìŠJŽn
//		11/30 
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Seasning.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* Seasning::m_pModel = nullptr;



Seasning::~Seasning()
{
	Uninit();
}


bool Seasning::Init()
{
	m_gimmickType = GIMMICK_SEASNING;
	m_size.x = SEASNING_SIZE_X;
	m_size.y = SEASNING_SIZE_Y;
	m_size.z = SEASNING_SIZE_Z;

	//m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Kitchen/Seasning/suger_soltBox.fbx"));
	}
	return true;
}


void Seasning::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void Seasning::Draw()
{
	//SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();

	SHADER->SetWorld(DirectX::XMMatrixRotationY(180 * 3.141592f / 180)*DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f) *DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
	SHADER->SetTexture(NULL);
}
