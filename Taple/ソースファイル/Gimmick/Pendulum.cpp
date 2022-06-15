
//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Pendulum.h"
#include "../Main.h"
#include "../Defines.h"
#include "../GamePad.h"
#include "../Player.h"

#include "../Input.h"


Pendulum::Pendulum()
	: m_fLength(0.0f)
	, m_fMinLength(4.0f)
	, m_fMove(0.0f)
	, m_fRollSpeed(10 / 60.0f)
	, m_pPendulum(nullptr)
{
	m_gimmickType = GIMMICK_PENDULUM;
	m_isTarget = true;
}


Pendulum::~Pendulum()
{
	Uninit();
}


bool Pendulum::Init()
{
	return true;
}


void Pendulum::Uninit()
{
	SAFE_DELETE(m_pCube);
}


void Pendulum::UpdatePlayer(Player *player)
{
	if (!m_pPendulum)
	{
		m_pPendulum = player;
	}

	//----- ’·‚³‚ðŒvŽZ‚·‚é -----
	DirectX::XMFLOAT3 pendulumPos(m_pPendulum->GetPos());
	DirectX::XMFLOAT3 centerPos = m_pos;
	centerPos.x += m_targetPos.x;
	centerPos.y += m_targetPos.y;
	centerPos.z += m_targetPos.z;

	m_fLength = sqrtf((centerPos.x - pendulumPos.x) * (centerPos.x - pendulumPos.x) + (centerPos.y - pendulumPos.y) * (centerPos.y - pendulumPos.y));

	//----- ’·‚³‚ð’Z‚­‚·‚é -----
	if (m_fLength > m_fMinLength)
	{
		m_fLength -= m_fRollSpeed;
	}
	if (GamePad::IsButtonPress(GamePadButton::A) || IsKeyPress('J'))
	{
		m_fLength -= 5 / 60.0f;
		if (m_fLength < 1.0f)
		{
			m_fLength = 1.0f;
		}
	}

	//----- ŒvŽZ‚ÉŽg‚¤Šp“x‚ð‹‚ß‚é -----
	float ang = RAD_TO_DEG(atan2f(centerPos.y - pendulumPos.y, centerPos.x - pendulumPos.x));
	float ang2 = ang - 90.0f;

	//----- ˆÚ“®‘¬“x‚ðXV‚·‚é -----
	m_fMove += cosf(DEG_TO_RAD(ang)) * GRAVITY;
	m_fMove *= 0.99f;
	m_fMove += GamePad::GetLeftStick().x * 0.003f;
	if (IsKeyPress('A'))
	{
		m_fMove -= 0.003f;
	}
	if (IsKeyPress('D'))
	{
		m_fMove += 0.003f;
	}

	//----- ˆÚ“®‚³‚¹‚é -----
	DirectX::XMFLOAT3 pos(pendulumPos.x - centerPos.x, pendulumPos.y - centerPos.y, pendulumPos.z - centerPos.z);
	pos.x += cosf(DEG_TO_RAD(ang2)) * m_fMove;
	pos.y += sinf(DEG_TO_RAD(ang2)) * m_fMove;

	//----- ƒxƒNƒgƒ‹‚Ì³‹K‰» -----
	DirectX::XMVECTOR vec = DirectX::XMLoadFloat3(&pos);
	vec = DirectX::XMVector3Normalize(vec);
	DirectX::XMStoreFloat3(&pos, vec);

	//----- ‹——£‚ð•â³‚·‚é -----
	pos.x = pos.x * m_fLength;
	pos.y = pos.y * m_fLength;

	//----- ˆÚ“®æ‚ÌÀ•W‚ð‹‚ß‚é -----
	pos.x += centerPos.x;
	pos.y += centerPos.y;

	//----- ˆÚ“®—Ê‚Ìî•ñ‚ð“n‚· -----
	m_pPendulum->SetMove(DirectX::XMFLOAT3((pos.x - pendulumPos.x) * 1.5f, (pos.y - pendulumPos.y) * 1.5f, 0.0f));

	//----- ˆÚ“®‚ð”½‰f‚·‚é -----
	m_pPendulum->SetPos(DirectX::XMFLOAT3(pos.x, pos.y, pos.z));
}
