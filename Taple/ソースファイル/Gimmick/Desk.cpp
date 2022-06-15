//==========================================
//									Desk.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//		   AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ð`````````
// 2020/11/** §ìŠJŽn
//		11/30 
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Desk.h"
#include "../Shader.h"
#include "../Defines.h"


Model* Desk::m_pModel = nullptr;



Desk::~Desk()
{
	Uninit();
}


bool Desk::Init(void)
{
	m_gimmickType = GIMMICK_DESK;
	m_size.x = DESK_SIZE_X;
	m_size.y = DESK_SIZE_Y;
	m_size.z = DESK_SIZE_Z;

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Desk/Desk.fbx"));
	}
	return true;
}


void Desk::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void Desk::Draw()
{
	SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
}
