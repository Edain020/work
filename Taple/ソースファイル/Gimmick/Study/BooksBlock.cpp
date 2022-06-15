//==========================================
//									BooksBlock.cpp
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ğ`````````
// 2020/12/10 §ìŠJn
//		 
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "BooksBlock.h"
#include "../../Shader.h"
#include "../../Defines.h"
#include "../../Collision.h"


Model* BooksBlock::m_pModel = nullptr;



BooksBlock::BooksBlock()
{
}


BooksBlock::~BooksBlock()
{
	Uninit();
}


bool BooksBlock::Init()
{
	for (int i = 0; i < BOOKS_BLOCK_PART_NUM; i++)
	{
		m_pCollision[i] = new GameObject();
		m_pCollision[i]->Init();
	}

	m_pCollision[0]->SetSize(DirectX::XMFLOAT3(BOOKS_BLOCK_ONE_SIZE_X, BOOKS_BLOCK_ONE_SIZE_Y, 1));
	m_pCollision[1]->SetSize(DirectX::XMFLOAT3(BOOKS_BLOCK_TWO_SIZE_X, BOOKS_BLOCK_TWO_SIZE_Y, 1));
	m_pCollision[2]->SetSize(DirectX::XMFLOAT3(BOOKS_BLOCK_THREE_SIZE_X, BOOKS_BLOCK_THREE_SIZE_Y, 1));
	m_pCollision[3]->SetSize(DirectX::XMFLOAT3(BOOKS_BLOCK_FOUR_SIZE_X, BOOKS_BLOCK_FOUR_SIZE_Y, 1));

	m_pCollision[0]->SetPos(DirectX::XMFLOAT3(BOOKS_BLOCK_ONE_SIZE_X / 2 + m_pos.x, -BOOKS_BLOCK_ONE_SIZE_Y / 2 + m_pos.y - 3, 0));
	m_pCollision[1]->SetPos(DirectX::XMFLOAT3(BOOKS_BLOCK_TWO_SIZE_X / 2 + m_pos.x + 1, -BOOKS_BLOCK_TWO_SIZE_Y / 2 + m_pos.y - 2 + 0.5f, 0));
	m_pCollision[2]->SetPos(DirectX::XMFLOAT3(BOOKS_BLOCK_THREE_SIZE_X / 2 + m_pos.x + 4 - 0.5f, -BOOKS_BLOCK_THREE_SIZE_Y / 2 + m_pos.y - 1, 0));
	m_pCollision[3]->SetPos(DirectX::XMFLOAT3(BOOKS_BLOCK_FOUR_SIZE_X / 2 + m_pos.x + 6, -BOOKS_BLOCK_FOUR_SIZE_Y / 2 + m_pos.y + 0.5f, 0));

	m_gimmickType = GIMMICK_BOOKS_BLOCK;
	m_isSingle = false;

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Study/BooksGroup/BookGroup.fbx"));
	}
	return true;
}


void BooksBlock::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void BooksBlock::Update()
{
}


void BooksBlock::Draw()
{
	SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();

	for (int i = 0; i < BOOKS_BLOCK_PART_NUM; i++)
	{
		DirectX::XMFLOAT3 size(m_pCollision[i]->GetSize());
		DirectX::XMFLOAT3 pos(m_pCollision[i]->GetPos());
		SHADER->SetWorld(DirectX::XMMatrixScaling(size.x, size.y, size.z) * DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z));
		m_pCollision[i]->Draw();
	}
}


void BooksBlock::SetCollision(GameObject *object)
{
	for (int i = 0; i < BOOKS_BLOCK_PART_NUM; i++)
	{
		RegisterCollision(object, m_pCollision[i]);
	}
}
