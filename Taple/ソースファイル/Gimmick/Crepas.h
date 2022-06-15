//==========================================
//									  Crepas.h
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
#include "../Sound.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define CREPAS_SIZE_X (7)
#define CREPAS_SIZE_Y (1)
#define CREPAS_SIZE_Z (1)


class Crepas :public Gimmick //ƒNƒŒƒpƒXƒNƒ‰ƒX
{
public:
	Crepas(void);
	virtual ~Crepas(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void UpdatePlayer(Player *player);
	virtual void Draw(void);
	
	virtual bool isClimb(void) { return true; }

private:
	float m_fMoveDis;
	bool m_isPlaySE;
	bool m_isStopSE;

	static Model *m_pModel;
	static Sound *m_pSE;
protected:
};

