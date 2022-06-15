
// インクルードガード
#pragma once


//===== インクルード部 =====
#include "Number.h"


//===== 定数・マクロ定義 =====
#define TIMER_MAX_NUM	(999)
#define TIMER_MAX_DIGIT	(3)


//===== クラス定義 =====
class Timer	// タイマークラス
{
public:
	Timer();	// デフォルトの秒数を指定
	Timer(int time);	// 引数で秒数を指定
	~Timer();

	HRESULT Init();
	void Uninit();
	bool Update();
	void Draw();

	void SetPos(DirectX::XMFLOAT3 pos);
	void SetSize(DirectX::XMFLOAT3 size);

private:
	DirectX::XMFLOAT3 m_pos;	// 中心座標
	DirectX::XMFLOAT3 m_size;	// 全ての桁数の大きさの合計

	int m_nCnt;		// カウンター(フレーム計算用)
	int m_nTime;	// 残り時間(秒)
	Number *m_pDigit[TIMER_MAX_DIGIT];	// 各桁のオブジェクト
};
