
// インクルードガード
#pragma once


//===== インクルード部 =====
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "GimmickManager.h"
#include "Defines.h"
#include "Fade.h"


//===== 定数・マクロ定義 =====
#define SCENE_MANAGER GetSceneMgr()


//===== クラス定義 =====
class SceneMgr
{
public:
	SceneMgr() {}
	~SceneMgr() {}


	void SetStartScene();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetNextScene(SceneKind scene);
	void SetStage(StageKind stage);

	SceneKind GetScene() { return m_scene; }

private:
	SceneKind m_scene;		// 現在のシーン
	SceneKind m_nextScene;	// 次のシーン

	StageKind m_stage;	// 現在のステージ

	TitleScene m_titleScene;	// タイトルシーン
	StageSelectScene m_stageSelectScene;	// ステージ選択シーン
	GameScene m_gameScene;		// ゲームシーン

	Fade m_fade;
};


//===== プロトタイプ宣言 =====
SceneMgr* GetSceneMgr();
