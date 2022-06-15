//==========================================
//							 CharacterBase.h
//@ƒLƒƒƒ‰ƒNƒ^[ŠÖ˜A
//@§ìÒ:AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ğ`````````
// 2020/10/28 §ìŠJn
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "GameObject.h"


//===== ƒNƒ‰ƒX’è‹` =====
class CharacterBase : public GameObject
{
public:
	//===== ƒƒ“ƒoŠÖ” =====
	CharacterBase();
	virtual ~CharacterBase();

	// ƒLƒƒƒ‰ƒNƒ^[‚Ì‰æ‘œƒf[ƒ^‚ª‘«Œ³‚É‚È‚é‚æ‚¤‚É•`‰æ‚Å•â³‚ğs‚¤
	void Draw();

protected:
	float m_fYaw;
	float m_fPitch;
	float m_fRoll;
};
