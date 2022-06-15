#pragma once

// ゲームタイトル
#define GAME_TITLE	("Taple")

// FPS数
#define FPS	(60)

// 画面サイズ
#define SCREEN_WIDTH (1024)
#define SCREEN_HEIGHT (768)

// シーン管理
enum SceneKind
{
	SCENE_TITLE = 0,	// タイトル
	SCENE_STAGESELECT,	// ステージセレクト
	SCENE_GAME,			// ゲーム

	SCENE_MAX	// シーン数
};

// ステージ管理
enum StageKind
{
	STAGE_KIDSROOM = 0,	// 子供部屋
//	STAGE_STUDY,		// 書斎
	STAGE_KITCHEN,		// キッチン

	RETURN_TITLE,		// タイトルに戻る

	STAGE_MAX	// ステージ選択数
};


// リソースパス
#define ASSET(path)	("Assets/"path)

// デリート
#define SAFE_DELETE(p)	if(p){delete p; p = nullptr;}
#define SAFE_DELETE_ARRAY(p)	if(p){delete[] p; p = nullptr;}

// 重力
#define GRAVITY			(0.0098f)

// ラジアン変換
#define PI				(3.14159265f)		// 円周率
#define DEG_TO_RAD(deg)	((deg) * PI / 180.0f)	// 度をラジアンに変換
#define RAD_TO_DEG(rad) ((rad) * 180.0f / PI)	// ラジアンを度に変換
