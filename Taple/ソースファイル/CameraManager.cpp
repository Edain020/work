//==========================================
//						   CameraManager.cpp
//	ƒJƒƒ‰ŠÇ—ŠÖ˜A
//@§ìŽÒ:AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ð`````````
// 2020/11/28 §ìŠJŽn
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "CameraManager.h"
#include "Defines.h"
#include "DirectX.h"


//----- Ã“Iƒƒ“ƒo•Ï”‚Ì’è‹` -----
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
