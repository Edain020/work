//==========================================
//									  BooksBlock.h
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
#define BOOKS_BLOCK_SIZE_X (7)
#define BOOKS_BLOCK_SIZE_Y (8)
#define BOOKS_BLOCK_SIZE_Z (1)

#define BOOKS_BLOCK_PART_NUM (4)

#define BOOKS_BLOCK_ONE_SIZE_X (1)
#define BOOKS_BLOCK_ONE_SIZE_Y (5)

#define BOOKS_BLOCK_TWO_SIZE_X (3)
#define BOOKS_BLOCK_TWO_SIZE_Y (6)

#define BOOKS_BLOCK_THREE_SIZE_X (2)
#define BOOKS_BLOCK_THREE_SIZE_Y (7)

#define BOOKS_BLOCK_FOUR_SIZE_X (1)
#define BOOKS_BLOCK_FOUR_SIZE_Y (8)


class BooksBlock :public Gimmick //–{ƒNƒ‰ƒX
{
public:
	BooksBlock(void);
	virtual ~BooksBlock(void);

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

