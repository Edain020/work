//==========================================
//									  FallBook.h
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ğ`````````
// 2020/01/05 §ìŠJn
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "../Gimmick.h"
#include "../../DrawBuffer.h" 
#include "../../FBX/FBXPlayer.h"
#include "../../Sound.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define FALL_BOOK_SIZE_X (1)
#define FALL_BOOK_SIZE_Y (7)
#define FALL_BOOK_SIZE_Z (1)


//===== ƒNƒ‰ƒX’è‹` =====
class FallBook :public Gimmick	// –{ƒNƒ‰ƒX
{
public:
	FallBook(void);
	virtual ~FallBook(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void UpdatePlayer(Player *player);
	virtual void Draw(void);

private:
	bool m_isFallDown;
	float m_fAngle;
	float m_fFallSpeed;

	static Model *m_pModel;
	static Sound *m_pSE;
protected:
};
