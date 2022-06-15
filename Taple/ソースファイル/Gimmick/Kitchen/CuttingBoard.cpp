//==========================================
//						CuttingBoard.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.29 ¼–{aŒá
//
//````````XV—š—ð`````````
// 2020/11/** §ìŠJŽn
//		12/11 ‚Ü‚È”Â
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "CuttingBoard.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* CuttingBoard::m_pModel = nullptr;



CuttingBoard::~CuttingBoard()
{
	Uninit();
}


bool CuttingBoard::Init(void)
{
	m_gimmickType = GIMMICK_CUTTINGBOARD;
	m_size.x = CUTTINGBOARD_SIZE_X;
	m_size.y = CUTTINGBOARD_SIZE_Y;
	m_size.z = CUTTINGBOARD_SIZE_Z;

	//m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Kitchen/CuttingBoard/manaita.fbx"));
	}
	return true;
}


void CuttingBoard::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void CuttingBoard::Draw()
{
	//SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();

	SHADER->SetWorld(DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f) *DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
	SHADER->SetTexture(NULL);
}
