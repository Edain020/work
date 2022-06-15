//==========================================
//								   Gimmick.h
//	ギミック関連
//　制作者:AT12D171 No.12 白井喬也
//		   AT12D171 No.11 小畠大季
//
//～～～～～～～～更新履歴～～～～～～～～～
// 2020/11/** 制作開始
//		11/30 設計を変更
//		12/11 ギミックタイプの種類を変更
//～～～～～～～～～～～～～～～～～～～～～

// インクルードガード
#pragma once

//===== インクルード部 =====
#include "../GameObject.h"
#include "../Model.h"


// 前方宣言
class Player;

//===== 列挙型宣言 =====
enum GimmickType	// ギミックの種類
{
	GIMMICK_NONE,
	GIMMICK_DEFAULT,

	GIMMICK_DESK,
	GIMMICK_BOOK,
	GIMMICK_RULER,
	GIMMICK_CLOSET,
	
	GIMMICK_SHELF_BLOCK,
	GIMMICK_BOOKS_BLOCK,
	
	GIMMICK_ERASER,
	GIMMICK_LIFT_BOOK,
	GIMMICK_PENDULUM,
	
	GIMMICK_CREPAS,
	GIMMICK_PIN,
	
	GIMMICK_CLOCK,

	GIMMICK_THORN,
	GIMMICK_FALL_BOOK,
	GIMMICK_NAIL,

	GIMMICK_BOX,

	//  キッチンルーム
	GIMMICK_KNIFE,              // ナイフ
	GIMMICK_HOOK,               // フック
	GIMMICK_CUPBOARD,           // 食器棚
	GIMMICK_BIGCUPBOARD,        // 大きい食器棚
	GIMMICK_KITCHENSHELVES,     // キッチン棚
	GIMMICK_GOALKITCHENSHELVES, // ゴールキッチン棚
	GIMMICK_STAND,              // 台
	GIMMICK_STOVE,              // コンロ
	GIMMICK_LADLE,              // お玉
	GIMMICK_CONTAINER,          // 容器
	GIMMICK_LID,                // 蓋
	GIMMICK_CUTTINGBOARD,       // まな板
	GIMMICK_DISH,               // 皿
	GIMMICK_WASHINGCUPBOARD,    // 洗い物食器棚
	GIMMICK_OVEN,               // オーブン
	GIMMICK_MICROWAVE,          // 電子レンジ
	GIMMICK_FAUCET,             // 蛇口
	GIMMICK_RICECOOKER,         // 炊飯器
	GIMMICK_SEASNING,           // 調味料
	GIMMICK_STOVEFIRE,          // コンロ
	GIMMICK_WLSHELF,            // 横L字棚
	GIMMICK_HLSHELF,
};


//===== クラス定義 =====
class Gimmick : public GameObject // ギミッククラス
{
public:
	//===== コンストラクタ・デストラクタ=====

	// デフォルトコンストラクタ
	Gimmick(void);
	// デストラクタ
	virtual ~Gimmick(void);

	//===== 四大処理 =====
	virtual void Uninit(void);

	// プレイヤーから呼び出す更新処理
	virtual void UpdatePlayer(Player *player) {}
	// 掴んだ時に呼び出す関数
	virtual void Grab(Player *player) {}
	// 当たり判定が複数ある場合に当たり判定を設定する関数
	virtual void SetCollision(GameObject *object) {}


	//===== ゲッター =====
	DirectX::XMFLOAT3 GetTargetPos(void) { return m_targetPos; }
	int GetGimmickType(void) { return m_gimmickType; }
	bool isTarget(void) { return m_isTarget; }
	bool isSingle(void) { return m_isSingle; }
	
	//==== セッター ====
	DirectX::XMFLOAT3 SetTargetPos(const DirectX::XMFLOAT3 pos) { m_targetPos = pos; }

protected:
	//===== メンバ変数 =====
	DirectX::XMFLOAT3 m_targetPos;	// ターゲットする位置
	GimmickType m_gimmickType;	// ギミックの種類
	bool m_isTarget;			// ターゲットできるかどうか
	bool m_isSingle;			// 単体かどうか
};
