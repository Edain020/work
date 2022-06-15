//==========================================
//							WashingCuoboard.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.29 ¼–{aŒá
//
//````````XV—š—ð`````````
// 2020/11/** §ìŠJŽn
//		12/11 ô‚¢•¨HŠí’I(‘«ê+ƒ^[ƒUƒ“)
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Washingcupboard.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* WashingCuoboard::m_pModel = nullptr;



WashingCuoboard::~WashingCuoboard()
{
	Uninit();
}


bool WashingCuoboard::Init(void)
{
	m_gimmickType = GIMMICK_WASHINGCUPBOARD;
	m_size.x = WASHINGCUPBOARD_SIZE_X;
	m_size.y = WASHINGCUPBOARD_SIZE_Y;
	m_size.z = WASHINGCUPBOARD_SIZE_Z;

	m_targetPos.x = -(WASHINGCUPBOARD_SIZE_X / 2.0f + 0.5f);
	m_targetPos.y = -(WASHINGCUPBOARD_SIZE_Y / 4.0f);

	m_fMinLength = 0.0f;
	m_fRollSpeed = 20 / 60.0f;

	//m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Kitchen/WashingCuoboard/saku.fbx"));
	}
	return true;
}


void WashingCuoboard::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void WashingCuoboard::Draw()
{
	//SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();

	SHADER->SetWorld(DirectX::XMMatrixRotationY(180 * 3.141592f / 180)*DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f) *DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
	SHADER->SetTexture(NULL);
}
