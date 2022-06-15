//==========================================
//							    Ladle.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.29  ¼–{aŒá
//
//````````XV—š—ð`````````
// 2020/11/** §ìŠJŽn
//		12/11
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Ladle.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* Ladle::m_pModel = nullptr;



Ladle::~Ladle()
{
	Uninit();
}


bool Ladle::Init()
{
	m_gimmickType = GIMMICK_LADLE;
	m_size.x = LADLE_SIZE_X;
	m_size.y = LADLE_SIZE_Y;
	m_size.z = LADLE_SIZE_Z;

	//m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Kitchen/Ladle/otama.fbx"));
	}
	return true;
}


void Ladle::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void Ladle::Draw()
{
	//SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();

	SHADER->SetWorld(
		DirectX::XMMatrixScaling(3,2,1)
		* DirectX::XMMatrixRotationY(DEG_TO_RAD(180))
		* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y-0.2f, m_pos.z));
	m_pModel->Draw();
	SHADER->SetTexture(NULL);
}
