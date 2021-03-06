//==========================================
//							 CharacterBase.h
//　キャラクター関連
//　制作者:AT12D171 No.11 小畠大季
//
//〜〜〜〜〜〜〜〜更新履歴〜〜〜〜〜〜〜〜〜
// 2020/10/28 制作開始
//〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜〜

// インクルードガード
#pragma once


//===== インクルード部 =====
#include "GameObject.h"


//===== クラス定義 =====
class CharacterBase : public GameObject
{
public:
	//===== メンバ関数 =====
	CharacterBase();
	virtual ~CharacterBase();

	// キャラクターの画像データが足元になるように描画で補正を行う
	void Draw();

protected:
	float m_fYaw;
	float m_fPitch;
	float m_fRoll;
};
