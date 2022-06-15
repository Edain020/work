//==========================================
//									Camera.h
//�@�J�����֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/10/21 ����J�n
//		11/30 Bind�֐��œ������e�ƕ��s���e��؂�ւ��\��
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include <DirectXMath.h>	// DirectX���񋟂��Ă��鐔�w�n�̃��C�u����


//===== �N���X��` =====
class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	void Uninit();
	void Update();
	void Bind(bool isPerspective);

	DirectX::XMMATRIX GetView() { return m_viewMat; }
	DirectX::XMFLOAT3 GetPos() { return m_pos; }

	void SetLook(DirectX::XMFLOAT3 look) { m_look = look; }
	void SetRadius(float radius) { m_radius = radius; }
	void SetXZAngle(float angle) { m_xzAngle = angle; }

private:
	DirectX::XMMATRIX m_viewMat;
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_look;
	DirectX::XMFLOAT3 m_up;
	float m_angle;
	float m_near;
	float m_far;

	//----- �ɍ��W�n -----
	// XZ����ł̊p�x(0����-Z�̈ʒu)
	float m_xzAngle;
	// XZ����ŉ�]�����p�x(0���Ő���)
	float m_yAngle;
	// ���S����̋���
	float m_radius;
};
