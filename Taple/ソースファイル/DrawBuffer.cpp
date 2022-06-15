//==========================================
//							  DrawBuffer.cpp
//	描画関連
//　制作者:AT12D171 No.11 小畠大季
//
//～～～～～～～～更新履歴～～～～～～～～～
// 2020/10/07 制作開始
//		10/09 インデックスバッファを追加
//～～～～～～～～～～～～～～～～～～～～～

//===== インクルード部 =====
#include "DrawBuffer.h"



DrawBuffer::DrawBuffer() : m_pVertexBuffer(NULL), m_vtxSize(0), m_vtxCount(0), m_pIndexBuffer(NULL), m_idxCount(0)
{

}



DrawBuffer::~DrawBuffer()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}



HRESULT DrawBuffer::CreateVertexBuffer(void *pVtx, UINT size, UINT count, bool isWrite)
{
	//===== バッファの情報を設定 =====
	D3D11_BUFFER_DESC bufDesc = {};

	// バッファの大きさ
	bufDesc.ByteWidth = size * count;
	// バッファの使用方法
	if (isWrite)
	{
		bufDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		bufDesc.Usage = D3D11_USAGE_DEFAULT;
	}
	// バッファの使用先
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	//----- バッファの初期値を設定 -----
	D3D11_SUBRESOURCE_DATA subResource = {};
	// 初期化に使うデータの置き場所の指定
	subResource.pSysMem = pVtx;
	// 頂点バッファの作成
	HRESULT hr;
	ID3D11Device *pDevice = GetDevice();
	hr = pDevice->CreateBuffer(
		&bufDesc, &subResource,
		&m_pVertexBuffer);

	//----- そのほかの情報を設定 -----
	if (SUCCEEDED(hr))
	{
		m_vtxSize = size;
		m_vtxCount = count;
	}

	return hr;
}



HRESULT DrawBuffer::CreateIndexBuffer(const long* pIdx, UINT count)
{
	//===== バッファの情報を設定 =====
	D3D11_BUFFER_DESC bufDesc = {};
	
	// バッファの大きさ
	bufDesc.ByteWidth = sizeof(long) * count;
	// バッファの使用方法
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	// バッファの使用先
	bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	//----- バッファの初期値を設定 -----
	D3D11_SUBRESOURCE_DATA subResource = {};
	// 初期化に使うデータの置き場所の指定
	subResource.pSysMem = pIdx;
	// インデックスバッファの作成
	HRESULT hr;
	ID3D11Device *pDevice = GetDevice();
	hr = pDevice->CreateBuffer(
		&bufDesc, &subResource,
		&m_pIndexBuffer);

	//----- そのほかの情報を設定 -----
	if (SUCCEEDED(hr))
	{
		m_idxCount = count;
	}

	return hr;
}


// バッファの書き込み
void DrawBuffer::Write(void *pData)
{
	HRESULT hr;
	ID3D11DeviceContext *pContext = GetContext();
	D3D11_MAPPED_SUBRESOURCE mapResource;
	hr = pContext->Map(
	m_pVertexBuffer, 0,
	D3D11_MAP_WRITE_DISCARD,
	0, &mapResource);

	// Map関数で書き込みOKであれば
	// 実行
	if (SUCCEEDED(hr))
	{
		memcpy_s(
			mapResource.pData,
			m_vtxSize * m_vtxCount,
			pData,
			m_vtxSize * m_vtxCount);
	}

	// 書き込み終了
	pContext->Unmap(m_pVertexBuffer, 0);
}



void DrawBuffer::Draw(D3D11_PRIMITIVE_TOPOLOGY primitive)
{
	ID3D11DeviceContext *pContext = GetContext();
	// 頂点一つ当たりの大きさ
	UINT stride = m_vtxSize;
	// 頂点データの読み取り開始位置
	UINT offset = 0;

	// プリミティブの設定
	// TriangleList…頂点を3つずつに区切って描画
	// 例) [0,1,2] [3,4,5]
	//
	// TriangleStrip…参照場所を一つずつずらしながら描画
	// 例) [0,1,2] [1,2,3] [2,3,4] [3,4,5]
	pContext->IASetPrimitiveTopology(primitive);

	// 描画に使用するバッファの設定
	pContext->IASetVertexBuffers(
		0,	// GPUへの割り当て先
		1,	// 頂点バッファの数
		&m_pVertexBuffer,	// 頂点バッファ
		&stride,	// 頂点のサイズ
		&offset		// 読み取り開始位置
	);

	// 描画
	// インデックスバッファの有無で描画処理が若干異なる
	if (m_idxCount > 0)
	{
		// 描画に使用するインデックスバッファを設定
		pContext->IASetIndexBuffer(
			m_pIndexBuffer,
			// インデックス一つあたりの大きさ
			// 4byte = 32bit
			// 2byte = 64bit
			DXGI_FORMAT_R32_UINT,
			0);

		// インデックスバッファを使用して描画
		pContext->DrawIndexed(
			m_idxCount, 0, 0);
	}
	else
	{	// 頂点バッファのみで描画
		pContext->Draw(m_vtxCount, 0);
	}
}
