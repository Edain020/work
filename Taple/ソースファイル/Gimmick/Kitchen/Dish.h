//==========================================
//								 Dish.h
//	–{ŠÖ˜A
//@§ìÒ:AT12D171 No.29 ¼–{aŒá
//
//````````XV—š—ğ`````````
// 2020/11/** §ìŠJn
//		12/11
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "../Gimmick.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define DISH_SIZE_X (1)
#define DISH_SIZE_Y (4)
#define DISH_SIZE_Z (1)


class Dish :public Gimmick //MƒNƒ‰ƒX
{
public:
	Dish(void);
	Dish(float DesPawnPos); // Á‚¦‚éÀ•Wî•ñ
	virtual ~Dish(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual void OnCollision(GameObject *other);

private:
	DirectX::XMFLOAT3 m_spawnPos;
	int m_spawnCount; 
	bool m_isSpawn;
	int m_fallCount;
	float m_fallSpeed;
	float m_DeathPawnPos;	// ‰ºŒÀÀ•W(‚±‚±‚æ‚è‰º‚É—‚¿‚½‚çÁ‚¦‚é)

	static Model *m_pModel;

protected:
};