//==========================================
//									  Oven.h
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.29  ¼–{aŒá
//
//````````XV—š—ğ`````````
// 2020/11/** §ìŠJn
//		12/06
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "../Gimmick.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define OVEN_SIZE_X (12)
#define OVEN_SIZE_Y (7)
#define OVEN_SIZE_Z (1)


class Oven :public Gimmick //ƒtƒbƒNƒNƒ‰ƒX
{
public:
	Oven(void) {}
	virtual ~Oven(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;

protected:
};
