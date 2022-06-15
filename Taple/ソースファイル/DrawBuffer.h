//==========================================
//								DrawBuffer.h
//	描画関連
//　制作者:AT12D171 No.11 小畠大季
//
//～～～～～～～～更新履歴～～～～～～～～～
// 2020/10/07 制作開始
//		10/09 インデックスバッファを追加
//～～～～～～～～～～～～～～～～～～～～～

// インクルードガード
#pragma once


//===== インクルード部 =====
#include <Windows.h>
#include "DirectX.h"
#include <DirectXMath.h>


//===== 構造体定義 =====
struct Vertex	// 頂点情報
{
	DirectX::XMFLOAT3 pos;		// x,y,z
	DirectX::XMFLOAT4 color;	// r,g,b,a
	DirectX::XMFLOAT2 uv;		// u,v
};


//===== クラス定義 =====
class DrawBuffer	// 描画関連用
{
public:
	DrawBuffer();
	~DrawBuffer();

	HRESULT CreateVertexBuffer(
		// 描画に必要な頂点のデータ
		void *pVtx,
		// 一つ当たりの頂点のデータサイズ
		UINT size,
		// 描画する頂点の数
		UINT count,
		// 頂点バッファの書き換えが可能か
		bool isWrite = false
	);

	HRESULT CreateIndexBuffer(
		const long* pIdx,
		UINT count
	);

	// バッファの書き込み
	void Write(void *pData);

	// バッファの描画
	void Draw(
		// ポリゴンの描画方法
		D3D11_PRIMITIVE_TOPOLOGY primitive);

private:
	// 頂点バッファ
	ID3D11Buffer *m_pVertexBuffer;
	// 頂点のデータサイズ
	UINT m_vtxSize;
	// 頂点の数
	UINT m_vtxCount;

	// インデックスバッファ
	ID3D11Buffer *m_pIndexBuffer;
	// インデックスの数
	UINT m_idxCount;
};
