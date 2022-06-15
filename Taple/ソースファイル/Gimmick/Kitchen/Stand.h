//=============================================
//									  Stand.h
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
#include "../Gimmick.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define STAND_SIZE_X (55)
#define STAND_SIZE_Y (12)
#define STAND_SIZE_Z (1)



class Stand :public Gimmick // ‘äƒNƒ‰ƒX
{
public:
	Stand(void) {}
	virtual ~Stand(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;

protected:
};



