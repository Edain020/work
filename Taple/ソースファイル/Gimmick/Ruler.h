//==========================================
//									  Ruler.h
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
#define RULER_SIZE_X (20)
#define RULER_SIZE_Y (0.25f)
#define RULER_SIZE_Z (1)



class Ruler :public Gimmick
{
public:
	Ruler(void);
	virtual ~Ruler(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static Model *m_pModel;

private:
protected:
};
