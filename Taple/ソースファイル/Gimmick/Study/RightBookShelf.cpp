//==========================================
//									RightBookShelf.cpp
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ğ`````````
// 2020/12/10 §ìŠJn
//		 
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "RightBookShelf.h"
#include "../../Shader.h"
#include "../../Defines.h"
#include "../../Collision.h"


Model* RightBookShelf::m_pModel = nullptr;



RightBookShelf::RightBookShelf()
{
}


RightBookShelf::~RightBookShelf()
{
	Uninit();
}


bool RightBookShelf::Init()
{
	for (int i = 0; i < RIGHT_BOOK_SHELF_PART_NUM; i++)
	{
		m_pCollision[i] = new GameObject();
		m_pCollision[i]->Init();
	}

	m_pCollision[0]->SetSize(DirectX::XMFLOAT3(RIGHT_UP_BLOCKL_SIZE_X, RIGHT_UP_BLOCKL_SIZE_Y, 1));
	m_pCollision[1]->SetSize(DirectX::XMFLOAT3(RIGHT_RIGHT_WALL_SIZE_X, RIGHT_RIGHT_WALL_SIZE_Y, 1));
	m_pCollision[2]->SetSize(DirectX::XMFLOAT3(RIGHT_IN_UP_BLOCK_X, RIGHT_IN_UP_BLOCK_Y, 1));
	m_pCollision[3]->SetSize(DirectX::XMFLOAT3(RIGHT_IN_DOWN_LEFT_BLOCK_SIZE_X, RIGHT_IN_DOWN_LEFT_BLOCK_SIZE_Y, 1));
	m_pCollision[4]->SetSize(DirectX::XMFLOAT3(RIGHT_IN_DOWN_RIGHT_BLOCK_SIZE_X, RIGHT_IN_DOWN_RIGHT_BLOCK_SIZE_Y, 1));
	m_pCollision[5]->SetSize(DirectX::XMFLOAT3(RIGHT_DOWN_BLOCK_SIZE_X, RIGHT_DOWN_BLOCK_SIZE_Y, 1));

	m_pCollision[0]->SetPos(DirectX::XMFLOAT3(RIGHT_UP_BLOCKL_SIZE_X / 2 + m_pos.x + 0.5f, -RIGHT_UP_BLOCKL_SIZE_Y / 2 + m_pos.y, 0));
	m_pCollision[1]->SetPos(DirectX::XMFLOAT3(RIGHT_RIGHT_WALL_SIZE_X / 2 + m_pos.x + 30, -RIGHT_RIGHT_WALL_SIZE_Y / 2 + m_pos.y + 0.5f - 1, 0));
	m_pCollision[2]->SetPos(DirectX::XMFLOAT3(RIGHT_IN_UP_BLOCK_X / 2 + m_pos.x + 1, -RIGHT_IN_UP_BLOCK_Y / 2 + m_pos.y - 12 + 1, 0));
	m_pCollision[3]->SetPos(DirectX::XMFLOAT3(RIGHT_IN_DOWN_LEFT_BLOCK_SIZE_X / 2 + m_pos.x + 1, -RIGHT_IN_DOWN_LEFT_BLOCK_SIZE_Y / 2 + m_pos.y - 23 + 1, 0));
	m_pCollision[4]->SetPos(DirectX::XMFLOAT3(RIGHT_IN_DOWN_RIGHT_BLOCK_SIZE_X / 2 + m_pos.x + 0.5f + 20, -RIGHT_IN_DOWN_RIGHT_BLOCK_SIZE_Y / 2 + m_pos.y  - 23 + 1, 0));
	m_pCollision[5]->SetPos(DirectX::XMFLOAT3(RIGHT_DOWN_BLOCK_SIZE_X / 2 + m_pos.x +0.5f, -RIGHT_DOWN_BLOCK_SIZE_Y / 2 + m_pos.y +0.5f - 34 + 1, 0));

	m_gimmickType = GIMMICK_SHELF_BLOCK;
	m_isSingle = false;

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Study/RightBookShelf/RightBookShelf.fbx"));
	}
	return true;
}


void RightBookShelf::Uninit(void)
{
	for (int i = 0; i < RIGHT_BOOK_SHELF_PART_NUM; i++)
	{
		SAFE_DELETE(m_pCollision[i]);
	}
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void RightBookShelf::Update()
{
}


void RightBookShelf::Draw()
{
	SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();

	for (int i = 0; i < RIGHT_BOOK_SHELF_PART_NUM; i++)
	{
		m_size = m_pCollision[i]->GetSize();
		m_pos = m_pCollision[i]->GetPos();
		SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
		m_pCollision[i]->Draw();
	}
}


void RightBookShelf::SetCollision(GameObject *object)
{
	for (int i = 0; i < RIGHT_BOOK_SHELF_PART_NUM; i++)
	{
		RegisterCollision(object, m_pCollision[i]);
	}
}
