//=============================================
//						    WashingCuoboard.h
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.29 ¼–{aŒá
//
//````````XV—š—ğ``````````
// 2020/11/** §ìŠJn
//		12/11  ƒRƒ“ƒ‚Ì‘ä(‘«ê)
//``````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "../Pendulum.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define WASHINGCUPBOARD_SIZE_X (15)
#define WASHINGCUPBOARD_SIZE_Y (6)
#define WASHINGCUPBOARD_SIZE_Z (1)



class WashingCuoboard :public Pendulum // ‘äƒNƒ‰ƒX
{
public:
	WashingCuoboard(void) {}
	virtual ~WashingCuoboard(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;

protected:
};




