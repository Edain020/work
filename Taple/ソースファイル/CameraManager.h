//==========================================
//							 CameraManager.h
//	�J�����Ǘ��֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/11/28 ����J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include <Windows.h>
#include <DirectXMath.h>
#include "Camera.h"


//===== �N���X��` =====
class CameraMgr
{
	// �C���X�^���X�����֎~
private:
	CameraMgr(void);

public:
	//===== �����o�֐� =====
	//----- �l�又�� -----
	static HRESULT Init(void);
	static void Uninit(void);
	static void Update(void);

	//----- �`��ݒ� -----
	static void DrawSetting(bool is3D);

	//----- �Q�b�^�[ -----
//	static Camera *GetCamera() { return m_pCamera; }
	static DirectX::XMFLOAT3 GetCameraPos(void) { return m_pCamera->GetPos(); }
	static DirectX::XMMATRIX GetCameraMatrix(void) { return m_pCamera->GetView(); }
	static DirectX::XMMATRIX GetInverseCameraMatrix(void) { return DirectX::XMMatrixInverse(NULL, m_pCamera->GetView()); }

	//----- �Z�b�^�[ -----
	static void SetLook(DirectX::XMFLOAT3 look) { m_pCamera->SetLook(look); }
	void SetRadius(float radius) { m_pCamera->SetRadius(radius); }
	void SetXZAngle(float angle) { m_pCamera->SetXZAngle(angle); }

private:
	//===== �����o�ϐ� =====
	static Camera *m_pCamera;
};
