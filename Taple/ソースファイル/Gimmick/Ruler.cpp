//==========================================
//									Ruler.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//		   AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ð`````````
// 2020/11/** §ìŠJŽn
//		11/30 
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Ruler.h"
#include "../Shader.h"
#include "../Defines.h"


Model* Ruler::m_pModel = nullptr;


Ruler::Ruler()
{
}
Ruler::~Ruler()
{
	Uninit();
}

bool Ruler::Init()
{
	m_gimmickType = GIMMICK_RULER;
	m_size.x = RULER_SIZE_X;
	m_size.y = RULER_SIZE_Y;
	m_size.z = RULER_SIZE_Z;

	m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Ruler/Ruler.fbx"));
	}
	return true;
}

void Ruler::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}

void Ruler::Update()
{

}
void Ruler::Draw()
{
	//SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();

	SHADER->SetWorld(
		DirectX::XMMatrixRotationRollPitchYaw(0.0f, DEG_TO_RAD(180.0f), 0.0f)
		* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();

	SHADER->SetTexture(NULL);
}

