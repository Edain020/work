//==========================================
//									Knife.h
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.29 ¼–{aŒá
//
//````````XV—š—ğ`````````
// 2020/11/** §ìŠJn
//		12/04
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "../Gimmick.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define KNIFE_SIZE_X (0.25)
#define KNIFE_SIZE_Y (2)
#define KNIFE_SIZE_Z (1)


class Knife :public Gimmick
{
public:
	Knife(void);
	Knife(bool isVertical, float radius, float seed);
	virtual ~Knife(void);

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

