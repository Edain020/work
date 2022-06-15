
// インクルードガード
#pragma once


//===== インクルード部 =====
#include <Windows.h>


//====== プロトタイプ宣言 =====

HRESULT Init(HWND hWnd, UINT width, UINT height);
void Uninit();
void Update();
void Draw();

void DrawTutorial();
