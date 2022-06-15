//==========================================
//									  Box.h
//	‚¨‚à‚¿‚á” iƒS[ƒ‹jŠÖ˜A
//@§ìÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ğ`````````
// 2020/12/25 §ìŠJn 
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "../DrawBuffer.h" 
#include "../FBX/FBXPlayer.h"
#include "Gimmick.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define BOX_SIZE_X (7)
#define BOX_SIZE_Y (2)
#define BOX_SIZE_Z (1)


//===== ƒNƒ‰ƒX’è‹` =====
class Box :public Gimmick	// –{ƒNƒ‰ƒX
{
public:
	Box(void)
		: m_fCnt(0.0f)
	{}
	virtual ~Box(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual bool isClimb(void) { return true; }

private:
	static Model *m_pModel;
	static Model *m_pStrModel;

	float m_fCnt;
protected:
};
