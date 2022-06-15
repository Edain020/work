//==========================================
//									Microwave.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.29  ¼–{aŒá
//
//````````XV—š—ð`````````
// 2020/11/** §ìŠJŽn
//		12/06 “dŽqƒŒƒ“ƒW
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Microwave.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* Microwave::m_pModel = nullptr;


Microwave::~Microwave()
{
	Uninit();
}


bool Microwave::Init()
{
	m_gimmickType = GIMMICK_MICROWAVE;
	m_size.x = MICROWAVE_SIZE_X;
	m_size.y = MICROWAVE_SIZE_Y;
	m_size.z = MICROWAVE_SIZE_Z;

	//m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Kitchen/Microwave/microwave.fbx"));
	}
	return true;
}


void Microwave::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void Microwave::Draw()
{
	//SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();

	SHADER->SetWorld(DirectX::XMMatrixRotationY(180 * 3.141592f / 180)*DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
	SHADER->SetTexture(NULL);
}
