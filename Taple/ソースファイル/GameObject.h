//==========================================
//								GameObject.h
//　ゲームオブジェクト関連
//　制作者:AT12D171 No.11 小畠大季
//
//～～～～～～～～更新履歴～～～～～～～～～
// 2020/10/28 制作開始
//		12/12 衝突時の処理を行う関数OnCollisionを追加
//～～～～～～～～～～～～～～～～～～～～～

// インクルードガード
#pragma once


//===== インクルード部 =====
#include <DirectXMath.h>
#include "Cube.h"
#include "Shader.h"


// 当たり判定を実施するときのオブジェクトの種類
enum ObjectCollisionType
{
	COLLISION_STATIC,	// 静止している物体
	COLLISION_DYNAMIC,	// 動いている物体
	COLLISION_OVERLAP	// 貫通する物体
};


//===== クラス定義 =====
class GameObject
{
public:
	//===== メンバ関数 =====
	GameObject();
	virtual ~GameObject();

	//----- 四大処理 -----
	virtual bool Init();
	virtual void Uninit();
	virtual void Update() {}
	virtual void Draw();

	//----- 当たり判定 -----
	virtual void OnCollision(GameObject *other) {}

	//----- ゲッター -----
	DirectX::XMFLOAT3 GetPos() { return m_pos; }
	DirectX::XMFLOAT3 GetSize() { return m_size; }
	DirectX::XMFLOAT3 GetMove() { return m_move; }
	ObjectCollisionType GetCollisionType() { return m_collisionType; }

	//----- セッター -----
	void SetPos(const DirectX::XMFLOAT3 pos)	{ m_pos = pos; }
	void SetSize(const DirectX::XMFLOAT3 size)	{ m_size = size; }
	void SetMove(DirectX::XMFLOAT3 move)		{ m_move = move; }


	virtual bool isPlayer(void) { return false; }
	virtual bool isClimb(void) { return false; }

private:

protected:
	//===== メンバ変数 =====
	DirectX::XMFLOAT3 m_pos;	// 座標
	DirectX::XMFLOAT3 m_size;	// 大きさ
	DirectX::XMFLOAT3 m_move;	// 移動量
	DirectX::XMFLOAT3 m_rot;	// 回転量

	ObjectCollisionType m_collisionType;// 当たり判定の種類

	//===== メンバオブジェクト =====
	Cube *m_pCube;	// 簡易モデル
};
