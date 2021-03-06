
//===== インクルード部 =====
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

	//----- 長さを計算する -----
	DirectX::XMFLOAT3 pendulumPos(m_pPendulum->GetPos());
	DirectX::XMFLOAT3 centerPos = m_pos;
	centerPos.x += m_targetPos.x;
	centerPos.y += m_targetPos.y;
	centerPos.z += m_targetPos.z;

	m_fLength = sqrtf((centerPos.x - pendulumPos.x) * (centerPos.x - pendulumPos.x) + (centerPos.y - pendulumPos.y) * (centerPos.y - pendulumPos.y));

	//----- 長さを短くする -----
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

	//----- 計算に使う角度を求める -----
	float ang = RAD_TO_DEG(atan2f(centerPos.y - pendulumPos.y, centerPos.x - pendulumPos.x));
	float ang2 = ang - 90.0f;

	//----- 移動速度を更新する -----
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

	//----- 移動させる -----
	DirectX::XMFLOAT3 pos(pendulumPos.x - centerPos.x, pendulumPos.y - centerPos.y, pendulumPos.z - centerPos.z);
	pos.x += cosf(DEG_TO_RAD(ang2)) * m_fMove;
	pos.y += sinf(DEG_TO_RAD(ang2)) * m_fMove;

	//----- ベクトルの正規化 -----
	DirectX::XMVECTOR vec = DirectX::XMLoadFloat3(&pos);
	vec = DirectX::XMVector3Normalize(vec);
	DirectX::XMStoreFloat3(&pos, vec);

	//----- 距離を補正する -----
	pos.x = pos.x * m_fLength;
	pos.y = pos.y * m_fLength;

	//----- 移動先の座標を求める -----
	pos.x += centerPos.x;
	pos.y += centerPos.y;

	//----- 移動量の情報を渡す -----
	m_pPendulum->SetMove(DirectX::XMFLOAT3((pos.x - pendulumPos.x) * 1.5f, (pos.y - pendulumPos.y) * 1.5f, 0.0f));

	//----- 移動を反映する -----
	m_pPendulum->SetPos(DirectX::XMFLOAT3(pos.x, pos.y, pos.z));
}
