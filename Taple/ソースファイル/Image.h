// インクルードガード
#pragma once


//===== インクルード部 =====
#include "DrawBuffer.h"
#include "Texture.h"
#include <DirectXMath.h>


//===== クラス定義 =====
class Image	// 画像描画用クラス
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
	DirectX::XMFLOAT3 m_pos;	// 中心座標
	DirectX::XMFLOAT3 m_size;	// 大きさ

	Vertex *m_pVtx;	// 頂点
	DrawBuffer m_buffer;		// 表示用のバッファ
	ID3D11ShaderResourceView *m_pTexture;	// 表示する画像
};
