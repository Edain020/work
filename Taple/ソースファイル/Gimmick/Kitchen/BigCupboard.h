//==========================================
//									  Cupboard.h
//	�{�֘A
//�@�����:AT12D171 No.29  ���{�a��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/11/** ����J�n
//		12/07
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "../Gimmick.h"


//===== �萔�E�}�N����` =====
#define BIGCUPBOARD_SIZE_X (40)
#define BIGCUPBOARD_SIZE_Y (1)
#define BIGCUPBOARD_SIZE_Z (1)


class BigCupboard :public Gimmick //��e�N���X
{
public:
	BigCupboard(void) {}
	virtual ~BigCupboard(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;
protected:
};

