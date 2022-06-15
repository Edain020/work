
//===== インクルード部 =====
#include "GameScene.h"
#include "Defines.h"
#include "Collision.h"
#include "CameraManager.h"
#include "Main.h"
#include "GamePad.h"
#include "Input.h"
#include "SceneManager.h"
#include <random>



void GameScene::Init()
{
	// カメラ
	CameraMgr::Init();

	DrawTutorial();

	//ゴール
	m_pGoal = new Box();
	m_pGoal->Init();

	//----- ステージ -----
	switch (m_stage)
	{
	case STAGE_KIDSROOM:
		m_kidsRoom.Init();
		m_pGoal->SetPos(DirectX::XMFLOAT3(BOX_SIZE_X / 2.0f + 225, -BOX_SIZE_Y / 2.0f, 0));
		break;
//	case STAGE_STUDY:
//		m_study.Init();
//		m_pGoal->SetPos(DirectX::XMFLOAT3(BOX_SIZE_X / 2.0f + 94, -BOX_SIZE_Y / 2.0f + 22, 0));
//		break;
	case STAGE_KITCHEN:
		m_kitchen.Init();
		m_pGoal->SetPos(DirectX::XMFLOAT3(BOX_SIZE_X / 2.0f - 11, -BOX_SIZE_Y / 2.0f + 33, 0));
		break;
	default:
		break;
	}

	m_mode = MODE_GAME;

	// 背景
	m_pBackWall = new BackWall();
	m_pBackWall->Init(m_stage);

	// プレイヤー
	m_pPlayer = new Player();
	m_pPlayer->Init();

	// タイマー
	m_pTimer = new Timer();
	m_pTimer->Init();

	
	//----- クリア&ゲームオーバー画面
	m_pBlack = new Image();
	m_pBlack->LoadTexture(ASSET("black.png"));
	m_pBlack->SetPos(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pBlack->SetSize(DirectX::XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	m_pBlack->SetAlpha(0.3f);

	m_pClear = new Image();
	m_pClear->LoadTexture(ASSET("GOOD.png"));
	m_pClear->SetPos(DirectX::XMFLOAT3(0.0f, 52.5f, 0.0f));
	m_pClear->SetSize(DirectX::XMFLOAT3(473.0f, 210.0f, 0.0f));

	m_pGameOver = new Image();
	m_pGameOver->LoadTexture(ASSET("GAMEOVER.png"));
	m_pGameOver->SetPos(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
	m_pGameOver->SetSize(DirectX::XMFLOAT3(790.0f, 136.0f, 0.0f));

	std::random_device rand;
	for (int i = 0; i < BALLOON_NUM; ++i)
	{
		m_pBalloons[i] = new Balloon();
		m_pBalloons[i]->SetPos(DirectX::XMFLOAT3(
				rand() % static_cast<int>(SCREEN_WIDTH / 4 * 3) - SCREEN_WIDTH / 4.0f,
				-(SCREEN_HEIGHT / 2.0f + 100.0f + (rand() % 500)),
				0.0f));
		m_pBalloons[i]->Init();
	}
	m_fCnt = 0.0f;

	//決定音
	m_pSE = new Sound();
	m_pSE->Load(ASSET("Sound/SE/kettei.mp3"), false);
	m_pSE->SetVolume(0.2f);

	m_pClearSE = new Sound();
	m_pClearSE->Load(ASSET("Sound/SE/Clear.mp3"), false);
	m_pClearSE->SetVolume(0.5f);

	m_pGameOverSE = new Sound();
	m_pGameOverSE->Load(ASSET("Sound/SE/Gameover.mp3"), false);
	m_pGameOverSE->SetVolume(0.5f);
}


void GameScene::Uninit()
{
	//----- ステージ -----
	switch (m_stage)
	{
	case STAGE_KIDSROOM:
		m_kidsRoom.Uninit();
		break;
//	case STAGE_STUDY:
//		m_study.Uninit();
//		break;
	case STAGE_KITCHEN:
		m_kitchen.Uninit();
		break;
	default:
		break;
	}

	// 背景
	SAFE_DELETE(m_pBackWall);

	// プレイヤー
	SAFE_DELETE(m_pPlayer);

	// ゴール
	SAFE_DELETE(m_pGoal);

	// タイマー
	SAFE_DELETE(m_pTimer);

	// カメラ
	CameraMgr::Uninit();

	//----- クリア&ゲームオーバー画面 -----
	SAFE_DELETE(m_pBlack);
	SAFE_DELETE(m_pClear);
	SAFE_DELETE(m_pGameOver);
	SAFE_DELETE(m_pSE);
	SAFE_DELETE(m_pClearSE);
	SAFE_DELETE(m_pGameOverSE);
}


void GameScene::Update()
{
	switch (m_mode)
	{
	case MODE_GAME:
		switch (m_stage)
		{
		case STAGE_KIDSROOM:
			m_kidsRoom.Update();
			break;
//		case STAGE_STUDY:
//			m_study.Update();
//			break;
		case STAGE_KITCHEN:
			m_kitchen.Update();
			break;
		case STAGE_MAX:
			break;
		default:
			break;
		}

		// 背景
		m_pBackWall->Update();

		// プレイヤー
		m_pPlayer->Update();

		m_pGoal->Update();

		if (CheckCollision(m_pPlayer, m_pGoal))
		{
			m_mode = MODE_CLEAR;
			m_pClearSE->Play();
		}

		// 全ての移動(移動処理)が住んでからすべてのオブジェクトの当たり判定を行う
		GIMMICKS->SetCollision(m_pPlayer);
		UpdateCollision();

		// カメラ
		CameraMgr::Update();

		//----- UIの更新 -----

		// タイマー
		if (m_pTimer->Update())
		{
			m_mode = MODE_GAMEOVER;
			m_pGameOverSE->Play();
		}
		break;
	case MODE_CLEAR:
		m_fCnt += 2.0f;
		if (m_fCnt >= 360.0f)
		{
			m_fCnt -= 360.0f;
		}
		m_pClear->SetPos(DirectX::XMFLOAT3(0.0f, 52.5f + sinf(DEG_TO_RAD(m_fCnt)) * 25.0f, 0.0f));

		for (int i = 0; i < BALLOON_NUM; ++i)
		{
			m_pBalloons[i]->Update();
		}


		if (GamePad::IsButtonTrigger(GamePadButton::A) || IsKeyTrigger('J'))
		{
			SCENE_MANAGER->SetNextScene(SCENE_TITLE);
			m_pSE->Play();
		}
		break;
	case MODE_GAMEOVER:
		m_fCnt += 2.0f;
		if (m_fCnt >= 360.0f)
		{
			m_fCnt -= 360.0f;
		}
		m_pGameOver->SetPos(DirectX::XMFLOAT3(0.0f, sinf(DEG_TO_RAD(m_fCnt)) * 25.0f, 0.0f));


		if (GamePad::IsButtonTrigger(GamePadButton::A) || IsKeyTrigger('J'))
		{
			SCENE_MANAGER->SetNextScene(SCENE_TITLE);
			m_pSE->Play();
		}
		break;
	default:
		break;
	}

	
}


void GameScene::Draw()
{
	//----- 3D描画 -----
	CameraMgr::DrawSetting(true);

	m_pBackWall->Draw();
	//----- ステージ -----
	switch (m_stage)
	{
	case STAGE_KIDSROOM:
		m_kidsRoom.Draw();
		break;
//	case STAGE_STUDY:
//		m_study.Draw();
//		break;
	case STAGE_KITCHEN:
		m_kitchen.Draw();
		break;
	default:
		break;
	}
	m_pGoal->Draw();

	m_pPlayer->Draw();

	//----- 2D描画 -----
	CameraMgr::DrawSetting(false);
	m_pTimer->Draw();


	switch (m_mode)
	{
	case MODE_GAME:
		break;
	case MODE_CLEAR:
		m_pBlack->Draw();
		m_pClear->Draw();
		for (int i = 0; i < BALLOON_NUM; ++i)
		{
			m_pBalloons[i]->Draw();
		}
		break;
	case MODE_GAMEOVER:
		m_pBlack->Draw();
		m_pGameOver->Draw();
		break;
	default:
		break;
	}
}


void GameScene::SetStage(StageKind stage)
{
	m_stage = stage;
}
