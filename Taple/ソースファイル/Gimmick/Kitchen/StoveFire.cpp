//===== インクルード部 =====
#include "StoveFire.h"
#include "Stove.h"
#include "../../Defines.h"
#include "../../Player.h"



StoveFire::~StoveFire()
{
	Uninit();
}


bool StoveFire::Init()
{
	m_size = DirectX::XMFLOAT3(STOVE_SIZE_X, STOVE_SIZE_Y * 2, 0);

	for (int i = 0; i < STOVEFIRE_NUM; ++i)
	{
		m_pFires[i] = new Fire();
		m_pFires[i]->SetSize(DirectX::XMFLOAT3(m_size.x / STOVEFIRE_NUM, m_size.y, m_size.z));
		m_pFires[i]->SetPos(DirectX::XMFLOAT3(m_pos.x + m_size.x / 2.0f - (m_pFires[i]->GetSize().x * i + m_pFires[i]->GetSize().x / 2.0f), m_pos.y, m_pos.z));
		m_pFires[i]->Init();
	}

	return true;
}


void StoveFire::Uninit()
{
	for (int i = 0; i < STOVEFIRE_NUM; ++i)
	{
		SAFE_DELETE(m_pFires[i]);
	}
}


void StoveFire::Update()
{
	for (auto fire : m_pFires)
	{
		fire->Update();
	}
}


void StoveFire::Draw()
{
	for (auto fire : m_pFires)
	{
		fire->Draw();
	}
}


void StoveFire::OnCollision(GameObject *other)
{
	// 当たったら即死判定
	if (other->isPlayer())
	{
		dynamic_cast<Player*>(other)->ReSpawn();
	}
}
