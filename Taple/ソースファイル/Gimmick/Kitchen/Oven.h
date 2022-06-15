//==========================================
//									  Oven.h
//	�{�֘A
//�@�����:AT12D171 No.29  ���{�a��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/11/** ����J�n
//		12/06
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "../Gimmick.h"


//===== �萔�E�}�N����` =====
#define OVEN_SIZE_X (12)
#define OVEN_SIZE_Y (7)
#define OVEN_SIZE_Z (1)


class Oven :public Gimmick //�t�b�N�N���X
{
public:
	Oven(void) {}
	virtual ~Oven(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;

protected:
};
