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
	// �o�ߎ��Ԃ̌v��
	if (m_maxTime > m_time)
	{
		// 60FPS���Z
		m_time += 1.0f / 60;
	}
	else
	{
		// �t�F�[�h�����s���Ă��Ȃ��Ƃ���
		// ���s���Ԃ�0������
		m_maxTime = 0.0f;
	}
}


void Fade::Draw()
{
	//----- ���ߐF�̌v�Z -----
	// �S�̂̎��s���Ԃ�1�Ƃ����Ƃ��̌o�ߎ��Ԃ̊���
	float rate = 1.0f;
	if (m_maxTime != 0.0f)
	{
		// �t�F�[�h�����������0������������̂�
		// �G���[�Ώ�
		rate = m_time / m_maxTime;
	}
	// ���ߐF
	float alpha = rate;
	if (!m_isOut)
	{
		alpha = 1 - alpha;
	}

	// �t�F�[�h�p�̃|���S���̓��ߐݒ�
	m_pImage->SetAlpha(alpha);
	m_pImage->Draw();
}


// �t�F�[�h��������
bool Fade::IsFinish()
{
	return m_maxTime <= m_time;
}


// �t�F�[�h���s����
bool Fade::IsExecute()
{
	// �t�F�[�h�����s���Ă��遨���b�����ăt�F�[�h���邩��
	// ���܂��Ă��遨0�b�ȏ゠��͂�
	return m_maxTime > 0.0f;
}


// �t�F�[�h�J�n
void Fade::Start(float time, bool isOut)
{
	m_time = 0;
	m_maxTime = time;
	m_isOut = isOut;
}
