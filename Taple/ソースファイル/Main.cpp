
//===== インクルード部 =====
#include "Main.h"
#include "FBX/FBXLoader.h"
#include "DirectX.h"
#include "Shader.h"
#include "GamePad.h"
#include "Sound.h"
#include "Collision.h"
#include "CameraManager.h"
#include "Input.h"
#include "SceneManager.h"
#include "Image.h"


Image		*g_pTutorial;


HRESULT ErrorBox(HRESULT hr, const char* message)
{
	MessageBox(NULL, message, "Error", MB_OK);
	return hr;
}


HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;

	// fbxsdk
	ggfbx::Initialize();
	
	// DirectX
	hr = InitDX(hWnd, width, height, false);
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to DirectX."); }
	
	// シェーダ
	hr = SHADER->Init();
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to Shader."); }

	// キーボード
	hr = InitKeyboard();
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to Keyboard."); }
	
	// コントローラー
	hr = GamePad::Init();
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to GamePad."); }

	// サウンド
	hr = InitSound();
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to Sound."); }

	// 当たり判定
	hr = InitCollision();
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to Collision."); }

	SCENE_MANAGER->SetStartScene();
	SCENE_MANAGER->Init();


	g_pTutorial = new Image();
	g_pTutorial->LoadTexture(ASSET("Tutorial.png"));
	g_pTutorial->SetPos(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
	g_pTutorial->SetSize(DirectX::XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	return hr;
}


void Uninit()
{
	SCENE_MANAGER->Uninit();
	GIMMICKS->Uninit();
	SAFE_DELETE(g_pTutorial);
	UninitCollision();
	UninitSound();
	GamePad::Uninit();
	SHADER->Uninit();
	UninitKeyboard();
	UninitDX();
	ggfbx::Terminate();
}


void Update()
{
	// キーボード
	UpdateKeyboard();

	// コントローラー
	GamePad::Update();

	// シーンの更新
	SCENE_MANAGER->Update();
}


void Draw()
{
	BeginDrawDX();
	//----- ここから -----
	
	// シェーダーのバインド
//	SHADER->Bind(VS_WORLD, PS_PHONG);
//	SHADER->Bind(VS_WORLD, PS_LAMBERT);
	SHADER->Bind(VS_WORLD, PS_UNLIT);

	// 光の当たってる部分の色に反映される
	SHADER->SetDiffuse(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));	
	// 光の当たっていない(影)の部分の色に反映される
	SHADER->SetLightAmbient(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	// デフォルトテクスチャの設定
	SHADER->SetTexture(NULL);

	// シーンの更新
	SCENE_MANAGER->Draw();

	//----- ここまで -----
	EndDrawDX();
}


void DrawTutorial()
{
	BeginDrawDX();

	CameraMgr::DrawSetting(false);
	g_pTutorial->Draw();

	EndDrawDX();
}


// EOF