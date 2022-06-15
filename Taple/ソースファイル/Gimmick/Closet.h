//==========================================
//									  Closet.h
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
#include "Gimmick.h"
#include "../DrawBuffer.h" 
#include "../FBX/FBXPlayer.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define CLOSET_SIZE_X (10)
#define CLOSET_SIZE_Y (16)
#define CLOSET_SIZE_Z (1)


//===== ƒNƒ‰ƒX’è‹` =====
class Closet :public Gimmick //ƒNƒ[ƒ[ƒbƒgƒNƒ‰ƒX
{
public:
	Closet(void) {}
	virtual ~Closet(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;
protected:
};
