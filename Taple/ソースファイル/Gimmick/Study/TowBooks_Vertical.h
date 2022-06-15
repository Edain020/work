//==========================================
//									  TowBooks_V.h
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ğ`````````
// 2020/01/03 §ìŠJn
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "../Gimmick.h"
#include "../../DrawBuffer.h" 
#include "../../FBX/FBXPlayer.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define TOW_BOOKS_V_SIZE_X (2)
#define TOW_BOOKS_V_SIZE_Y (7)
#define TOW_BOOKS_V_SIZE_Z (1)

#define TOW_BOOKS_V_PART_NUM (2)

#define LEFT_BOOK_SIZE_X (1)
#define LEFT_BOOK_SIZE_Y (7)

#define RIGHT_BOOK_SIZE_X (1)
#define RIGHT_BOOK_SIZE_Y (6)


class TowBooks_V :public Gimmick //–{ƒNƒ‰ƒX
{
public:
	TowBooks_V(void);
	virtual ~TowBooks_V(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual void SetCollision(GameObject *object);

private:
	static Model *m_pModel;
	GameObject *m_pCollision[8];
protected:
};

