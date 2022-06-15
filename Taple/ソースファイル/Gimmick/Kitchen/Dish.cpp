//==========================================
//							Dish.cpp
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.29 ¼–{aŒá
//
//````````XV—š—ğ`````````
// 2020/11/** §ìŠJn
//		12/11 MƒIƒuƒWƒFƒNƒg
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Dish.h"
#include "../../Shader.h"
#include "../../Defines.h"
#include "../../Player.h"



Model* Dish::m_pModel = nullptr;


Dish::Dish()
	: m_spawnPos(0.0f, 0.0f, 0.0f)
	, m_spawnCount(0)
	, m_isSpawn(false)
	, m_fallCount(0)
	, m_fallSpeed(0.0f)
	, m_DeathPawnPos(0)
{
}


Dish::Dish(float DeathPawnPos)
	: m_spawnPos(0.0f, 0.0f, 0.0f)
	, m_spawnCount(0)
	, m_isSpawn(false)
	, m_fallCount(0)
	, m_fallSpeed(0.0f)
	, m_DeathPawnPos(DeathPawnPos)
{
}


Dish::~Dish()
{
	Uninit();
}


bool Dish::Init()
{
	m_gimmickType = GIMMICK_DISH;
	m_size.x = DISH_SIZE_X;
	m_size.y = DISH_SIZE_Y;
	m_size.z = DISH_SIZE_Z;

	m_spawnPos = m_pos;

	//m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Kitchen/Dish/plate.fbx"));
	}
	return true;
}


void Dish::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void Dish::Update()
{
	// ‚à‚µ‘¶İ‚µ‚Ä‚¢‚È‚©‚Á‚½‚ç
	if (!m_isSpawn)
	{
		// oŒ»‚·‚é‚Ü‚Å‚ÌƒJƒEƒ“ƒg
		m_spawnCount++;
		// ‚à‚µ120ˆÈã‚¾‚Á‚½‚ç
		if (m_spawnCount >= 120)
		{
			m_isSpawn = true;	// oŒ»
			m_pos = m_spawnPos;	// oŒ»ˆÊ’u‚ÉˆÚ“®
		}
		return;
		//**** ‚±‚±‚©‚çæ‚ÍÀs‚¹‚¸‚ÉI‚í‚é ****
	}


	if (m_fallCount<60)	// 60‚æ‚è­‚È‚©‚Á‚½‚ç
	{
		// —‰º‚·‚é‚Ü‚Å‚ÌƒJƒEƒ“ƒg
		m_fallCount++;
		return;
		//**** ‚±‚±‚©‚çæ‚ÍÀs‚¹‚¸‚ÉI‚í‚é ****
	}


	// —‰º‚·‚é
	m_fallSpeed += GRAVITY;
	m_pos.y -= m_fallSpeed;

	// ‹«ŠE”»’è
	if (m_pos.y <=m_DeathPawnPos)
	{
		m_isSpawn = false; // ‘¶İ‚µ‚È‚¢
		m_spawnCount = 0;  // ‰Šú‰»
		m_fallCount = 0;   // ‰Šú‰»
		m_fallSpeed = 0.0f;
	}
}


void Dish::Draw()
{
	//SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();

	SHADER->SetWorld(DirectX::XMMatrixScaling(0.1f,0.1f,0.1f)*DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
	SHADER->SetTexture(NULL);
}


void Dish::OnCollision(GameObject *other)
{
	// “–‚½‚Á‚½‚ç‘¦€”»’è
	if (other->isPlayer())
	{
		dynamic_cast<Player*>(other)->ReSpawn();
	}
}
