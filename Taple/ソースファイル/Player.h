//==========================================
//								  Player.cpp
//	プレイヤー関連
//　制作者:AT12D171 No.11 小畠大季
//
//～～～～～～～～更新履歴～～～～～～～～～
// 2020/10/30 制作開始
//		12/10 メンバ変数に状態を表すフラグを複数個追加
//～～～～～～～～～～～～～～～～～～～～～

// インクルードガード
#pragma once


//===== インクルード部 =====
#include <list>
#include "CharacterBase.h"
#include "Model.h"
#include "Gimmick/Gimmick.h"
#include "Sound.h"


//===== 前方宣言 =====
class Tape;


//===== クラス定義 =====
class Player : public CharacterBase
{
public:
	//===== メンバ関数 =====
	Player(void);
	virtual ~Player(void);

	//----- 四大処理 -----
	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void ReSpawn(void);
	void Roll(float rollSpeed);
	
	virtual bool isPlayer(void) { return true; }

	//----- セッター -----
	void SetTarget(Gimmick *pTarget) { m_pTarget = pTarget; }
	void SetGround(bool isGround) { m_isGround = isGround; }
	void SetGrab(bool isGrab) { m_isGrab = isGrab; }
	void SetExtendTape(bool isExtend) { m_isExtendTape = isExtend; }
	void SetRoll(bool isRoll) { m_isRoll = isRoll; }
	void SetCanRoll(bool canRoll) { m_canRoll = canRoll; }


	//----- ゲッター -----
	Gimmick* GetTarget(void) { return m_pTarget; }
	float GetDir(void) { return m_fDir; }
	bool isGround(void) { return m_isGround; }

private:
	//===== メンバ変数 =====
	Gimmick *m_pTarget;	// ターゲット

	float m_fRotSpeed;		// 回転速度
	float m_fDir;			// 向き
	float m_fYaw;			// y方向の回転(目標値)
	float m_fTargetSizeCnt;	// ターゲットの目印のサイズ
	bool m_isGround;		// 接地判定
	bool m_isGrab;			// 物をつかんでいるかどうか
	bool m_isExtendTape;	// テープを伸ばしているかどうか
	bool m_isRoll;			// テープを巻いているかどうか
	bool m_canRoll;			// テープを離せるかどうか

	Model *m_pBodyModel;	// テープ本体のモデル
	Model *m_pEyeModel;		// テープの目のモデル
	Model *m_pMouthModel;	// テープの口のモデル
	Tape *m_pTape;			// テープ

	Sound *m_pTapeSE;	// サウンド

	DirectX::XMFLOAT3 m_targetRange;
	std::list<Gimmick*> m_pTargetList;

	//===== メンバ関数 =====
	void Move(void);		// 移動関係
	void ControlTape(void);	// テープ関係
};
