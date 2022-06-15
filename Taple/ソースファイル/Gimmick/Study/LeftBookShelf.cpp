//==========================================
//									LeftBookShelf.cpp
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ğ`````````
// 2020/12/10 §ìŠJn
//		 
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "LeftBookShelf.h"
#include "../../Shader.h"
#include "../../Defines.h"
#include "../../Collision.h"


Model* LeftBookShelf::m_pModel = nullptr;



LeftBookShelf::LeftBookShelf()
{
}


LeftBookShelf::~LeftBookShelf()
{
	Uninit();
}


bool LeftBookShelf::Init()
{
	for (int i = 0; i < LEFT_BOOK_SHELF_PART_NUM; i++)
	{
		m_pCollision[i] = new GameObject();
		m_pCollision[i]->Init();
	}

	m_pCollision[0]->SetSize(DirectX::XMFLOAT3(LEFT_UP_BLOCK_SIZE_X, LEFT_UP_BLOCK_SIZE_Y, 1));
	m_pCollision[1]->SetSize(DirectX::XMFLOAT3(LEFT_LEFT_WALL_SIZE_X, LEFT_LEFT_WALL_SIZE_Y, 1));
	m_pCollision[2]->SetSize(DirectX::XMFLOAT3(LEFT_UP_RIGHT_WALL_SIZE_X, LEFT_UP_RIGHT_WALL_SIZE_Y, 1));
	m_pCollision[3]->SetSize(DirectX::XMFLOAT3(LEFT_DOWN_RIGHT_WALL_SIZE_X, LEFT_DOWN_RIGHT_WALL_SIZE_Y, 1));
	m_pCollision[4]->SetSize(DirectX::XMFLOAT3(LEFT_IN_UP_BLOCK_SIZE_X, LEFT_IN_UP_BLOCK_SIZE_Y, 1));
	m_pCollision[5]->SetSize(DirectX::XMFLOAT3(LEFT_IN_DOWN_BLOCK_SIZE_X, LEFT_IN_DOWN_BLOCK_SIZE_Y, 1));
	m_pCollision[6]->SetSize(DirectX::XMFLOAT3(LEFT_DOWN_LEFT_BLOCK_SIZE_X, LEFT_DOWN_LEFT_BLOCK_SIZE_Y, 1));
	m_pCollision[7]->SetSize(DirectX::XMFLOAT3(LEFT_DOWN_RIGHT_BLOCK_SIZE_X, LEFT_DOWN_RIGHT_BLOCK_SIZE_Y, 1));
	
	m_pCollision[0]->SetPos(DirectX::XMFLOAT3(LEFT_UP_BLOCK_SIZE_X / 2 + m_pos.x + 0.5f-1, -LEFT_UP_BLOCK_SIZE_Y / 2 + m_pos.y, 0));
	m_pCollision[1]->SetPos(DirectX::XMFLOAT3(LEFT_LEFT_WALL_SIZE_X / 2 + m_pos.x, -LEFT_LEFT_WALL_SIZE_Y / 2 + m_pos.y - 1 + 0.5f, 0));
	m_pCollision[2]->SetPos(DirectX::XMFLOAT3(LEFT_UP_RIGHT_WALL_SIZE_X / 2 + m_pos.x + 30-1, -LEFT_UP_RIGHT_WALL_SIZE_Y / 2 + m_pos.y - 1 + 0.5f, 0));
	m_pCollision[3]->SetPos(DirectX::XMFLOAT3(LEFT_DOWN_RIGHT_WALL_SIZE_X / 2 + m_pos.x + 30-1, -LEFT_DOWN_RIGHT_WALL_SIZE_Y / 2 + m_pos.y -11, 0));
	m_pCollision[4]->SetPos(DirectX::XMFLOAT3(LEFT_IN_UP_BLOCK_SIZE_X / 2 + m_pos.x + 6 + 0.5f-1, -LEFT_IN_UP_BLOCK_SIZE_Y / 2 + m_pos.y - 11, 0));
	m_pCollision[5]->SetPos(DirectX::XMFLOAT3(LEFT_IN_DOWN_BLOCK_SIZE_X / 2 + m_pos.x + 1 + 0.5f-1, -LEFT_IN_DOWN_BLOCK_SIZE_Y / 2 + m_pos.y - 22, 0));
	m_pCollision[6]->SetPos(DirectX::XMFLOAT3(LEFT_DOWN_LEFT_BLOCK_SIZE_X / 2 + m_pos.x, -LEFT_DOWN_LEFT_BLOCK_SIZE_Y / 2 + m_pos.y - 33 + 0.5f, 0));
	m_pCollision[7]->SetPos(DirectX::XMFLOAT3(LEFT_DOWN_RIGHT_BLOCK_SIZE_X / 2 + m_pos.x + 20 + 0.5f-1, -LEFT_DOWN_RIGHT_BLOCK_SIZE_Y / 2 + m_pos.y - 33 + 0.5f, 0));


	m_gimmickType = GIMMICK_SHELF_BLOCK;
	m_isSingle = false;

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Study/LeftBookShelf/LeftBookShelf.fbx"));
	}
	return true;
}


void LeftBookShelf::Uninit(void)
{
	for (int i = 0; i < LEFT_BOOK_SHELF_PART_NUM; i++)
	{
		SAFE_DELETE(m_pCollision[i]);
	}
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void LeftBookShelf::Update()
{
}


void LeftBookShelf::Draw()
{
	SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();


	for (int i = 0; i < LEFT_BOOK_SHELF_PART_NUM; i++)
	{
		m_pCollision[i]->Draw();
	}
}


void LeftBookShelf::SetCollision(GameObject *object)
{
	for (int i = 0; i < LEFT_BOOK_SHELF_PART_NUM; i++)
	{
		RegisterCollision(object, m_pCollision[i]);
	}
}
