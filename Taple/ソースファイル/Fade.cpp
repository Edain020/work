#include "Fade.h"
#include "Defines.h"


HRESULT Fade::Init()
{
	m_isOut = false;
	m_maxTime = 0.0f;
	m_time = 0.0f;

	m_pImage = new Image();
	m_pImage->SetSize(DirectX::XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));
	m_pImage->LoadTexture(ASSET("black.png"));
	return S_OK;
}


void Fade::Uninit()
{

}

void Fade::Update()
{
	// 経過時間の計測
	if (m_maxTime > m_time)
	{
		// 60FPS換算
		m_time += 1.0f / 60;
	}
	else
	{
		// フェードを実行していないときは
		// 実行時間に0を入れる
		m_maxTime = 0.0f;
	}
}


void Fade::Draw()
{
	//----- 透過色の計算 -----
	// 全体の実行時間を1としたときの経過時間の割合
	float rate = 1.0f;
	if (m_maxTime != 0.0f)
	{
		// フェードが完了すると0割が発生するので
		// エラー対処
		rate = m_time / m_maxTime;
	}
	// 透過色
	float alpha = rate;
	if (!m_isOut)
	{
		alpha = 1 - alpha;
	}

	// フェード用のポリゴンの透過設定
	m_pImage->SetAlpha(alpha);
	m_pImage->Draw();
}


// フェード完了判定
bool Fade::IsFinish()
{
	return m_maxTime <= m_time;
}


// フェード実行判定
bool Fade::IsExecute()
{
	// フェードを実行している→何秒かけてフェードするかが
	// 決まっている→0秒以上あるはず
	return m_maxTime > 0.0f;
}


// フェード開始
void Fade::Start(float time, bool isOut)
{
	m_time = 0;
	m_maxTime = time;
	m_isOut = isOut;
}
