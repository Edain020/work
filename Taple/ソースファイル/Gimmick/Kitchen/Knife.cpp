//==========================================
//									Knife.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.29 ¼–{aŒá
//
//````````XV—š—ð`````````
// 2020/12/04 §ìŠJŽn
//		
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Knife.h"
#include "../../Shader.h"
#include "../../Defines.h"
#include "../../Player.h"


Model* Knife::m_pModel = nullptr;



Knife::Knife()
	: m_isVertical(true)
	, m_fRadius(0.5)
	, m_fDeg(0)
{
}


Knife::Knife(bool isVertical, float radius, float seed)
	: m_isVertical(isVertical)
	, m_fRadius(radius)
	, m_fDeg(seed)
{
}


Knife::~Knife()
{
	Uninit();
}


bool Knife::Init()
{
	m_gimmickType = GIMMICK_KNIFE;
	m_size.x = KNIFE_SIZE_X;
	m_size.y = KNIFE_SIZE_Y;
	m_size.z = KNIFE_SIZE_Z;

	m_startPos = m_pos;

	//m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Kitchen/Knife/houtyou.fbx"));
	}
	return true;
}


void Knife::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void Knife::Update()
{
	m_fDeg += 90 / 60.0f;
	if (m_fDeg >= 360.0f)
	{
		m_fDeg -= 360.0f;
	}

	if (m_isVertical)
	{
		float pos = m_startPos.y + sinf(DEG_TO_RAD(m_fDeg)) * m_fRadius;
		m_move.y = pos - m_pos.y;
		m_pos.y = pos;
	}

}


void Knife::Draw()
{
	//SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();

	SHADER->SetWorld(DirectX::XMMatrixRotationY(180 * 3.141592f / 180)*DirectX::XMMatrixScaling(0.1f,0.1f, 0.1f) *DirectX::XMMatrixTranslation(m_pos.x, m_pos.y-2.5f, m_pos.z+4));
	m_pModel->Draw();
	SHADER->SetTexture(NULL);
}


void Knife::OnCollision(GameObject *other)
{
	// “–‚½‚Á‚½‚ç‘¦Ž€”»’è
	if (other->isPlayer())
	{
		dynamic_cast<Player*>(other)->ReSpawn();
	}
}
