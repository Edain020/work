//==========================================
//									  Eraser.h
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
#define ERASER_SIZE_X (2)
#define ERASER_SIZE_Y (0.5f)
#define ERASER_SIZE_Z (1)


class Eraser :public Gimmick //Á‚µƒSƒ€ƒNƒ‰ƒX
{
public:
	Eraser(void);
	Eraser(bool isVertical, float radius, float deg);
	virtual ~Eraser(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual void OnCollision(GameObject *other);

private:
	DirectX::XMFLOAT3 m_startPos;
	bool m_isVertical;
	float m_fRadius;
	float m_fDeg;

	static Model *m_pModel;
protected:

};


