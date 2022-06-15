//==========================================
//									  RightBookShelf.h
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
#define RIGHT_BOOK_SHELF_SIZE_X (30)
#define RIGHT_BOOK_SHELF_SIZE_Y (45)
#define RIGHT_BOOK_SHELF_SIZE_Z (1)

#define RIGHT_BOOK_SHELF_PART_NUM (6)

#define RIGHT_UP_BLOCKL_SIZE_X (30)
#define RIGHT_UP_BLOCKL_SIZE_Y (1)

#define RIGHT_RIGHT_WALL_SIZE_X (1)
#define RIGHT_RIGHT_WALL_SIZE_Y (32)

#define RIGHT_IN_UP_BLOCK_X (29)
#define RIGHT_IN_UP_BLOCK_Y (1)

#define RIGHT_IN_DOWN_LEFT_BLOCK_SIZE_X (13)
#define RIGHT_IN_DOWN_LEFT_BLOCK_SIZE_Y (1)

#define RIGHT_IN_DOWN_RIGHT_BLOCK_SIZE_X (4)
#define RIGHT_IN_DOWN_RIGHT_BLOCK_SIZE_Y (1)

#define RIGHT_DOWN_BLOCK_SIZE_X (30)
#define RIGHT_DOWN_BLOCK_SIZE_Y (12)

class RightBookShelf :public Gimmick //âÊïeÉNÉâÉX
{
public:
	RightBookShelf(void);
	virtual ~RightBookShelf(void);

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

