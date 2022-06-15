//==========================================
//									Nail.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ð`````````
// 2020/01/03 §ìŠJŽn
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Nail.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* Nail::m_pModel = nullptr;



Nail::Nail()
{
	m_isTarget = true;
}


Nail::~Nail()
{
	Uninit();
}


bool Nail::Init()
{
	m_gimmickType = GIMMICK_NAIL;
	m_size.x = NAIL_SIZE_X;
	m_size.y = NAIL_SIZE_Y;
	m_size.z = NAIL_SIZE_Z;

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Study/Nail/pushpinRED.fbx"));
	}
	return true;
}


void Nail::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void Nail::Update()
{

}


void Nail::Draw()
{
	SHADER->SetWorld(DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
}
