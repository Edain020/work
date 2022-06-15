//==========================================
//									Eraser.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//		   AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ð`````````
// 2020/11/** §ìŠJŽn
//		11/30 
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Eraser.h"
#include "../Shader.h"
#include "../Defines.h"


Model* Eraser::m_pModel = nullptr;



Eraser::Eraser()
	: m_isVertical(true)
	, m_fRadius(5)
	, m_fDeg(0)
{
}


Eraser::Eraser(bool isVertical, float radius, float deg)
	: m_isVertical(isVertical)
	, m_fRadius(radius)
	, m_fDeg(deg)
{
}


Eraser::~Eraser()
{
	Uninit();
}


bool Eraser::Init()
{
	m_gimmickType = GIMMICK_ERASER;
	m_size.x = ERASER_SIZE_X;
	m_size.y = ERASER_SIZE_Y;
	m_size.z = ERASER_SIZE_Z;

	m_startPos = m_pos;

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Eraser/Eraser.fbx"));
	}
	return true;
}


void Eraser::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void Eraser::Update()
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
	else
	{
		float pos = m_startPos.x + sinf(DEG_TO_RAD(m_fDeg)) * m_fRadius;
		m_move.x = pos - m_pos.x;
		m_pos.x = pos;
	}
}


void Eraser::Draw()
{
	SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
}


void Eraser::OnCollision(GameObject *other)
{
	if(other->isPlayer())
	{
		DirectX::XMFLOAT3 pos(other->GetPos());
		pos.x += m_move.x;
		pos.y += m_move.y;
		other->SetPos(pos);
	}
}
