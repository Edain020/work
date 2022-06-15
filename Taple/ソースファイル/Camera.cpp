//==========================================
//								  Camera.cpp
//�@�J�����֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/10/21 ����J�n
//		11/30 Bind�֐��œ������e�ƕ��s���e��؂�ւ��\��
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

//===== �C���N���[�h�� =====
#include "Camera.h"
#include "Shader.h"
#include "Defines.h"
#include "GamePad.h"
#include "Defines.h"
#include "SceneManager.h"



Camera::Camera(void)
	: m_pos(0, 0, 5)
	, m_look(0, 0, 0)
	, m_up(0, 1, 0)
	, m_angle(60.0f)
	, m_near(0.5f)
	, m_far(500.0f)
	, m_xzAngle(0.0f)
	, m_yAngle(0.0f)
	, m_radius(11.0f)
//	, m_radius(100.0f)
{

}



Camera::~Camera(void)
{
	Uninit();
}



void Camera::Init(void)
{
	if (SCENE_MANAGER->GetScene() == SCENE_STAGESELECT)
	{
		m_angle = 0.0f;
	}
}



void Camera::Uninit(void)
{
}



void Camera::Update(void)
{
	// �J�����ʒu�v�Z
	float xzRad = m_xzAngle * 3.141592f / 180.0f;
	float yRad = m_yAngle * 3.141592f / 180.0f;

	if (SCENE_MANAGER->GetScene() == SCENE_GAME)
	{
		m_look.y += 3;
	}

	m_pos.x = m_look.x + cosf(yRad) * sinf(xzRad) * m_radius;
	m_pos.z = m_look.z + cosf(yRad) * -cosf(xzRad) * m_radius;
	m_pos.y = m_look.y + sinf(yRad) * m_radius;
}



void Camera::Bind(bool isPerspective)
{
	if (isPerspective)	// 3D
	{
		//----- �������e -----

		m_viewMat = DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(m_pos.x, m_pos.y, m_pos.z, 0),
			DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0),
			DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0)
		);
		SHADER->SetView(m_viewMat);
		SHADER->SetProjection(DirectX::XMMatrixPerspectiveFovLH(m_angle * 3.141592f / 180.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, m_near, m_far));	

		// �J�����̍��W���V�F�[�_�ɐݒ�
		SHADER->SetPSCameraPos(m_pos);
	}
	else	// 2D
	{
		//----- ���s���e -----
		SHADER->SetView(DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(0, 0, -1, 0),
			DirectX::XMVectorSet(0, 0, 0, 0),
			DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0)
		));
		SHADER->SetProjection(DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, m_near, m_far));
	}
}
