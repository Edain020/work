//=============================================
//									  Stove.h
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.29 ¼–{aŒá
//
//````````XV—š—ğ``````````
// 2020/11/** §ìŠJn
//		12/11  ƒRƒ“ƒ
//``````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "../Gimmick.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define STOVE_SIZE_X (7)
#define STOVE_SIZE_Y (1)
#define STOVE_SIZE_Z (1)



class Stove :public Gimmick // ƒRƒ“ƒƒNƒ‰ƒX
{
public:
	Stove() {}
	virtual ~Stove(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

	virtual bool isClimb(void) { return true; }

private:
	static Model *m_pModel;

protected:
};



