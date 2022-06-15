// インクルードガード
#pragma once


//===== インクルード部 =====
#include "Fire.h"
#include "../Gimmick.h"


//===== 定数・マクロ定義 =====
#define STOVEFIRE_NUM	(4)


//===== クラス定義 =====
class StoveFire	: public Gimmick
{
public:
	StoveFire() {}
	virtual ~StoveFire();

	virtual bool Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	virtual void OnCollision(GameObject *other);

private:
	Fire *m_pFires[STOVEFIRE_NUM];
};
