//===== インクルード部 =====
#include "SceneManager.h"
#include "CameraManager.h"


//===== グローバル変数 =====
SceneMgr g_sceneMgr;


void SceneMgr::SetStartScene()
{
	m_scene = SCENE_TITLE;
	m_nextScene = SCENE_MAX;
	m_stage = STAGE_MAX;
	m_fade.Init();
	m_fade.Start(1.0f, false);
}


void SceneMgr::Init()
{
	switch (m_scene)
	{
	case SCENE_TITLE:
		m_titleScene.Init();
		break;
	case SCENE_STAGESELECT:
		m_stageSelectScene.Init();
		break;
	case SCENE_GAME:
		m_gameScene.SetStage(m_stage);
		m_gameScene.Init();
		break;
	default:
		break;
	}
}


void SceneMgr::Uninit()
{
	switch (m_scene)
	{
	case SCENE_TITLE:
		m_titleScene.Uninit();
		break;
	case SCENE_STAGESELECT:
		m_stage = m_stageSelectScene.GetStage();
		m_stageSelectScene.Uninit();
		break;
	case SCENE_GAME:
		m_gameScene.Uninit();
		break;
	default:
		break;
	}
}


void SceneMgr::Update()
{
	m_fade.Update();

	// フェードが完了したらシーンを更新する
	if (m_fade.IsFinish())
	{
		// 予約が入っていたらシーンを更新
		if (m_nextScene != SCENE_MAX)
		{
			Uninit();	// 前のシーンの終了処理

			// シーンの更新
			m_scene = m_nextScene;
			// 予約を初期化
			m_nextScene = SCENE_MAX;

			// 新しいシーンで初期化
			Init();

			// フェードインで新しいシーン開始
			m_fade.Start(0.5f, false);
		}
	}

	// 更新処理
	switch (m_scene)
	{
	case SCENE_TITLE:
		m_titleScene.Update();
		break;
	case SCENE_STAGESELECT:
		m_stageSelectScene.Update();
		break;
	case SCENE_GAME:
		m_gameScene.Update();
		break;
	default:
		break;
	}
}


void SceneMgr::Draw()
{
	switch (m_scene)
	{
	case SCENE_TITLE:
		m_titleScene.Draw();
		break;
	case SCENE_STAGESELECT:
		m_stageSelectScene.Draw();
		break;
	case SCENE_GAME:
		m_gameScene.Draw();
		break;
	default:
		break;
	}

	CameraMgr::DrawSetting(false);
	m_fade.Draw();
}


void SceneMgr::SetNextScene(SceneKind scene)
{
	if (m_nextScene != SCENE_MAX)
	{
		return;
	}

	m_nextScene = scene;
	m_fade.Start(0.5f, true);
}


void SceneMgr::SetStage(StageKind stage)
{
	m_stage = stage;
}


SceneMgr* GetSceneMgr()
{
	return &g_sceneMgr;
}
