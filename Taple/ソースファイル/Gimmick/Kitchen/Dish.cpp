//==========================================
//							Dish.cpp
//	本関連
//　制作者:AT12D171 No.29 松本紳吾
//
//〜〜〜〜〜〜〜〜更新履歴〜〜〜〜〜〜〜〜〜
// 2020/11/** 制作開始
//		12/11 皿オブジェクト
//〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜

//===== インクルード部 =====
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
	// もし存在していなかったら
	if (!m_isSpawn)
	{
		// 出現するまでのカウント
		m_spawnCount++;
		// もし120以上だったら
		if (m_spawnCount >= 120)
		{
			m_isSpawn = true;	// 出現
			m_pos = m_spawnPos;	// 出現位置に移動
		}
		return;
		//**** ここから先は実行せずに終わる ****
	}


	if (m_fallCount<60)	// 60より少なかったら
	{
		// 落下するまでのカウント
		m_fallCount++;
		return;
		//**** ここから先は実行せずに終わる ****
	}


	// 落下する
	m_fallSpeed += GRAVITY;
	m_pos.y -= m_fallSpeed;

	// 境界判定
	if (m_pos.y <=m_DeathPawnPos)
	{
		m_isSpawn = false; // 存在しない
		m_spawnCount = 0;  // 初期化
		m_fallCount = 0;   // 初期化
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
	// 当たったら即死判定
	if (other->isPlayer())
	{
		dynamic_cast<Player*>(other)->ReSpawn();
	}
}
