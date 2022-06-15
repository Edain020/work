//==========================================
//									Lid.h
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.29 ¼–{aŒá
//
//````````XV—š—ğ`````````
// 2020/11/** §ìŠJn
//		12/11 ŠWi—eŠí—pj
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "../Gimmick.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define LID_SIZE_X (1)
#define LID_SIZE_Y (6)
#define LID_SIZE_Z (1)


class Lid :public Gimmick // ŠWƒNƒ‰ƒX
{
public:
	Lid(void);
	virtual ~Lid(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void UpdatePlayer(Player *player);
	virtual void Draw(void);

private:
	bool m_isFallDown;
	float m_fAngle;
	float m_fFallSpeed;

	static Model *m_pModel;
protected:
};

