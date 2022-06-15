//==========================================
//									Box.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//````````XV—š—ð`````````
// 2020/12/25 §ìŠJŽn
//		
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Box.h"
#include "../Shader.h"
#include "../Defines.h"
#include "../Main.h"
#include "../SceneManager.h"


Model* Box::m_pModel = nullptr;
Model* Box::m_pStrModel = nullptr;




Box::~Box()
{
	Uninit();
}


bool Box::Init(void)
{
	m_gimmickType = GIMMICK_BOX;
	m_size.x = BOX_SIZE_X;
	m_size.y = BOX_SIZE_Y;
	m_size.z = BOX_SIZE_Z;

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/ToolBox/ToolBox.fbx"));
	}
	if (m_pStrModel == nullptr)
	{
		m_pStrModel = new Model();
		m_pStrModel->LoadModel(ASSET("Model/ToolBox/GOAL.fbx"));
	}
	return true;
}


void Box::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
	SAFE_DELETE(m_pStrModel);
}


void Box::Update(void)
{
	m_fCnt += 1.0f;
	if (m_fCnt >= 360.0f)
	{
		m_fCnt -= 360.0f;
	}
}


void Box::Draw()
{
	SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y + 1, m_pos.z));
	m_pModel->Draw();

	SHADER->SetWorld(
		DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f)
		* DirectX::XMMatrixRotationY(DEG_TO_RAD(m_fCnt))
		* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y + 3 + sinf(DEG_TO_RAD(m_fCnt)), m_pos.z));
	m_pStrModel->Draw();
}
