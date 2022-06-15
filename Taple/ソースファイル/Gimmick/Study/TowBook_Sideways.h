//==========================================
//									  TowBooks_S.h
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
#define TOW_BOOKS_S_SIZE_X (7)
#define TOW_BOOKS_S_SIZE_Y (2)
#define TOW_BOOKS_S_SIZE_Z (1)

#define TOW_BOOKS_S_PART_NUM (2)

#define UP_BOOK_SIZE_X (6)
#define UP_BOOK_SIZE_Y (1)

#define DOWN_BOOK_SIZE_X (7)
#define DOWN_BOOK_SIZE_Y (1)


class TowBooks_S :public Gimmick //–{ƒNƒ‰ƒX
{
public:
	TowBooks_S(void);
	virtual ~TowBooks_S(void);

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

