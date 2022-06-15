//==========================================
//							Stand.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.29 ¼–{aŒá
//
//````````XV—š—ð`````````
// 2020/11/** §ìŠJŽn
//		12/11 ƒRƒ“ƒ‚Ì‘ä(‘«ê)
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Stand.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* Stand::m_pModel = nullptr;


Stand::~Stand()
{
	Uninit();
}


bool Stand::Init(void)
{
	m_gimmickType = GIMMICK_STAND;
	m_size.x = STAND_SIZE_X;
	m_size.y = STAND_SIZE_Y;
	m_size.z = STAND_SIZE_Z;

	//m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Kitchen/Stand/Desk.fbx"));
	}
	return true;
}


void Stand::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void Stand::Draw()
{
	//SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();

	SHADER->SetWorld(DirectX::XMMatrixScaling(1.85f, 1, 1) *DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
	SHADER->SetTexture(NULL);
}
