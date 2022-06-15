//==========================================
//									 Model.h
//	モデル関連
//　制作者:AT12D171 No.11 小畠大季
//
//～～～～～～～～更新履歴～～～～～～～～～
// 2020/10/16 制作開始
//～～～～～～～～～～～～～～～～～～～～～

// インクルードガード
#pragma once


//===== インクルード部 =====
#include "DrawBuffer.h"
#include "FBX/FBXPlayer.h"


//===== クラス定義 =====
class Model	// 3Dモデル用クラス
{
public:
	Model();
	~Model();

	bool LoadModel(const char* pFilePath);
	void Draw();

private:
	// ゲームのキャラクターは複数のパーツで成り立っている
	// そのパーツ一つ一つをメッシュと呼ぶ
	// 基本的に一つのメッシュで一つの頂点バッファを持つ
	// モデルごとにメッシュの数が違うため、頂点バッファを動的に確保する
	DrawBuffer *m_pBuffer;

	FBXPlayer m_fbx;	// FBXファイル操作クラス
};
