//==========================================
//								  KitchenRoom
//	�X�e�[�W���F�L�b�`�����[��
//�@�����:AT12D171 No.29 ���{�a��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/12/04 ����J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once

//===== �C���N���[�h�� =====
#include "Sound.h"


//===== �N���X��` =====
class Kitchen
{
public:
	Kitchen() {}
	~Kitchen() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	Sound * m_pBGM;
};