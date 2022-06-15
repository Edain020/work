//==========================================
//									  Pin.h
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//		   AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ğ`````````
// 2020/11/** §ìŠJn
//		11/30 
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Pendulum.h"
#include "../DrawBuffer.h" 
#include "../FBX/FBXPlayer.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define PIN_SIZE_X (0.25f)
#define PIN_SIZE_Y (0.25f)
#define PIN_SIZE_Z (1)


class Pin :public Pendulum //‰æ•eƒNƒ‰ƒX
{
public:
	Pin(void);
	virtual ~Pin(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

	static Model *m_pModel;

private:
protected:
};

