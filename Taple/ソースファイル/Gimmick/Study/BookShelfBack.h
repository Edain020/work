//==========================================
//									  BookShelfBack.h
//	–{’I”wŒiŠÖ˜A
//@§ìÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ğ`````````
// 2020/01/22 §ìŠJn
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "../../DrawBuffer.h" 
#include "../../FBX/FBXPlayer.h"
#include "../Gimmick.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define BOOK_SHELF_BACK_SIZE_X (30)
#define BOOK_SHELF_BACK_SIZE_Y (45)
#define BOOK_SHELF_BACK_SIZE_Z (1)


//===== ƒNƒ‰ƒX’è‹` =====
class BookShelfBack :public Gimmick	// –{’I”wŒiƒNƒ‰ƒX
{
public:
	BookShelfBack(void);
	virtual ~BookShelfBack(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;
protected:
};
