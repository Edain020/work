//===== インクルード部 =====
#include "Timer.h"
#include "Defines.h"
#include "SceneManager.h"



// デフォルトの秒数を指定
Timer::Timer()
	: m_nTime(300)
	, m_nCnt(0)
	, m_pos(0, 0, 0)
	, m_size(1, 1, 0)
{
}


// 引数で秒数を指定
Timer::Timer(int time)
	: m_nTime(time)
	, m_nCnt(0)
	, m_pos(0, 0, 0)
	, m_size(1, 1, 0)
{
}


Timer::~Timer()
{
	Uninit();
}


HRESULT Timer::Init()
{
	int i;	// ループ用
	int nTime;	// 秒数計算用

	m_size = DirectX::XMFLOAT3(128, 72, 0);
	m_pos = DirectX::XMFLOAT3((SCREEN_WIDTH - m_size.x) / 2 - 50, (SCREEN_HEIGHT - m_size.y) / 2 - 50, 0);
	nTime = m_nTime;
	for (i = 0; i < TIMER_MAX_DIGIT; ++i)
	{
		m_pDigit[i] = new Number();
		m_pDigit[i]->SetSize(DirectX::XMFLOAT3(m_size.x / TIMER_MAX_DIGIT, m_size.y, m_size.z));
		m_pDigit[i]->SetPos(DirectX::XMFLOAT3(m_pos.x + m_size.x / 2.0f - (m_pDigit[i]->GetSize().x * i + m_pDigit[i]->GetSize().x / 2.0f), m_pos.y, m_pos.z));
		m_pDigit[i]->SetNum(nTime % 10);
		nTime /= 10;
	}

	return S_OK;
}


void Timer::Uninit()
{
	int i;	// ループ用

	for (i = 0; i < TIMER_MAX_DIGIT; ++i)
	{
		//SAFE_DELETE(m_pDigit[i]);
		if (m_pDigit[i]) { delete m_pDigit[i]; m_pDigit[i] = nullptr; }
	}
}


bool Timer::Update()
{
	m_nCnt++;
	if (m_nCnt > FPS)
	{
		if (m_nTime > 0)
		{
			m_nTime--;
		}

		int i;	// ループ用
		int nTime = m_nTime;	// 秒数計算用

		for (i = 0; i < TIMER_MAX_DIGIT; ++i)
		{
			m_pDigit[i]->SetNum(nTime % 10);
			nTime /= 10;
		}

		m_nCnt = 0;
	}

	return m_nTime <= 0;
}


void Timer::Draw()
{
	int i;	// ループ用
	for (i = 0; i < TIMER_MAX_DIGIT; ++i)
	{
		m_pDigit[i]->Draw();
	}
}


void Timer::SetPos(DirectX::XMFLOAT3 pos)
{
}


void Timer::SetSize(DirectX::XMFLOAT3 size)
{
}
