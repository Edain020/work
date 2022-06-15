//==========================================
//									  PendulumClock.h
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ğ`````````
// 2020/01/03 §ìŠJn
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "../Gimmick.h"
#include "../../DrawBuffer.h" 
#include "../../FBX/FBXPlayer.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define PENDULUM_CLOCKL_SIZE_X (3)
#define PENDULUM_CLOCKL_SIZE_Y (3)
#define PENDULUM_CLOCKL_SIZE_Z (1)


class PendulumClock :public Gimmick //‰æ•eƒNƒ‰ƒX
{
public:
	PendulumClock(void);
	virtual ~PendulumClock(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;
protected:
};

