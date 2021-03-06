//==========================================
//								 Dish.h
//	本関連
//　制作者:AT12D171 No.29 松本紳吾
//
//〜〜〜〜〜〜〜〜更新履歴〜〜〜〜〜〜〜〜〜
// 2020/11/** 制作開始
//		12/11
//〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜

// インクルードガード
#pragma once


//===== インクルード部 =====
#include "../Gimmick.h"


//===== 定数・マクロ定義 =====
#define DISH_SIZE_X (1)
#define DISH_SIZE_Y (4)
#define DISH_SIZE_Z (1)


class Dish :public Gimmick //皿クラス
{
public:
	Dish(void);
	Dish(float DesPawnPos); // 消える座標情報
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
	float m_DeathPawnPos;	// 下限座標(ここより下に落ちたら消える)

	static Model *m_pModel;

protected:
};