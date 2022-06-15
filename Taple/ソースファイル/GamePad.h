//==========================================
//								   GamePad.h
//　ゲームパッド関連
//　制作者:AT12D171 No.11 小畠大季
//
//～～～～～～～～更新履歴～～～～～～～～～
// 2020/11/18 制作開始
//		11/19 コントローラーのステータスからボタンの入力情報を取得するのに使用するマスクの一覧を定数化(GamePadButton)
//			  ボタンの判定(Press,Trigger,Release)を実装
//		11/20 トリガーの判定(Press,Trigger,Release)を実装
//			  スティックの判定(-1.0～1.0で傾きを取得)を実装
//			  GamePadButtonをenum classからclassに変更
//		11/26 インクルード部にDirectXMath.hを追加
//			  スティックの判定のX,Yが別の関数になっていたのを一つにまとめる
//		11/27 判定の関数をすべてインライン化
//～～～～～～～～～～～～～～～～～～～～～

// インクルードガード
#pragma once


//===== インクルード部 =====
#include <Windows.h>
#include <DirectXMath.h>
#include <Xinput.h>

// xinput.libをリンクする
#pragma comment (lib, "xinput.lib")


//===== 定数・マクロ定義 =====
#define GAMEPAD_TRIGGER_THRESHOLD	(100)
#define GAMEPAD_STICK_MAX		(32767)


//===== クラス定義 =====
class GamePadButton	// 入力を取得することのできるボタンの一覧
{
	// インスタンス化を禁止
private:
	GamePadButton();

public:
	static const WORD NONE				= 0x0000;	// 何も押していない
	static const WORD DPAD_UP			= 0x0001;	// 十字キー上
	static const WORD DPAD_DOWN			= 0x0002;	// 十字キー下
	static const WORD DPAD_LEFT			= 0x0004;	// 十字キー左
	static const WORD DPAD_RIGHT		= 0x0008;	// 十字キー右
	static const WORD START				= 0x0010;	// スタートボタン
	static const WORD BACK				= 0x0020;	// バックボタン
	static const WORD LEFT_THUMB		= 0x0040;	// 左スティック押し込み(L3)
	static const WORD RIGHT_THUMB		= 0x0080;	// 右スティック押し込み(R3)
	static const WORD LEFT_SHOULDER		= 0x0100;	// LB(L1)
	static const WORD RIGHT_SHOULDER	= 0x0200;	// RB(R1)
	static const WORD A					= 0x1000;	// A(×)
	static const WORD B					= 0x2000;	// B(〇)
	static const WORD X					= 0x4000;	// X(□)
	static const WORD Y					= 0x8000;	// Y(△)
};


class GamePad	// ゲームパッドの入力をとるクラス
{
// インスタンス化を禁止
private:
	GamePad();

public:
	//===== メンバ関数 =====
	//----- 四大処理 -----

	//--------------------------------------
	//関数名：Init
	//引　数：なし
	//戻り値：HRESULT コントローラーが繋がっているかどうか
	//内　容：初期化処理
	//--------------------------------------
	static HRESULT Init(void);
	//--------------------------------------
	//関数名：Uninit
	//引　数：なし
	//戻り値：なし
	//内　容：終了処理
	//--------------------------------------
	static void Uninit(void);
	//--------------------------------------
	//関数名：Update
	//引　数：なし
	//戻り値：なし
	//内　容：更新処理
	//--------------------------------------
	static void Update(void);


	//----- ボタン -----

	//--------------------------------------
	//関数名：IsButtonPress
	//引　数：const WORD button 判定をとるボタン
	//戻り値：bool 押されているか
	//内　容：ボタンが押されているか
	//--------------------------------------
	static bool IsButtonPress(const WORD button) { return button == GamePadButton::NONE ? m_state.Gamepad.wButtons == 0 : m_state.Gamepad.wButtons & button; }
	//--------------------------------------
	//関数名：IsButtonTrigger
	//引　数：const WORD button 判定をとるボタン
	//戻り値：bool 押されたか
	//内　容：ボタンが押されたか
	//--------------------------------------
	static bool IsButtonTrigger(const WORD button) { return (m_state.Gamepad.wButtons ^ m_oldState.Gamepad.wButtons) & m_state.Gamepad.wButtons & button; }
	//--------------------------------------
	//関数名：IsButtonRelease
	//引　数：const WORD button 判定をとるボタン
	//戻り値：bool 離されたか
	//内　容：ボタンが離されたか
	//--------------------------------------
	static bool IsButtonRelease(const WORD button) { return (m_oldState.Gamepad.wButtons ^ m_state.Gamepad.wButtons) & m_oldState.Gamepad.wButtons & button; }
//	static const bool IsButtonRepeat(WORD);	未実装


	//----- トリガー -----

	//--------------------------------------
	//関数名：GetRightTrigger
	//引　数：なし
	//戻り値：BYTE どれだけ押し込まれているか(0～255)
	//内　容：右のトリガーがどれだけ押されているか
	//--------------------------------------
	static BYTE GetRightTrigger(void) { return m_state.Gamepad.bRightTrigger; }
	//--------------------------------------
	//関数名：IsRightTriggerPress
	//引　数：なし
	//戻り値：bool 押されているか
	//内　容：右トリガーが押されているか
	//--------------------------------------
	static bool IsRightTriggerPress(void) { return m_state.Gamepad.bRightTrigger > GAMEPAD_TRIGGER_THRESHOLD; }
	//--------------------------------------
	//関数名：IsRightTriggerTrigger
	//引　数：なし
	//戻り値：bool 押されたか
	//内　容：右トリガーが押されたか
	//--------------------------------------
	static bool IsRightTriggerTrigger(void) { return (m_state.Gamepad.bRightTrigger > GAMEPAD_TRIGGER_THRESHOLD) && (m_oldState.Gamepad.bRightTrigger <= GAMEPAD_TRIGGER_THRESHOLD); }
	//--------------------------------------
	//関数名：IsRightTriggerRelease
	//引　数：なし
	//戻り値：bool 離されたか
	//内　容：右トリガーが離されたか
	//--------------------------------------
	static bool IsRightTriggerRelease(void) { return (m_state.Gamepad.bRightTrigger <= GAMEPAD_TRIGGER_THRESHOLD) && (m_oldState.Gamepad.bRightTrigger > GAMEPAD_TRIGGER_THRESHOLD); }
//	static bool IsRightTriggerRepeat(void);	未実装

	//--------------------------------------
	//関数名：GetLeftTrigger
	//引　数：なし
	//戻り値：BYTE どれだけ押し込まれているか(0～255)
	//内　容：左のトリガーがどれだけ押されているか
	//--------------------------------------
	static BYTE GetLeftTrigger(void) { return m_state.Gamepad.bLeftTrigger; }
	//--------------------------------------
	//関数名：IsLeftTriggerPress
	//引　数：なし
	//戻り値：bool 押されているか
	//内　容：左トリガーが押されているか
	//--------------------------------------
	static bool IsLeftTriggerPress(void) { return m_state.Gamepad.bLeftTrigger > GAMEPAD_TRIGGER_THRESHOLD; }
	//--------------------------------------
	//関数名：IsLeftTriggerTrigger
	//引　数：なし
	//戻り値：bool 押されたか
	//内　容：左トリガーが押されたか
	//--------------------------------------
	static bool IsLeftTriggerTrigger(void) { return (m_state.Gamepad.bLeftTrigger > GAMEPAD_TRIGGER_THRESHOLD) && (m_oldState.Gamepad.bLeftTrigger <= GAMEPAD_TRIGGER_THRESHOLD); }
	//--------------------------------------
	//関数名：IsLeftTriggerRelease
	//引　数：なし
	//戻り値：bool 離されたか
	//内　容：左トリガーが離されたか
	//--------------------------------------
	static bool IsLeftTriggerRelease(void) { return (m_state.Gamepad.bLeftTrigger <= GAMEPAD_TRIGGER_THRESHOLD) && (m_oldState.Gamepad.bLeftTrigger > GAMEPAD_TRIGGER_THRESHOLD); }
//	static const bool IsLeftTriggerRepeat(void);	未実装


	//----- スティック -----

	//--------------------------------------
	//関数名：GetRightStick
	//引　数：なし
	//戻り値：DirectX::XMFLOAT2 傾き(x軸、y軸 (-1.0～1.0))
	//内　容：右スティックの傾きを取得
	//--------------------------------------
	static DirectX::XMFLOAT2 GetRightStick(void) { return DirectX::XMFLOAT2(static_cast<float>(m_state.Gamepad.sThumbRX) / GAMEPAD_STICK_MAX, static_cast<float>(m_state.Gamepad.sThumbRY) / GAMEPAD_STICK_MAX); }
	//--------------------------------------
	//関数名：GetLeftStick
	//引　数：なし
	//戻り値：DirectX::XMFLOAT2 傾き(x軸、y軸 (-1.0～1.0))
	//内　容：左スティックの傾きを取得
	//--------------------------------------
	static DirectX::XMFLOAT2 GetLeftStick(void) { return DirectX::XMFLOAT2(static_cast<float>(m_state.Gamepad.sThumbLX) / GAMEPAD_STICK_MAX, static_cast<float>(m_state.Gamepad.sThumbLY) / GAMEPAD_STICK_MAX); }

private:
	//===== メンバ変数 =====
	static XINPUT_STATE m_state;	// ゲームパッドの情報
	static XINPUT_STATE m_oldState;	// 前回のゲームパッドの情報
};
