//==========================================
//								  Study.cpp
//	�X�e�[�W���F����
//�@�����:AT12D171 No.12 ���䋪��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/12/04 ����J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once

//===== �C���N���[�h�� =====
#include "Sound.h"


//===== �N���X��` =====
class Study
{
public:
	Study() {}
	~Study() {}

	bool Init();
	void Uninit();
	void Update();
	void Draw();

private:
	Sound *m_pBGM;
};