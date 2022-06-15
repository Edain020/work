//===== インクルード部 =====
#include "TitleObj.h"
#include "Defines.h"



TitleObj::TitleObj()
{

}


TitleObj::~TitleObj()
{
	Uninit();
}


bool TitleObj::Init()
{
	m_pBodyModel = new Model();
	m_pBodyModel->LoadModel(ASSET("Model/Player/tepukunn_karada_gf.fbx"));
	m_pEyeModel = new Model();
	m_pEyeModel->LoadModel(ASSET("Model/Player/tepukunn_me.fbx"));
	m_pMouthModel = new Model();
	m_pMouthModel->LoadModel(ASSET("Model/Player/tepukunn_kuti.fbx"));
	m_size = DirectX::XMFLOAT3(1.0f / 12, 1.0f / 12, 1.0f / 12);
	m_rot.y = 210.0f;
	m_pos.y = -1.0f;
	return true;
}


void TitleObj::Uninit()
{
	SAFE_DELETE(m_pCube)
	SAFE_DELETE(m_pBodyModel);
	SAFE_DELETE(m_pEyeModel);
	SAFE_DELETE(m_pMouthModel);
}


void TitleObj::Update()
{
	m_rot.z -= DEG_TO_RAD(360 / 60.0f);
}


void TitleObj::Draw()
{
	SHADER->SetWorld(
		DirectX::XMMatrixScaling(1.2f * 2, 1.2f * 2, 1.2f * 2)
		* DirectX::XMMatrixRotationRollPitchYaw(m_rot.x, DEG_TO_RAD(m_rot.y), m_rot.z)
		* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	);
	m_pBodyModel->Draw();

	SHADER->SetWorld(
		DirectX::XMMatrixScaling(1.0f / 16 * 2, 1.0f / 16 * 2, 1.0f / 16 * 2)
		* DirectX::XMMatrixRotationRollPitchYaw(m_rot.x, DEG_TO_RAD(m_rot.y), m_rot.z)
		* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	);
	m_pEyeModel->Draw();
	m_pMouthModel->Draw();

//	SHADER->SetWorld(
//		DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z)
//		* DirectX::XMMatrixRotationRollPitchYaw(m_rot.x, m_rot.y, m_rot.z)
//		* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
//	);
}
