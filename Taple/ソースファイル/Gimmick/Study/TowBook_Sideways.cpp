//==========================================
//									TowBooks_S.cpp
//	ñ{ä÷òA
//Å@êßçÏé“:AT12D171 No.12 îíà‰ã™ñÁ
//
//Å`Å`Å`Å`Å`Å`Å`Å`çXêVóöóÅ`Å`Å`Å`Å`Å`Å`Å`Å`
// 2020/12/10 êßçÏäJén
//		 
//Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`

//===== ÉCÉìÉNÉãÅ[Éhïî =====
#include "TowBook_Sideways.h"
#include "../../Shader.h"
#include "../../Defines.h"
#include "../../Collision.h"


Model* TowBooks_S::m_pModel = nullptr;





TowBooks_S::TowBooks_S()
{
}


TowBooks_S::~TowBooks_S()
{
	Uninit();

}

bool TowBooks_S::Init()
{
	for (int i = 0; i < TOW_BOOKS_S_PART_NUM; i++)
	{
		m_pCollision[i] = new GameObject();
		m_pCollision[i]->Init();
	}

	m_pCollision[0]->SetSize(DirectX::XMFLOAT3(UP_BOOK_SIZE_X, UP_BOOK_SIZE_Y, 1));
	m_pCollision[1]->SetSize(DirectX::XMFLOAT3(DOWN_BOOK_SIZE_X, DOWN_BOOK_SIZE_Y, 1));

	m_pCollision[0]->SetPos(DirectX::XMFLOAT3(UP_BOOK_SIZE_X / 2 + m_pos.x, -UP_BOOK_SIZE_Y / 2 + m_pos.y, 0));
	m_pCollision[1]->SetPos(DirectX::XMFLOAT3(DOWN_BOOK_SIZE_X / 2 + m_pos.x + 0.5f, -DOWN_BOOK_SIZE_Y / 2 + m_pos.y - 1 , 0));

	m_gimmickType = GIMMICK_BOOKS_BLOCK;
	m_isSingle = false;

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Study/TowBooks_S/pushpin.fbx"));
	}
	return true;
}


void TowBooks_S::Uninit(void)
{
	for (int i = 0; i < TOW_BOOKS_S_PART_NUM; i++)
	{
		SAFE_DELETE(m_pCollision[i]);
	}
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void TowBooks_S::Update()
{
}


void TowBooks_S::Draw()
{
	SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();

	for (int i = 0; i < TOW_BOOKS_S_PART_NUM; i++)
	{
		DirectX::XMFLOAT3 size(m_pCollision[i]->GetSize());
		DirectX::XMFLOAT3 pos(m_pCollision[i]->GetPos());
		SHADER->SetWorld(DirectX::XMMatrixScaling(size.x, size.y, size.z) * DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z));
		m_pCollision[i]->Draw();
	}
}


void TowBooks_S::SetCollision(GameObject *object)
{
	for (int i = 0; i < TOW_BOOKS_S_PART_NUM; i++)
	{
		RegisterCollision(object, m_pCollision[i]);
	}
}
