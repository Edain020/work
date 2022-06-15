
// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "Number.h"


//===== �萔�E�}�N����` =====
#define TIMER_MAX_NUM	(999)
#define TIMER_MAX_DIGIT	(3)


//===== �N���X��` =====
class Timer	// �^�C�}�[�N���X
{
public:
	Timer();	// �f�t�H���g�̕b�����w��
	Timer(int time);	// �����ŕb�����w��
	~Timer();

	HRESULT Init();
	void Uninit();
	bool Update();
	void Draw();

	void SetPos(DirectX::XMFLOAT3 pos);
	void SetSize(DirectX::XMFLOAT3 size);

private:
	DirectX::XMFLOAT3 m_pos;	// ���S���W
	DirectX::XMFLOAT3 m_size;	// �S�Ă̌����̑傫���̍��v

	int m_nCnt;		// �J�E���^�[(�t���[���v�Z�p)
	int m_nTime;	// �c�莞��(�b)
	Number *m_pDigit[TIMER_MAX_DIGIT];	// �e���̃I�u�W�F�N�g
};
