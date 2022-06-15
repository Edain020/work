//===== インクルード部 =====
#include "Balloon.h"
#include "Defines.h"
#include <random>



Balloon::~Balloon()
{
	Uninit();
}


void Balloon::Init()
{
	m_pImage = new Image();
	m_pImage->SetSize(DirectX::XMFLOAT3(120.0f, 187.0f, 0.0f));

	std::random_device rand;
	switch (rand() % 4)
	{
	case 0:
		m_pImage->LoadTexture(ASSET("Balloon_Blue.png"));
		break;
	case 1:
		m_pImage->LoadTexture(ASSET("Balloon_Green.png"));
		break;
	case 2:
		m_pImage->LoadTexture(ASSET("Balloon_Red.png"));
		break;
	case 3:
		m_pImage->LoadTexture(ASSET("Balloon_Yellow.png"));
		break;
	default:
		break;
	}
}


void Balloon::Uninit()
{
	SAFE_DELETE(m_pImage);
}


void Balloon::Update()
{
	float move = SCREEN_HEIGHT / (60.0f * 1.5f);
	m_pos.x -= move * 0.1f;
	m_pos.y += move;

	m_pImage->SetPos(m_pos);
}


void Balloon::Draw()
{
	m_pImage->Draw();
}


void Balloon::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}
