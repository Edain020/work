//==========================================
//									LiftBook.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ð`````````
// 2020/12/10 §ìŠJŽn
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "LiftBook.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* LiftBook::m_pModel = nullptr;



LiftBook::LiftBook()
	: m_isVertical(true)
	, m_fRadius(5)
	, m_fDeg(0)
	, m_isPulsStart(true)
{
}


LiftBook::LiftBook(bool isVertical, float radius, float seed, bool isPulsStart)
	: m_isVertical(isVertical)
	, m_fRadius(radius)
	, m_fDeg(seed)
	, m_isPulsStart(isPulsStart)
{
}


LiftBook::~LiftBook()
{
	Uninit();
}


bool LiftBook::Init()
{
	m_gimmickType = GIMMICK_LIFT_BOOK;
	m_size.x = LIFT_BOOK_SIZE_X;
	m_size.y = LIFT_BOOK_SIZE_Y;
	m_size.z = LIFT_BOOK_SIZE_Z;

	m_startPos = m_pos;

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Study/BookSlimYoko5cm/BookSlimYoko5cm.fbx"));
	}
	return true;
}


void LiftBook::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void LiftBook::Update()
{
	if (m_isPulsStart)
	{
		m_fDeg += 60 / 60.0f;
	}
	else
	{
		m_fDeg -= 60 / 60.0f;
	}
	
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
	else
	{
		float pos = m_startPos.x + sinf(DEG_TO_RAD(m_fDeg)) * m_fRadius;
		m_move.x = pos - m_pos.x;
		m_pos.x = pos;
	}
}


void LiftBook::Draw()
{
	SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
}


void LiftBook::OnCollision(GameObject *other)
{
	if (other->isPlayer())
	{
		DirectX::XMFLOAT3 pos(other->GetPos());
		pos.x += m_move.x;
		pos.y += m_move.y;
		other->SetPos(pos);
	}
}
