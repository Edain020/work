//==========================================
//								 GamePad.cpp
//　ゲームパッド関連
//　制作者:AT12D171 No.11 小畠大季
//
//～～～～～～～～更新履歴～～～～～～～～～
// 2020/11/18 制作開始
//		11/19 ボタンの判定(Press,Trigger,Release)を実装
//		11/20 トリガーのしきい値を定数化(GAMEPAD_TRIGGER_THRESHOLD)
//			  トリガーの判定(Press,Trigger,Release)を実装
//			  スティックの傾きの最大値を定数化(GAMEPAD_STICK_TILT_MAX)
//			  スティックの判定(-1.0～1.0で傾きを取得)を実装
//		11/26 インクルード部にDirectXMath.hを追加
//			  スティックの判定のX,Yが別の関数になっていたのを一つにまとめる
//		11/27 判定の関数をすべてインライン化
//～～～～～～～～～～～～～～～～～～～～～

// 警告抑止
#pragma warning(disable : 4995)


//====== インクルード部 =====
#include "GamePad.h"

// 静的メンバ変数の定義
XINPUT_STATE GamePad::m_state = {};
XINPUT_STATE GamePad::m_oldState = {};



//--------------------------------------
//関数名：Init
//引　数：なし
//戻り値：HRESULT コントローラーが繋がっているかどうか
//内　容：初期化処理
//--------------------------------------
HRESULT GamePad::Init(void)
{
	//===== 変数宣言 =====
	DWORD dwResult;	// 実行結果

	// コントローラーが繋がっているかどうか確認
	dwResult = XInputGetState(0, &m_state);
	// XInputを有効化(呼び出す必要なし)
	XInputEnable(true);
	
	if (dwResult == ERROR_SUCCESS)
	{
		return S_OK;
	}
	else
	{
		return S_FALSE;
	}
}


//--------------------------------------
//関数名：Uninit
//引　数：なし
//戻り値：なし
//内　容：終了処理
//--------------------------------------
void GamePad::Uninit(void)
{
	// XInput無効化(バイブレーションなどを中断)
	XInputEnable(false);
}


//--------------------------------------
//関数名：Update
//引　数：なし
//戻り値：なし
//内　容：更新処理
//--------------------------------------
void GamePad::Update(void)
{
	// 前回の入力情報を退避
	m_oldState = m_state;
	// コントローラーの状態を取得
	XInputGetState(0, &m_state);

	// スティックの傾きのマイナス方向とプラス方向の差を補正する
	if (m_state.Gamepad.sThumbRX < -GAMEPAD_STICK_MAX)
	{
		m_state.Gamepad.sThumbRX = -GAMEPAD_STICK_MAX;
	}
	if (m_state.Gamepad.sThumbLX < -GAMEPAD_STICK_MAX)
	{
		m_state.Gamepad.sThumbLX = -GAMEPAD_STICK_MAX;
	}
	// スティックの傾きがデッドゾーン未満なら0にする(スティックに遊びを持たせる)
	if ((m_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(m_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		m_state.Gamepad.sThumbLX = 0;
		m_state.Gamepad.sThumbLY = 0;
	}
	if ((m_state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && m_state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(m_state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && m_state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		m_state.Gamepad.sThumbRX = 0;
		m_state.Gamepad.sThumbRY = 0;
	}
}
