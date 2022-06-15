//==========================================
//									  LeftBookShelf.h
//	ñ{ä÷òA
//Å@êßçÏé“:AT12D171 No.12 îíà‰ã™ñÁ
//		   AT12D171 No.11 è¨î©ëÂãG
//
//Å`Å`Å`Å`Å`Å`Å`Å`çXêVóöóÅ`Å`Å`Å`Å`Å`Å`Å`Å`
// 2020/12/11 êßçÏäJén
//Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`Å`

// ÉCÉìÉNÉãÅ[ÉhÉKÅ[Éh
#pragma once


//===== ÉCÉìÉNÉãÅ[Éhïî =====
#include "../Gimmick.h"
#include "../../DrawBuffer.h" 
#include "../../FBX/FBXPlayer.h"


//===== íËêîÅEÉ}ÉNÉçíËã` =====
#define LEFT_BOOK_SHELF_SIZE_X (30)
#define LEFT_BOOK_SHELF_SIZE_Y (45)
#define LEFT_BOOK_SHELF_SIZE_Z (1)

#define LEFT_BOOK_SHELF_PART_NUM (8)

#define LEFT_LEFT_WALL_SIZE_X (1)
#define LEFT_LEFT_WALL_SIZE_Y (32)

#define LEFT_UP_BLOCK_SIZE_X (30)
#define LEFT_UP_BLOCK_SIZE_Y (1)

#define LEFT_UP_RIGHT_WALL_SIZE_X (1)
#define LEFT_UP_RIGHT_WALL_SIZE_Y (4)

#define LEFT_DOWN_RIGHT_WALL_SIZE_X (1)
#define LEFT_DOWN_RIGHT_WALL_SIZE_Y (22)

#define LEFT_IN_UP_BLOCK_SIZE_X	(24)
#define LEFT_IN_UP_BLOCK_SIZE_Y	(1)

#define LEFT_IN_DOWN_BLOCK_SIZE_X (22)
#define LEFT_IN_DOWN_BLOCK_SIZE_Y (1)

#define LEFT_DOWN_LEFT_BLOCK_SIZE_X (15)
#define LEFT_DOWN_LEFT_BLOCK_SIZE_Y (12)

#define LEFT_DOWN_RIGHT_BLOCK_SIZE_X (10)
#define LEFT_DOWN_RIGHT_BLOCK_SIZE_Y (12)





class LeftBookShelf :public Gimmick
{
public:
	LeftBookShelf(void);
	virtual ~LeftBookShelf(void);

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

