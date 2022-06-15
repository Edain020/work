//==========================================
//									PendulumClock.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ð`````````
// 2020/01/03 §ìŠJŽn
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "PendulumClock.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* PendulumClock::m_pModel = nullptr;


PendulumClock::PendulumClock()
{
}


PendulumClock::~PendulumClock()
{
	Uninit();

}

bool PendulumClock::Init()
{
	m_gimmickType = GIMMICK_PENDULUM;
	m_size.x = PENDULUM_CLOCKL_SIZE_X;
	m_size.y = PENDULUM_CLOCKL_SIZE_Y;
	m_size.z = PENDULUM_CLOCKL_SIZE_Z;

	m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/PendulumClock/pushpin.fbx"));
	}
	return true;
}


void PendulumClock::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void PendulumClock::Update()
{

}


void PendulumClock::Draw()
{
	SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pCube->Draw();

	SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
	SHADER->SetTexture(NULL);
}

