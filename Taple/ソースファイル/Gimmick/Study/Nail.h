//==========================================
//									  Nail.h
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
#include "../Pendulum.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define NAIL_SIZE_X (0.25f)
#define NAIL_SIZE_Y (0.25f)
#define NAIL_SIZE_Z (1)


class Nail :public Pendulum //‰æ•eƒNƒ‰ƒX
{
public:
	Nail(void);
	virtual ~Nail(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static Model *m_pModel;

private:
protected:
};

