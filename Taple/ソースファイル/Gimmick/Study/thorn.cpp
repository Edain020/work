//==========================================
//									thorn.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ð`````````
// 2020/01/03 §ìŠJŽn
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "thorn.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* thorn::m_pModel = nullptr;



thorn::thorn()
{
}


thorn::~thorn()
{
	Uninit();
}


bool thorn::Init()
{
	m_gimmickType = GIMMICK_THORN;
	m_size.x = THORN_SIZE_X;
	m_size.y = THORN_SIZE_Y;
	m_size.z = THORN_SIZE_Z;

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Study/thorn/pushpin.fbx"));
	}
	return true;
}


void thorn::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void thorn::Update()
{
}


void thorn::Draw()
{
	SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
}

