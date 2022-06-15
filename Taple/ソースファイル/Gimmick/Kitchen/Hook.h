
//==========================================
//									  Hook.h
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
#include "../Pendulum.h"

//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define HOOK_SIZE_X (1)
#define HOOK_SIZE_Y (2)
#define HOOK_SIZE_Z (1)


class Hook :public Pendulum //ƒtƒbƒNƒNƒ‰ƒX
{
public:
	Hook(void) {}
	virtual ~Hook(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;

protected:
};
