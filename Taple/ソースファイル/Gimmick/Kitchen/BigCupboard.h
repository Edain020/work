//==========================================
//									  Cupboard.h
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.29  ¼–{aŒá
//
//````````XV—š—ğ`````````
// 2020/11/** §ìŠJn
//		12/07
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "../Gimmick.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define BIGCUPBOARD_SIZE_X (40)
#define BIGCUPBOARD_SIZE_Y (1)
#define BIGCUPBOARD_SIZE_Z (1)


class BigCupboard :public Gimmick //‰æ•eƒNƒ‰ƒX
{
public:
	BigCupboard(void) {}
	virtual ~BigCupboard(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;
protected:
};

