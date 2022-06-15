//==========================================
//									Oven.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.29  ¼–{aŒá
//
//````````XV—š—ð`````````
// 2020/11/** §ìŠJŽn
//		12/06 
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Oven.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* Oven::m_pModel = nullptr;



Oven::~Oven()
{
	Uninit();
}


bool Oven::Init()
{
	m_gimmickType = GIMMICK_OVEN;
	m_size.x = OVEN_SIZE_X;
	m_size.y = OVEN_SIZE_Y;
	m_size.z = OVEN_SIZE_Z;

	//m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Kitchen/Oven/oven.fbx"));
	}
	return true;
}


void Oven::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void Oven::Draw()
{
	//SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();

	SHADER->SetWorld(DirectX::XMMatrixRotationY(180 * 3.141592f / 180)*DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
	SHADER->SetTexture(NULL);
}
