//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "TitleScene.h"
#include "GamePad.h"
#include "CameraManager.h"
#include "Defines.h"
#include "SceneManager.h"

#include "Input.h"



void TitleScene::Init(void)
{
	m_pTitleObj = new TitleObj();
	m_pTitleObj->Init();


	m_pTitleBack = new Image();
	m_pTitleBack->LoadTexture(ASSET("BG/Title.png"));
	m_pTitleBack->SetPos(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pTitleBack->SetSize(DirectX::XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	m_pTitleLogo = new Image();
	m_pTitleLogo->LoadTexture(ASSET("TitleRogo.png"));
	m_pTitleLogo->SetPos(DirectX::XMFLOAT3(0.0f, SCREEN_HEIGHT / 4.0f, 0.0f));
	m_pTitleLogo->SetSize(DirectX::XMFLOAT3(350.0f * 2, 248.0f * 2, 0.0f));

	m_pNext = new Image();
	m_pNext->LoadTexture(ASSET("UI/next.png"));
	m_pNext->SetPos(DirectX::XMFLOAT3(SCREEN_WIDTH / 2.0f - 466.0f / 4 - 50.0f, -(SCREEN_HEIGHT / 2.0f - 125.0f / 4 - 50.0f), 0.0f));
	m_pNext->SetSize(DirectX::XMFLOAT3(466.0f / 2, 125.0f / 2, 0.0f));

	m_pSceneIcon = new Image();
	m_pSceneIcon->LoadTexture(ASSET("UI/TitleIcon.png"));
	m_pSceneIcon->SetSize(DirectX::XMFLOAT3(231.0f / 2, 131.0f / 2, 0.0f));
	m_pSceneIcon->SetPos(DirectX::XMFLOAT3(-SCREEN_WIDTH / 2.0f + 231.0f / 2, SCREEN_HEIGHT / 2.0f - 131.0f / 2, 0.0f));

	CameraMgr::Init();

	// BGM
	m_pBGM = new Sound();
	m_pBGM->Load(ASSET("Sound/BGM/Title.mp3"), true);
	m_pBGM->Play();
	m_pBGM->SetVolume(0.2f);

	//Œˆ’è‰¹
	m_pSE = new Sound();
	m_pSE->Load(ASSET("Sound/SE/kettei.mp3"), false);
	m_pSE->SetVolume(0.2f);
}


void TitleScene::Uninit(void)
{
	CameraMgr::Uninit();
	SAFE_DELETE(m_pTitleObj);
	SAFE_DELETE(m_pTitleBack);
	SAFE_DELETE(m_pTitleLogo);
	SAFE_DELETE(m_pNext);
	SAFE_DELETE(m_pSceneIcon);
	m_pBGM->Stop();
	SAFE_DELETE(m_pBGM);
	SAFE_DELETE(m_pSE);
}


void TitleScene::Update()
{
	m_pTitleObj->Update();

	if (GamePad::IsButtonTrigger(GamePadButton::A) || IsKeyTrigger('J'))
	{
		SCENE_MANAGER->SetNextScene(SCENE_STAGESELECT);
		m_pSE->Play();
	}
}


void TitleScene::Draw(void)
{
	//----- 2D•`‰æ -----
	CameraMgr::DrawSetting(false);
	m_pTitleBack->Draw();

	//----- 3D•`‰æ -----
	CameraMgr::DrawSetting(true);
	m_pTitleObj->Draw();

	//----- 2D•`‰æ -----
	CameraMgr::DrawSetting(false);
	m_pTitleLogo->Draw();
	m_pNext->Draw();
	m_pSceneIcon->Draw();
}
