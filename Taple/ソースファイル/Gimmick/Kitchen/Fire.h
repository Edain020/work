//==========================================
//								StoveFire.h
//	ƒrƒ‹ƒ{[ƒh(‰Î)ŠÖ˜A
//@§ìÒ:AT12D171 No.29 ¼–{aŒá
//
//````````XV—š—ğ`````````
// //`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "../Gimmick.h"


//===== ƒNƒ‰ƒX’è‹` =====
class Fire : public Gimmick
{
public:
	Fire();
	virtual ~Fire();

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual void OnCollision(GameObject *other);

private:
	void UpdateUV(void);

	int m_nTexCnt;
	int m_nTexNum;	//ƒeƒNƒXƒ`ƒƒ”Ô†
	Vertex *m_pVtx;			// ’¸“_À•W
	DrawBuffer m_buffer;	// •\¦—p‚Ìƒoƒbƒtƒ@

	static ID3D11ShaderResourceView *m_pTex;	// ‰Î‚ÌƒeƒNƒXƒ`ƒƒ
};
