//=============================================
//						    WashingCuoboard.h
//	�{�֘A
//�@�����:AT12D171 No.29 ���{�a��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`�`
// 2020/11/** ����J�n
//		12/11  �R�����̑�(����)
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "../Pendulum.h"


//===== �萔�E�}�N����` =====
#define WASHINGCUPBOARD_SIZE_X (15)
#define WASHINGCUPBOARD_SIZE_Y (6)
#define WASHINGCUPBOARD_SIZE_Z (1)



class WashingCuoboard :public Pendulum // ��N���X
{
public:
	WashingCuoboard(void) {}
	virtual ~WashingCuoboard(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;

protected:
};




