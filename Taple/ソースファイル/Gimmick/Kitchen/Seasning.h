//==========================================
//							Seasning.h
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.29 ¼–{aŒá
//		 
//
//````````XV—š—ğ`````````
// 2020/11/** §ìŠJn
//		01/23 
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "../Gimmick.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define SEASNING_SIZE_X (2)
#define SEASNING_SIZE_Y (3)
#define SEASNING_SIZE_Z (1)


class Seasning :public Gimmick
{
public:
	Seasning(void) {}
	virtual ~Seasning(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;

protected:
};
