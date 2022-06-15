//==========================================
//									Clock.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ð`````````
// 2020/12/04 §ìŠJŽn
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Clock.h"
#include "../Shader.h"
#include "../Defines.h"


Model* Clock::m_pModel = nullptr;


Clock::Clock()
	: m_fRadius(5)
	, m_fDeg(0)
{
}
Clock::Clock(float radius, float seed)
	: m_fRadius(radius)
	, m_fDeg(seed)
{

}

Clock::~Clock()
{
	Uninit();

}

bool Clock::Init()
{
	m_gimmickType = GIMMICK_CLOCK;
	m_size.x = CLOCK_SIZE_X;
	m_size.y = CLOCK_SIZE_Y;
	m_size.z = CLOCK_SIZE_Z;

	m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Clock/pushpin.fbx"));
	}
	return true;
}


void Clock::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void Clock::Update()
{
	m_fDeg += 90 / 60.0f;
	if (m_fDeg >= 360.0f)
	{
		m_fDeg -= 360.0f;
	}

		m_pos.y = m_startPos.y + sinf(DEG_TO_RAD(m_fDeg)) * m_fRadius;
}


void Clock::Draw()
{
	//SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();

	SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();

}

