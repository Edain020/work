// インクルードガード
#pragma once


//===== インクルード部 =====
#include "Image.h"


//===== クラス定義 =====
class Balloon
{
public:
	Balloon()
		: m_pos(0.0f, 0.0f, 0.0f)
		, m_pImage(nullptr)
	{}
	~Balloon();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetPos(DirectX::XMFLOAT3 pos);

private:
	DirectX::XMFLOAT3 m_pos;
	Image *m_pImage;
};
