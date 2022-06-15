
// インクルード部
#pragma once


//===== インクルード部 =====
#include "Player.h"
#include "Defines.h"
#include "GimmickManager.h"
#include "Player.h"
#include "Timer.h"
#include "back_wall.h"
#include "Gimmick\Box.h"
#include "Sound.h"
#include "Image.h"
#include "Balloon.h"
#include "KidsRoom.h"
#include "Study.h"
#include "Kitchen.h"


//===== 定数・マクロ定義 =====
#define BALLOON_NUM	(20)

enum ModeKind
{
	MODE_GAME,		// ゲーム中
	MODE_CLEAR,		// クリア
	MODE_GAMEOVER,	// ゲームオーバー
};


//===== クラス定義 =====
class GameScene
{
public:
	GameScene(void) {}
	~GameScene(void) {}

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetStage(StageKind stage);

private:
	StageKind m_stage;
	ModeKind m_mode;

	Player		*m_pPlayer;		// プレイヤー
	BackWall	*m_pBackWall;	// 背景
	Box			*m_pGoal;		// ゴール
	Timer		*m_pTimer;		// タイマー

	// クリア&ゲームオーバー画面
	Image *m_pBlack;	// 画面を暗くする
	Image *m_pClear;	// クリア表示
	Image *m_pGameOver;	// ゲームオーバー
	Balloon *m_pBalloons[BALLOON_NUM];	// 風船(クリア演出)
	float m_fCnt;

	Sound *m_pSE;		// 決定音
	Sound *m_pClearSE;	// クリア音
	Sound *m_pGameOverSE;

	//----- ステージ -----
	KidsRoom	m_kidsRoom;	// 子供部屋
	Study		m_study;	// 書斎
	Kitchen		m_kitchen;	// キッチン
};
