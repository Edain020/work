
//===== �C���N���[�h�� =====
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
	
	// �V�F�[�_
	hr = SHADER->Init();
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to Shader."); }

	// �L�[�{�[�h
	hr = InitKeyboard();
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to Keyboard."); }
	
	// �R���g���[���[
	hr = GamePad::Init();
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to GamePad."); }

	// �T�E���h
	hr = InitSound();
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to Sound."); }

	// �����蔻��
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
	// �L�[�{�[�h
	UpdateKeyboard();

	// �R���g���[���[
	GamePad::Update();

	// �V�[���̍X�V
	SCENE_MANAGER->Update();
}


void Draw()
{
	BeginDrawDX();
	//----- �������� -----
	
	// �V�F�[�_�[�̃o�C���h
//	SHADER->Bind(VS_WORLD, PS_PHONG);
//	SHADER->Bind(VS_WORLD, PS_LAMBERT);
	SHADER->Bind(VS_WORLD, PS_UNLIT);

	// ���̓������Ă镔���̐F�ɔ��f�����
	SHADER->SetDiffuse(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));	
	// ���̓������Ă��Ȃ�(�e)�̕����̐F�ɔ��f�����
	SHADER->SetLightAmbient(DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));

	// �f�t�H���g�e�N�X�`���̐ݒ�
	SHADER->SetTexture(NULL);

	// �V�[���̍X�V
	SCENE_MANAGER->Draw();

	//----- �����܂� -----
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