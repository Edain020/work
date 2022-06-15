//==========================================
//						RiceCooker.cpp
//	ñ{ä÷òA
//Å@êßçÏé“:AT12D171 No.29 èºñ{êaå·
//
//Å`Å`Å`Å`Å`Å`Å`Å`çXêVóöóÅ`Å`Å`Å`Å`Å`Å`Å`Å`
// 2020/11/** êßçÏäJén
//		12/11 óeäÌ
//Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`

//===== ÉCÉìÉNÉãÅ[Éhïî =====
#include "RiceCooker.h"
#include "../../Shader.h"
#include "../../Defines.h"
#include "../../Player.h"
#include "../../Collision.h"


Model* RiceCooker::m_pModel = nullptr;



RiceCooker::RiceCooker(void)
{
	m_isSingle = false;
}


RiceCooker::~RiceCooker()
{
	Uninit();
}


bool RiceCooker::Init(void)
{
	m_gimmickType = GIMMICK_RICECOOKER;
	m_size.x = RICECOOKER_SIZE_X;
	m_size.y = RICECOOKER_SIZE_Y;
	m_size.z = RICECOOKER_SIZE_Z;

//	m_pCube = new Cube();

	for (int i = 0; i < 2; ++i)
	{
		m_pCollision[i] = new GameObject();
		m_pCollision[i]->SetSize(DirectX::XMFLOAT3(0.5f, RICECOOKER_SIZE_Y, RICECOOKER_SIZE_Z));
		m_pCollision[i]->SetPos(DirectX::XMFLOAT3(m_pos.x + ((m_size.x - 0.5f) / 2) * (i * 2 - 1), m_pos.y - 1.0f, m_pos.z));
		m_pCollision[i]->Init();
	}

	m_pDeathArea = new GameObject();
	m_pDeathArea->SetSize(DirectX::XMFLOAT3(RICECOOKER_SIZE_X - 1, 1.0f, 1.0f));
	m_pDeathArea->SetPos(DirectX::XMFLOAT3(m_pos.x, m_pos.y + m_size.y / 2 - 2.0f, m_pos.z));
	m_pDeathArea->Init();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Kitchen/RiceCooker/suihanki.fbx"));
	}
	return true;
}


void RiceCooker::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void RiceCooker::Draw()
{
	//SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();
	//for (int i = 0; i < 2; ++i)
	//{
	//	m_pCollision[i]->Draw();
	//}
	//m_pDeathArea->Draw();

	SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y-2, m_pos.z));
	m_pModel->Draw();
	SHADER->SetTexture(NULL);
}


void RiceCooker::SetCollision(GameObject *object)
{
	for (int i = 0; i < 2; i++)
	{
		RegisterCollision(object, m_pCollision[i]);
	}

	if (CheckCollision(object, m_pDeathArea))
	{
		if (object->isPlayer())
		{
			dynamic_cast<Player*>(object)->ReSpawn();
		}
	}
}
