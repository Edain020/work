// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "DrawBuffer.h"
#include "Texture.h"
#include <DirectXMath.h>


//===== �N���X��` =====
class Image	// �摜�`��p�N���X
{
public:
	Image();
	~Image();

	void Draw(void);

	void LoadTexture(const char* pszFileName) { LoadTextureFromFile(pszFileName, &m_pTexture); }

	void SetPos(DirectX::XMFLOAT3 pos) { m_pos = pos; }
	void SetSize(DirectX::XMFLOAT3 size) { m_size = size; }

	void SetAlpha(float alpha);

private:
	DirectX::XMFLOAT3 m_pos;	// ���S���W
	DirectX::XMFLOAT3 m_size;	// �傫��

	Vertex *m_pVtx;	// ���_
	DrawBuffer m_buffer;		// �\���p�̃o�b�t�@
	ID3D11ShaderResourceView *m_pTexture;	// �\������摜
};
