//==========================================
//									Cube.cpp
//	立方体関連
//　制作者:AT12D171 No.11 小畠大季
//
//～～～～～～～～更新履歴～～～～～～～～～
// 2020/10/07 制作開始
//		10/14 インデックスバッファを作成
//～～～～～～～～～～～～～～～～～～～～～

//===== インクルード部 =====
#include "Cube.h"
#include "Defines.h"



Cube::Cube() : m_posX(0), m_posY(0), m_posZ(0), m_width(1), m_height(1), m_depth(1), m_pVtx(nullptr)
{
	const float fHalfWidth = m_width / 2.0f;
	const float fHalfHeight = m_height / 2.0f;
	const float fHalfDepth = m_depth / 2.0f;
	//===== 頂点バッファ =====

	m_pVtx = new Vertex[8];
	for (int i = 0; i < 8; ++i)
	{
		m_pVtx[i].color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	m_pVtx[0].pos = DirectX::XMFLOAT3(-fHalfWidth,  fHalfHeight, -fHalfDepth);	m_pVtx[0].uv = DirectX::XMFLOAT2(0.0f, 0.0f);	// 0.左上手前
	m_pVtx[1].pos = DirectX::XMFLOAT3( fHalfWidth,  fHalfHeight, -fHalfDepth);	m_pVtx[1].uv = DirectX::XMFLOAT2(1.0f, 0.0f);	// 1.右上手前
	m_pVtx[2].pos = DirectX::XMFLOAT3(-fHalfWidth, -fHalfHeight, -fHalfDepth);	m_pVtx[2].uv = DirectX::XMFLOAT2(0.0f, 1.0f);	// 2.左下手前
	m_pVtx[3].pos = DirectX::XMFLOAT3( fHalfWidth, -fHalfHeight, -fHalfDepth);	m_pVtx[3].uv = DirectX::XMFLOAT2(1.0f, 1.0f);	// 3.右下手前
	m_pVtx[4].pos = DirectX::XMFLOAT3( fHalfWidth,  fHalfHeight,  fHalfDepth);	m_pVtx[4].uv = DirectX::XMFLOAT2(0.0f, 0.0f);	// 4.右上奥
	m_pVtx[5].pos = DirectX::XMFLOAT3(-fHalfWidth,  fHalfHeight,  fHalfDepth);	m_pVtx[5].uv = DirectX::XMFLOAT2(1.0f, 0.0f);	// 5.左上奥
	m_pVtx[6].pos = DirectX::XMFLOAT3( fHalfWidth, -fHalfHeight,  fHalfDepth);	m_pVtx[6].uv = DirectX::XMFLOAT2(0.0f, 1.0f);	// 6.右下奥
	m_pVtx[7].pos = DirectX::XMFLOAT3(-fHalfWidth, -fHalfHeight,  fHalfDepth);	m_pVtx[7].uv = DirectX::XMFLOAT2(1.0f, 1.0f);	// 7.左下奥

	//===== インデックスデータ =====
	long idx[] = {
		0,1,2,	1,3,2,	// 手前の面
		1,4,3,  4,6,3,	// 右の面
		4,5,6,	5,7,6,	// 奥の面
		5,0,7,  0,2,7,	// 左の面
		5,4,0,  4,1,0,	// 上の面
		2,3,7,  3,6,7,	// 下の面
	};

	// バッファ作成
	m_buffer.CreateVertexBuffer(m_pVtx, sizeof(Vertex), 8, true);
	m_buffer.CreateIndexBuffer(idx, sizeof(idx) / sizeof(long));
}


Cube::~Cube()
{
	SAFE_DELETE_ARRAY(m_pVtx);
}


void Cube::SetPos(float x, float y, float z)
{
	m_posX = x;
	m_posY = y;
	m_posZ = z;
}


void Cube::SetSize(float width, float height, float depth)
{
	m_width = width;
	m_height = height;
	m_depth = depth;


	const float fHalfWidth = m_width / 2.0f;
	const float fHalfHeight = m_height / 2.0f;
	const float fHalfDepth = m_depth / 2.0f;

	m_pVtx[0].pos = DirectX::XMFLOAT3(-fHalfWidth, fHalfHeight, -fHalfDepth);
	m_pVtx[1].pos = DirectX::XMFLOAT3(fHalfWidth, fHalfHeight, -fHalfDepth);
	m_pVtx[2].pos = DirectX::XMFLOAT3(-fHalfWidth, -fHalfHeight, -fHalfDepth);
	m_pVtx[3].pos = DirectX::XMFLOAT3(fHalfWidth, -fHalfHeight, -fHalfDepth);
	m_pVtx[4].pos = DirectX::XMFLOAT3(fHalfWidth, fHalfHeight, fHalfDepth);
	m_pVtx[5].pos = DirectX::XMFLOAT3(-fHalfWidth, fHalfHeight, fHalfDepth);
	m_pVtx[6].pos = DirectX::XMFLOAT3(fHalfWidth, -fHalfHeight, fHalfDepth);
	m_pVtx[7].pos = DirectX::XMFLOAT3(-fHalfWidth, -fHalfHeight, fHalfDepth);
}


void Cube::Draw()
{
	m_buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}
