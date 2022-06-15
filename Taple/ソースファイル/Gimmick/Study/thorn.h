//==========================================
//									  thorn.h
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
#define THORN_SIZE_X (5)
#define THORN_SIZE_Y (1)
#define THORN_SIZE_Z (1)


class thorn :public Gimmick //‰æ•eƒNƒ‰ƒX
{
public:
	thorn(void);
	virtual ~thorn(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static Model *m_pModel;

private:
protected:
};

