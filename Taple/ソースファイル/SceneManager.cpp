//===== �C���N���[�h�� =====
#include "SceneManager.h"
#include "CameraManager.h"


//===== �O���[�o���ϐ� =====
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

	// �t�F�[�h������������V�[�����X�V����
	if (m_fade.IsFinish())
	{
		// �\�񂪓����Ă�����V�[�����X�V
		if (m_nextScene != SCENE_MAX)
		{
			Uninit();	// �O�̃V�[���̏I������

			// �V�[���̍X�V
			m_scene = m_nextScene;
			// �\���������
			m_nextScene = SCENE_MAX;

			// �V�����V�[���ŏ�����
			Init();

			// �t�F�[�h�C���ŐV�����V�[���J�n
			m_fade.Start(0.5f, false);
		}
	}

	// �X�V����
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
