// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "Image.h"


//===== �N���X��` =====
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
