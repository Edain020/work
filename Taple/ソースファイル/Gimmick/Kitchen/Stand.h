//=============================================
//									  Stand.h
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
#include "../Gimmick.h"


//===== �萔�E�}�N����` =====
#define STAND_SIZE_X (55)
#define STAND_SIZE_Y (12)
#define STAND_SIZE_Z (1)



class Stand :public Gimmick // ��N���X
{
public:
	Stand(void) {}
	virtual ~Stand(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;

protected:
};



