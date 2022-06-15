//==========================================
//							Seasning.h
//	�{�֘A
//�@�����:AT12D171 No.29 ���{�a��
//		 
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/11/** ����J�n
//		01/23 
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "../Gimmick.h"


//===== �萔�E�}�N����` =====
#define SEASNING_SIZE_X (2)
#define SEASNING_SIZE_Y (3)
#define SEASNING_SIZE_Z (1)


class Seasning :public Gimmick
{
public:
	Seasning(void) {}
	virtual ~Seasning(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;

protected:
};
