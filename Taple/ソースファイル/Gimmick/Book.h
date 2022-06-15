//==========================================
//									  Book.h
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//		   AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ğ`````````
// 2020/11/** §ìŠJn
//		11/30 
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Gimmick.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define BOOK_SIZE_X (7)
#define BOOK_SIZE_Y (2)
#define BOOK_SIZE_Z (1)


//===== ƒNƒ‰ƒX’è‹` =====
class Book :public Gimmick	// –{ƒNƒ‰ƒX
{
public:
	Book(void) {}
	virtual ~Book(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;
protected:
};
