//==========================================
//									TowBooks_V.cpp
//	ñ{ä÷òA
//Å@êßçÏé“:AT12D171 No.12 îíà‰ã™ñÁ
//
//Å`Å`Å`Å`Å`Å`Å`Å`çXêVóöóÅ`Å`Å`Å`Å`Å`Å`Å`Å`
// 2020/12/10 êßçÏäJén
//		 
//Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`

//===== ÉCÉìÉNÉãÅ[Éhïî =====
#include "TowBooks_Vertical.h"
#include "../../Shader.h"
#include "../../Defines.h"
#include "../../Collision.h"


Model* TowBooks_V::m_pModel = nullptr;



TowBooks_V::TowBooks_V()
{
}


TowBooks_V::~TowBooks_V()
{
	Uninit();
}


bool TowBooks_V::Init()
{
	for (int i = 0; i < TOW_BOOKS_V_PART_NUM; i++)
	{
		m_pCollision[i] = new GameObject();
		m_pCollision[i]->Init();
	}

	m_pCollision[0]->SetSize(DirectX::XMFLOAT3(LEFT_BOOK_SIZE_X, LEFT_BOOK_SIZE_Y, 1));
	m_pCollision[1]->SetSize(DirectX::XMFLOAT3(RIGHT_BOOK_SIZE_X, RIGHT_BOOK_SIZE_Y, 1));

	m_pCollision[0]->SetPos(DirectX::XMFLOAT3(LEFT_BOOK_SIZE_X / 2 + m_pos.x, -LEFT_BOOK_SIZE_Y / 2 + m_pos.y, 0));
	m_pCollision[1]->SetPos(DirectX::XMFLOAT3(RIGHT_BOOK_SIZE_X / 2 + m_pos.x+1, -RIGHT_BOOK_SIZE_Y / 2 + m_pos.y - 1 + 0.5f, 0));
	

	m_gimmickType = GIMMICK_BOOKS_BLOCK;
	m_isSingle = false;


	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Study/TowBooks_V/pushpin.fbx"));
	}
	return true;
}


void TowBooks_V::Uninit(void)
{
	for (int i = 0; i < TOW_BOOKS_V_PART_NUM; i++)
	{
		SAFE_DELETE(m_pCollision[i]);
	}
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void TowBooks_V::Update()
{
}


void TowBooks_V::Draw()
{
	SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();

	for (int i = 0; i < TOW_BOOKS_V_PART_NUM; i++)
	{
		DirectX::XMFLOAT3 size(m_pCollision[i]->GetSize());
		DirectX::XMFLOAT3 pos(m_pCollision[i]->GetPos());
		SHADER->SetWorld(DirectX::XMMatrixScaling(size.x, size.y, size.z) * DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z));
		m_pCollision[i]->Draw();
	}
}


void TowBooks_V::SetCollision(GameObject *object)
{
	for (int i = 0; i < TOW_BOOKS_V_PART_NUM; i++)
	{
		RegisterCollision(object, m_pCollision[i]);
	}
}
