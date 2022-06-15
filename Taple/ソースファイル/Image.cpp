//===== インクルード部 =====
#include "Image.h"
#include "Texture.h"
#include "Shader.h"
#include "Defines.h"



Image::Image()
	: m_pos(0, 0, 0)
	, m_size(1, 1, 1)
	, m_pTexture(nullptr)
{
	float halfSize = 0.5f;

	m_pVtx = new Vertex[4];

	for (int i = 0; i < 4; ++i)
	{
		m_pVtx[i].color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	m_pVtx[0].pos = DirectX::XMFLOAT3(-halfSize, halfSize, 0.0f);
	m_pVtx[1].pos = DirectX::XMFLOAT3(halfSize, halfSize, 0.0f);
	m_pVtx[2].pos = DirectX::XMFLOAT3(-halfSize, -halfSize, 0.0f);
	m_pVtx[3].pos = DirectX::XMFLOAT3(halfSize, -halfSize, 0.0f);

	m_pVtx[0].uv = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_pVtx[1].uv = DirectX::XMFLOAT2(1.0f, 0.0f);
	m_pVtx[2].uv = DirectX::XMFLOAT2(0.0f, 1.0f);
	m_pVtx[3].uv = DirectX::XMFLOAT2(1.0f, 1.0f);

	// バッファ作成
	m_buffer.CreateVertexBuffer(m_pVtx, sizeof(Vertex), 4, true);
}


Image::~Image()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_DELETE_ARRAY(m_pVtx);
}


void Image::Draw(void)
{
	SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	SHADER->SetTexture(m_pTexture);
	m_buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	SHADER->SetTexture(NULL);
}


void Image::SetAlpha(float alpha)
{
	for (int i = 0; i < 4; ++i)
	{
		m_pVtx[i].color.w = alpha;
	}

	m_buffer.Write(m_pVtx);
}
