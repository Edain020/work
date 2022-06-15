//==========================================
//									Closet.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//		   AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ð`````````
// 2020/11/** §ìŠJŽn
//		11/30 
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Closet.h"
#include "../Shader.h"
#include "../Defines.h"


Model* Closet::m_pModel = nullptr;



Closet::~Closet()
{
	Uninit();
}


bool  Closet::Init(void)
{
	m_gimmickType = GIMMICK_CLOSET;
	m_size.x = CLOSET_SIZE_X;
	m_size.y = CLOSET_SIZE_Y;
	m_size.z = CLOSET_SIZE_Z;

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Closet/Closet.fbx"));
	}
	return true;
}


void Closet::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void Closet::Draw()
{
	SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
}
