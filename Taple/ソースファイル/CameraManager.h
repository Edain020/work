//==========================================
//							 CameraManager.h
//	ƒJƒƒ‰ŠÇ—ŠÖ˜A
//@§ìÒ:AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ğ`````````
// 2020/11/28 §ìŠJn
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include <Windows.h>
#include <DirectXMath.h>
#include "Camera.h"


//===== ƒNƒ‰ƒX’è‹` =====
class CameraMgr
{
	// ƒCƒ“ƒXƒ^ƒ“ƒX‰»‚ğ‹Ö~
private:
	CameraMgr(void);

public:
	//===== ƒƒ“ƒoŠÖ” =====
	//----- l‘åˆ— -----
	static HRESULT Init(void);
	static void Uninit(void);
	static void Update(void);

	//----- •`‰æİ’è -----
	static void DrawSetting(bool is3D);

	//----- ƒQƒbƒ^[ -----
//	static Camera *GetCamera() { return m_pCamera; }
	static DirectX::XMFLOAT3 GetCameraPos(void) { return m_pCamera->GetPos(); }
	static DirectX::XMMATRIX GetCameraMatrix(void) { return m_pCamera->GetView(); }
	static DirectX::XMMATRIX GetInverseCameraMatrix(void) { return DirectX::XMMatrixInverse(NULL, m_pCamera->GetView()); }

	//----- ƒZƒbƒ^[ -----
	static void SetLook(DirectX::XMFLOAT3 look) { m_pCamera->SetLook(look); }
	void SetRadius(float radius) { m_pCamera->SetRadius(radius); }
	void SetXZAngle(float angle) { m_pCamera->SetXZAngle(angle); }

private:
	//===== ƒƒ“ƒo•Ï” =====
	static Camera *m_pCamera;
};
