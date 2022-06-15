//==========================================
//									Crepas.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//		   AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ð`````````
// 2020/11/** §ìŠJŽn
//		11/30 
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Crepas.h"
#include "../Shader.h"
#include "../Defines.h"
#include "../Main.h"
#include "../GamePad.h"
#include "../Player.h"

#include "../Input.h"


Model* Crepas::m_pModel = nullptr;
Sound* Crepas::m_pSE = nullptr;



Crepas::Crepas()
	: m_fMoveDis(0.0f)
	, m_isPlaySE(false)
	, m_isStopSE(false)
{
	m_isTarget = true;
}


Crepas::~Crepas()
{
	Uninit();
}

bool Crepas::Init()
{
	m_gimmickType = GIMMICK_CREPAS;
	m_size.x = CREPAS_SIZE_X;
	m_size.y = CREPAS_SIZE_Y;
	m_size.z = CREPAS_SIZE_Z;

	m_targetPos.x = -(CREPAS_SIZE_X / 2.0f);

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Crepas/Crepas.fbx"));
	}
	if (m_pSE == nullptr)
	{
		m_pSE = new Sound();
		m_pSE->Load(ASSET("Sound/SE/Drag.mp3"), true);
		m_pSE->SetVolume(0.5f);
	}
	return true;
}


void Crepas::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
	if (m_pSE)
	{
		m_pSE->Stop();
		delete m_pSE;
		m_pSE = nullptr;
	}
}


void Crepas::Update(void)
{
	if (!m_isTarget)
	{
		if (m_isPlaySE)
		{
			m_pSE->Stop();
			m_isPlaySE = false;
		}
	}
	else
	{
		if(m_isStopSE && m_isPlaySE)
		{
			m_pSE->Stop();
			m_isPlaySE = false;
		}
	}

	m_isStopSE = true;
}


void Crepas::UpdatePlayer(Player *player)
{
	if (!player->isGround())
	{
		player->SetRoll(true);
		return;
	}

	if (GamePad::IsButtonPress(GamePadButton::A) || IsKeyPress('J'))
	 {
		float move = 5.0f / 60;
		move = -(move * player->GetDir());

		m_pos.x += move;
		m_fMoveDis += fabsf(move);
		player->Roll(((fabsf(move) / (1.0f * PI)) * 180.0f));
		
		if (!m_isPlaySE)
		{
			m_isPlaySE = true;
			m_pSE->Play();
		}
	}
	else if (m_isPlaySE)
	{
		m_isPlaySE = false;
		m_pSE->Stop();
	}

	if (m_fMoveDis > (CREPAS_SIZE_X / 3.0f) * 2.0f)
	{
		m_isTarget = false;
		m_isPlaySE = false;
		m_pSE->Stop();
		player->SetRoll(true);
	}

	m_isStopSE = false;
}


void Crepas::Draw()
{
	SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
}

