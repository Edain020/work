//==========================================
//									  Clock.h
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ğ`````````
// 2020/12/04 §ìŠJn
//		 
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Gimmick.h"
#include "../DrawBuffer.h" 
#include "../FBX/FBXPlayer.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define CLOCK_SIZE_X (3)
#define CLOCK_SIZE_Y (3)
#define CLOCK_SIZE_Z (1)


class Clock :public Gimmick //‰æ•eƒNƒ‰ƒX
{
public:
	Clock(void);
	Clock(float radius, float seed);
	virtual ~Clock(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);


	static Model *m_pModel;

private:
	DirectX::XMFLOAT3 m_startPos;
	bool m_isVertical;
	float m_fRadius;
	float m_fDeg;
protected:
};

#pragma once
