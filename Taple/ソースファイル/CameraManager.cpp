//==========================================
//						   CameraManager.cpp
//	�J�����Ǘ��֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/11/28 ����J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

//===== �C���N���[�h�� =====
#include "CameraManager.h"
#include "Defines.h"
#include "DirectX.h"


//----- �ÓI�����o�ϐ��̒�` -----
Camera* CameraMgr::m_pCamera = {};



HRESULT CameraMgr::Init(void)
{
	if (m_pCamera == nullptr)
	{
		m_pCamera = new Camera();
	}

	return S_OK;
}


void CameraMgr::Uninit(void)
{
	SAFE_DELETE(m_pCamera);
}


void CameraMgr::Update(void)
{
	m_pCamera->Update();
}


void CameraMgr::DrawSetting(bool is3D)
{
	m_pCamera->Bind(is3D);
	EnableZBuffer(is3D);
}
