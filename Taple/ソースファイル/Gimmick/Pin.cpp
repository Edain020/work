//==========================================
//									Pin.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//		   AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ð`````````
// 2020/11/** §ìŠJŽn
//		11/30 
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Pin.h"
#include "../Shader.h"
#include "../Defines.h"
#include "../Main.h"

Model* Pin::m_pModel = nullptr;


Pin::Pin()
{
}


Pin::~Pin()
{
	Uninit();

}

bool Pin::Init()
{
	m_size.x = PIN_SIZE_X;
	m_size.y = PIN_SIZE_Y;
	m_size.z = PIN_SIZE_Z;

//	m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Pin/pushpinRED.fbx"));
	}
	return true;
}


void Pin::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void Pin::Draw()
{
	//SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();

	SHADER->SetWorld(DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();

}

