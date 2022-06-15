
// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "TitleScene.h"
#include "StageSelectScene.h"
#include "GameScene.h"
#include "GimmickManager.h"
#include "Defines.h"
#include "Fade.h"


//===== �萔�E�}�N����` =====
#define SCENE_MANAGER GetSceneMgr()


//===== �N���X��` =====
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
	SceneKind m_scene;		// ���݂̃V�[��
	SceneKind m_nextScene;	// ���̃V�[��

	StageKind m_stage;	// ���݂̃X�e�[�W

	TitleScene m_titleScene;	// �^�C�g���V�[��
	StageSelectScene m_stageSelectScene;	// �X�e�[�W�I���V�[��
	GameScene m_gameScene;		// �Q�[���V�[��

	Fade m_fade;
};


//===== �v���g�^�C�v�錾 =====
SceneMgr* GetSceneMgr();
