//==========================================
//									FallBook.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ð`````````
// 2020/01/05 §ìŠJŽn
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "FallBook.h"
#include "../../Shader.h"
#include "../../Defines.h"
#include "../../GamePad.h"
#include "../../Input.h"
#include "../../Player.h"


Model* FallBook::m_pModel = nullptr;
Sound* FallBook::m_pSE = nullptr;



FallBook::FallBook()
	: m_isFallDown(false)
	, m_fAngle(0.0f)
	, m_fFallSpeed(0.0f)
{
	m_isTarget = true;
}


FallBook::~FallBook()
{
	Uninit();
}


bool FallBook::Init(void)
{
	m_gimmickType = GIMMICK_FALL_BOOK;
	m_size.x = FALL_BOOK_SIZE_X;
	m_size.y = FALL_BOOK_SIZE_Y;
	m_size.z = FALL_BOOK_SIZE_Z;

	m_targetPos.y = FALL_BOOK_SIZE_Y / 2.0f;
	
	m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Study/BookSlim7cm/BookSlim7cm.fbx"));
	}
	if (m_pSE == nullptr)
	{
		m_pSE = new Sound();
		m_pSE->Load(ASSET("Sound/SE/book.mp3"));
		m_pSE->SetVolume(0.5f);
	}
	return true;
}


void FallBook::Uninit(void)
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


void FallBook::UpdatePlayer(Player *player)
{
	if (!m_isFallDown)
	{ 
		if (GamePad::IsButtonPress(GamePadButton::A) || IsKeyPress('J'))
		{
			m_isFallDown = true;
			player->SetCanRoll(false);
		}
	}
	else
	{
		m_fFallSpeed += GRAVITY;
		m_fAngle += m_fFallSpeed * 2.0f;

		if (m_fAngle >= 90.0f)
		{
			m_fAngle = 90.0f;
			m_size.x = FALL_BOOK_SIZE_Y;
			m_size.y = FALL_BOOK_SIZE_X;
//			m_pos.x -= (FALL_BOOK_SIZE_Y / 2.0f);
//			m_pos.y -= FALL_BOOK_SIZE_Y / 2.0f;
			m_pos.x -= 0.5f;
			m_pos.y -= 0.75f;
			m_isTarget = false;
			player->SetRoll(true);
			player->SetCanRoll(true);
		}
	}
}



void FallBook::Draw()
{
	if (m_isTarget)
	{
		SHADER->SetWorld(
			DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, DEG_TO_RAD(m_fAngle))
			* DirectX::XMMatrixTranslation(m_pos.x - sinf(DEG_TO_RAD(m_fAngle)) * (FALL_BOOK_SIZE_Y / 2.0f - FALL_BOOK_SIZE_X / 2.0f), m_pos.y - FALL_BOOK_SIZE_Y / 2.0f + sinf(DEG_TO_RAD(m_fAngle)) * FALL_BOOK_SIZE_X / 2.0f, m_pos.z));
	}
	else
	{
		SHADER->SetWorld(
			DirectX::XMMatrixRotationRollPitchYaw(0.0f, 0.0f, DEG_TO_RAD(m_fAngle))
			* DirectX::XMMatrixTranslation(m_pos.x + m_size.x / 2.0f, m_pos.y, m_pos.z));
	}
	m_pModel->Draw();

	SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pCube->Draw();
}
