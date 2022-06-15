//=============================================
//								RiceCooker.h
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.29 ¼–{aŒá
//
//````````XV—š—ğ``````````
// 2020/11/** §ìŠJn
//		12/11  †”ÑŠí
//``````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "../Gimmick.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define RICECOOKER_SIZE_X (8)
#define RICECOOKER_SIZE_Y (5)
#define RICECOOKER_SIZE_Z (1)



class RiceCooker :public Gimmick // —eŠíƒNƒ‰ƒX
{
public:
	RiceCooker(void);
	virtual ~RiceCooker(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

	virtual void SetCollision(GameObject *object);

private:
	static Model *m_pModel;

	GameObject *m_pCollision[2];
	GameObject *m_pDeathArea;
protected:
};
