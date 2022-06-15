//==========================================
//									Ladle.h
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.29  ¼–{aŒá
//
//````````XV—š—ğ`````````
// 2020/11/** §ìŠJn
//		12/11
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "../Gimmick.h"

//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define LADLE_SIZE_X (3)
#define LADLE_SIZE_Y (0)
#define LADLE_SIZE_Z (1)


class Ladle :public Gimmick //ƒtƒbƒNƒNƒ‰ƒX
{
public:
	Ladle(void) {}
	virtual ~Ladle(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;

protected:
};

