//==========================================
//									Number.h
//	UI(”š)ŠÖ˜A
//@§ìÒ:AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ğ`````````
// 2020/11/27 §ìŠJn
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "DrawBuffer.h"
#include <DirectXMath.h>


//===== ƒNƒ‰ƒX’è‹` =====
class Number	// 1Œ…‚Ì”š‚ğ•`‰æ‚·‚éƒNƒ‰ƒX
{
public:
	Number();
	~Number();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNum(int);
	void SetPos(DirectX::XMFLOAT3);
	void SetSize(DirectX::XMFLOAT3);

	DirectX::XMFLOAT3 GetSize(void) { return m_size; }

private:
	void UpdateUV(void);


	int m_nNum;	// ”š(0`9)
	DirectX::XMFLOAT3 m_pos;	// ’†SÀ•W
	DirectX::XMFLOAT3 m_size;	// ‘å‚«‚³
	Vertex *m_pVtx;			// ’¸“_À•W
	DrawBuffer m_buffer;	// •\¦—p‚Ìƒoƒbƒtƒ@
	static ID3D11ShaderResourceView *m_pNumberTex;	// ”š‚ÌƒeƒNƒXƒ`ƒƒ
};
