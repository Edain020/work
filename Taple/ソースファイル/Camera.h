//==========================================
//									Camera.h
//　カメラ関連
//　制作者:AT12D171 No.11 小畠大季
//
//〜〜〜〜〜〜〜〜更新履歴〜〜〜〜〜〜〜〜〜
// 2020/10/21 制作開始
//		11/30 Bind関数で透視投影と平行投影を切り替え可能に
//〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜

// インクルードガード
#pragma once


//===== インクルード部 =====
#include <DirectXMath.h>	// DirectXが提供している数学系のライブラリ


//===== クラス定義 =====
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

	//----- 極座標系 -----
	// XZ軸上での角度(0°で-Zの位置)
	float m_xzAngle;
	// XZ軸上で回転した角度(0°で水平)
	float m_yAngle;
	// 中心からの距離
	float m_radius;
};
