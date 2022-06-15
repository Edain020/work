//===== インクルード部 =====
#include "StageSelectScene.h"
#include "Input.h"
#include "CameraManager.h"
#include "Defines.h"
#include "Shader.h"
#include "GamePad.h"
#include "SceneManager.h"



void StageSelectScene::Init(void)
{
	m_stage = STAGE_KIDSROOM;
	m_angle = 0.0f;
	m_currentAngle = 0.0f;
	m_cnt = 0;

	LoadTextureFromFile(ASSET("black.png"), &m_pTex);

	m_pStageIcon[0] = new Model();
	m_pStageIcon[0]->LoadModel(ASSET("Model/StageSelect/KidsRoom.fbx"));
	
//	m_pStageIcon[1] = new Model();
//	m_pStageIcon[1]->LoadModel(ASSET("Model/StageSelect/Study.fbx"));
//
//	m_pStageIcon[2] = new Model();
//	m_pStageIcon[2]->LoadModel(ASSET("Model/StageSelect/Kitchen.fbx"));
//
//	m_pStageIcon[3] = new Model();
//	m_pStageIcon[3]->LoadModel(ASSET("Model/StageSelect/Title.fbx"));

	m_pStageIcon[1] = new Model();
	m_pStageIcon[1]->LoadModel(ASSET("Model/StageSelect/Kitchen.fbx"));

	m_pStageIcon[2] = new Model();
	m_pStageIcon[2]->LoadModel(ASSET("Model/StageSelect/Title.fbx"));


	m_pStageImage[0] = new Image();
	m_pStageImage[0]->LoadTexture(ASSET("BG/StageSelect/KidsRoomImage.jpg"));
	m_pStageImage[0]->SetPos(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pStageImage[0]->SetSize(DirectX::XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

//	m_pStageImage[1] = new Image();
//	m_pStageImage[1]->LoadTexture(ASSET("BG/StageSelect/StudyImage.jpg"));
//	m_pStageImage[1]->SetPos(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
//	m_pStageImage[1]->SetSize(DirectX::XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
//
//	m_pStageImage[2] = new Image();
//	m_pStageImage[2]->LoadTexture(ASSET("BG/StageSelect/KitchenImage.jpg"));
//	m_pStageImage[2]->SetPos(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
//	m_pStageImage[2]->SetSize(DirectX::XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
//
//	m_pStageImage[3] = new Image();
//	m_pStageImage[3]->LoadTexture(ASSET("BG/Title.png"));
//	m_pStageImage[3]->SetPos(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
//	m_pStageImage[3]->SetSize(DirectX::XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	m_pStageImage[1] = new Image();
	m_pStageImage[1]->LoadTexture(ASSET("BG/StageSelect/KitchenImage.jpg"));
	m_pStageImage[1]->SetPos(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pStageImage[1]->SetSize(DirectX::XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	m_pStageImage[2] = new Image();
	m_pStageImage[2]->LoadTexture(ASSET("BG/Title.png"));
	m_pStageImage[2]->SetPos(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pStageImage[2]->SetSize(DirectX::XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));


	m_pStageName[0] = new Image();
	m_pStageName[0]->LoadTexture(ASSET("UI/StageSelect/KidsRoomName.png"));
	m_pStageName[0]->SetSize(DirectX::XMFLOAT3(426.0f, 148.0f, 0.0f));
	m_pStageName[0]->SetPos(DirectX::XMFLOAT3(0.0f, SCREEN_HEIGHT / 2.0f - 148.0f / 2, 0.0f));

//	m_pStageName[1] = new Image();
//	m_pStageName[1]->LoadTexture(ASSET("UI/StageSelect/StudyName.png"));
//	m_pStageName[1]->SetSize(DirectX::XMFLOAT3(426.0f, 148.0f, 0.0f));
//	m_pStageName[1]->SetPos(DirectX::XMFLOAT3(0.0f, SCREEN_HEIGHT / 2.0f - 148.0f / 2, 0.0f));
//
//	m_pStageName[2] = new Image();
//	m_pStageName[2]->LoadTexture(ASSET("UI/StageSelect/KitchenName.png"));
//	m_pStageName[2]->SetSize(DirectX::XMFLOAT3(426.0f, 148.0f, 0.0f));
//	m_pStageName[2]->SetPos(DirectX::XMFLOAT3(0.0f, SCREEN_HEIGHT / 2.0f - 148.0f / 2, 0.0f));
//
//	m_pStageName[3] = new Image();
//	m_pStageName[3]->LoadTexture(ASSET("UI/StageSelect/TitleName.png"));
//	m_pStageName[3]->SetSize(DirectX::XMFLOAT3(426.0f, 148.0f, 0.0f));
//	m_pStageName[3]->SetPos(DirectX::XMFLOAT3(0.0f, SCREEN_HEIGHT / 2.0f - 148.0f / 2, 0.0f));

	m_pStageName[1] = new Image();
	m_pStageName[1]->LoadTexture(ASSET("UI/StageSelect/KitchenName.png"));
	m_pStageName[1]->SetSize(DirectX::XMFLOAT3(426.0f, 148.0f, 0.0f));
	m_pStageName[1]->SetPos(DirectX::XMFLOAT3(0.0f, SCREEN_HEIGHT / 2.0f - 148.0f / 2, 0.0f));

	m_pStageName[2] = new Image();
	m_pStageName[2]->LoadTexture(ASSET("UI/StageSelect/TitleName.png"));
	m_pStageName[2]->SetSize(DirectX::XMFLOAT3(426.0f, 148.0f, 0.0f));
	m_pStageName[2]->SetPos(DirectX::XMFLOAT3(0.0f, SCREEN_HEIGHT / 2.0f - 148.0f / 2, 0.0f));


	m_pNext = new Image();
	m_pNext->LoadTexture(ASSET("UI/next.png"));
	m_pNext->SetPos(DirectX::XMFLOAT3(SCREEN_WIDTH / 2.0f - 466.0f / 4 - 50.0f, -(SCREEN_HEIGHT / 2.0f - 125.0f / 4 - 50.0f), 0.0f));
	m_pNext->SetSize(DirectX::XMFLOAT3(466.0f / 2, 125.0f / 2, 0.0f));

	m_pSceneIcon = new Image();
	m_pSceneIcon->LoadTexture(ASSET("UI/StageSelect/Icon.png"));
	m_pSceneIcon->SetSize(DirectX::XMFLOAT3(231.0f / 2, 131.0f / 2, 0.0f));
	m_pSceneIcon->SetPos(DirectX::XMFLOAT3(-SCREEN_WIDTH / 2.0f + 231.0f / 2, SCREEN_HEIGHT / 2.0f - 131.0f / 2, 0.0f));

	// BGM
	m_pBGM = new Sound();
	m_pBGM->Load(ASSET("Sound/BGM/StageSelect.mp3"), true);
	m_pBGM->Play();
	m_pBGM->SetVolume(0.2f);

	//決定音
	m_pNextSE = new Sound();
	m_pNextSE->Load(ASSET("Sound/SE/kettei.mp3"), false);
	m_pNextSE->SetVolume(0.2f);

	//選択切り替え音
	m_pSelectSE = new Sound();
	m_pSelectSE->Load(ASSET("Sound/SE/select.mp3"), false);
	m_pSelectSE->SetVolume(0.2f);

	CameraMgr::Init();
}


void StageSelectScene::Uninit(void)
{
	SAFE_RELEASE(m_pTex);

	for (int i = 0; i < STAGE_MAX; ++i)
	{
		SAFE_DELETE(m_pStageIcon[i]);
	}

	for (int i = 0; i < STAGE_MAX; ++i)
	{
		SAFE_DELETE(m_pStageImage[i]);
	}

	for (int i = 0; i < STAGE_MAX; ++i)
	{
		SAFE_DELETE(m_pStageName[i]);
	}

	SAFE_DELETE(m_pNext);
	SAFE_DELETE(m_pSceneIcon);

	m_pBGM->Stop();
	SAFE_DELETE(m_pBGM);
	SAFE_DELETE(m_pNextSE);
	SAFE_DELETE(m_pSelectSE);
	
	CameraMgr::Uninit();
}


void StageSelectScene::Update(void)
{
	if (GamePad::IsButtonTrigger(GamePadButton::DPAD_LEFT) || IsKeyTrigger('A'))
	{
		m_stage--;
		m_angle -= 360.0f / STAGE_MAX;
		if (m_stage < 0)
		{
			m_stage = STAGE_MAX - 1;
		}
		m_pSelectSE->Play();
	}
	if (GamePad::IsButtonTrigger(GamePadButton::DPAD_RIGHT) || IsKeyTrigger('D'))
	{
		m_stage++;
		m_angle += 360.0f / STAGE_MAX;
		if (m_stage >= STAGE_MAX)
		{
			m_stage = 0;
		}
		m_pSelectSE->Play();
	}

	if (GamePad::IsButtonTrigger(GamePadButton::A) || IsKeyTrigger('J'))
	{
		if (m_stage == RETURN_TITLE)
		{
			SCENE_MANAGER->SetNextScene(SCENE_TITLE);
		}
		else
		{
			SCENE_MANAGER->SetNextScene(SCENE_GAME);
			SCENE_MANAGER->SetStage(static_cast<StageKind>(m_stage));
		}
		m_pNextSE->Play();
	}


	if (m_angle != m_currentAngle)
	{
		float move;
		move = m_angle - m_currentAngle;
		move *= 0.1f;
		m_currentAngle += move;
	}
	
	if (m_currentAngle < 0 && m_angle < 0)
	{
		m_angle += 360.0f;
		m_currentAngle += 360.0f;
	}
	else if (m_currentAngle >= 360.0f && m_currentAngle >= 360)
	{
		m_angle -= 360.0f;
		m_currentAngle -= 360.0f;
	}

	m_cnt += 2;
	if (m_cnt > 360)
	{
		m_cnt -= 360;
	}
}


void StageSelectScene::Draw(void)
{
	CameraMgr::DrawSetting(false);

	m_pStageImage[m_stage]->Draw();
	m_pStageName[m_stage]->Draw();

	CameraMgr::DrawSetting(true);
	for (int i = 0; i < STAGE_MAX; ++i)
	{
		SHADER->SetWorld(
			DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f)
//			* DirectX::XMMatrixRotationY(DEG_TO_RAD(m_currentAngle + i * (360.0f / STAGE_MAX) + 180.0f))
			* DirectX::XMMatrixRotationY(DEG_TO_RAD(m_currentAngle - i * (360.0f / STAGE_MAX) + 180.0f))
			* DirectX::XMMatrixTranslation(
				sinf(DEG_TO_RAD(m_currentAngle - (i * 360.0f / STAGE_MAX))) * 3.0f,
				-0.3f + sinf(DEG_TO_RAD(m_cnt + i * (360.0f / STAGE_MAX))) * 0.05f,
				cosf(DEG_TO_RAD(m_currentAngle - (i * 360.0f / STAGE_MAX))) * 3.0f));
	m_pStageIcon[i]->Draw();
	}

	CameraMgr::DrawSetting(false);
	m_pNext->Draw();
	m_pSceneIcon->Draw();
}


StageKind StageSelectScene::GetStage(void)
{
	return static_cast<StageKind>(m_stage);
}
