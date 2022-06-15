//==========================================
//									Camera.h
//@ƒJƒƒ‰ŠÖ˜A
//@§ìÒ:AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ğ`````````
// 2020/10/21 §ìŠJn
//		11/30 BindŠÖ”‚Å“§‹“Š‰e‚Æ•½s“Š‰e‚ğØ‚è‘Ö‚¦‰Â”\‚É
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include <DirectXMath.h>	// DirectX‚ª’ñ‹Ÿ‚µ‚Ä‚¢‚é”ŠwŒn‚Ìƒ‰ƒCƒuƒ‰ƒŠ


//===== ƒNƒ‰ƒX’è‹` =====
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

	//----- ‹ÉÀ•WŒn -----
	// XZ²ã‚Å‚ÌŠp“x(0‹‚Å-Z‚ÌˆÊ’u)
	float m_xzAngle;
	// XZ²ã‚Å‰ñ“]‚µ‚½Šp“x(0‹‚Å…•½)
	float m_yAngle;
	// ’†S‚©‚ç‚Ì‹——£
	float m_radius;
};
