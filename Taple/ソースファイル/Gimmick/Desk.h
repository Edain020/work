//==========================================
//									  Desk.h
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
#include "../DrawBuffer.h" 
#include "../FBX/FBXPlayer.h"
#include "Gimmick.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define DESK_SIZE_X (30)
#define DESK_SIZE_Y (12)
#define DESK_SIZE_Z (1)


class Desk :public Gimmick
{
public:
	Desk(void) {}
	virtual ~Desk(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;
protected:
};

