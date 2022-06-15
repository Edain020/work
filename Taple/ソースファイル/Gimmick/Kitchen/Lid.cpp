//==========================================
//									Lid.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.29 ¼–{aŒá
//
//````````XV—š—ð`````````
// 2020/11/** §ìŠJŽn
//		12/11 ŠW(—eŠí—p)
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Lid.h"
#include "../../Shader.h"
#include "../../Defines.h"
#include "../../GamePad.h"
#include "../../Input.h"
#include "../../Player.h"


Model* Lid::m_pModel = nullptr;



Lid::Lid(void)
	: m_isFallDown(false)
	, m_fAngle(0.0f)
	, m_fFallSpeed(0.0f)
{
	m_isTarget = true;
}


Lid::~Lid()
{
	Uninit();
}


bool Lid::Init()
{
	m_gimmickType = GIMMICK_LID;
	m_size.x = LID_SIZE_X;
	m_size.y = LID_SIZE_Y;
	m_size.z = LID_SIZE_Z;

	m_targetPos.y += LID_SIZE_Y / 2.0f;

	m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Kitchen/Lid/Lid.fbx"));
	}
	return true;
}


void Lid::UpdatePlayer(Player *player)
{
	if (!player->isGround())
	{
		player->SetRoll(true);
		return;
	}

	if (!m_isFallDown)
	{
		if (GamePad::IsButtonPress(GamePadButton::A) || IsKeyPress('J'))
		{
			m_isFallDown = true;
			player->SetCanRoll(false);
		}
	}
	else if (m_isTarget)
	{
		m_fFallSpeed += GRAVITY;
		m_fAngle += m_fFallSpeed * 2.0f;
		player->Roll(((fabsf(5.0f / 60) / (1.0f * PI)) * 180.0f));

		if (m_fAngle >= 90.0f)
		{
			m_fAngle = 90.0f;
			m_size.x = LID_SIZE_Y;
			m_size.y = LID_SIZE_X;
			m_pos.x -= (LID_SIZE_Y / 2.0f);
			m_pos.y -= (LID_SIZE_Y / 2.0f);

			m_isTarget = false;
			player->SetRoll(true);
			player->SetCanRoll(true);
		}

		m_targetPos.x = -sinf(DEG_TO_RAD(m_fAngle)) * m_size.y;
		m_targetPos.y = -(m_size.y / 2) + cosf(DEG_TO_RAD(m_fAngle)) * m_size.y;
	}
}



void Lid::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void Lid::Draw()
{
	SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();

	if (m_isTarget)
	{
		SHADER->SetWorld(
			DirectX::XMMatrixRotationRollPitchYaw(DEG_TO_RAD(m_fAngle), DEG_TO_RAD(-90), 0.0f)
			* DirectX::XMMatrixTranslation(
				m_pos.x                  - (sinf(DEG_TO_RAD(m_fAngle)) * (m_size.y / 2)),
				m_pos.y - (m_size.y / 2) + (cosf(DEG_TO_RAD(m_fAngle)) * (m_size.y / 2)),
				m_pos.z));
	}
	else
	{
		SHADER->SetWorld(
			DirectX::XMMatrixRotationRollPitchYaw(DEG_TO_RAD(m_fAngle), DEG_TO_RAD(-90), 0.0f)
			* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	}
	m_pModel->Draw();
	SHADER->SetTexture(NULL);
}