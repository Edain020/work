
//==========================================
//									  Faucet.h
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
#include "../Pendulum.h"


//===== �萔�E�}�N����` =====
#define FAUCET_SIZE_X (1)
#define FAUCET_SIZE_Y (2)
#define FAUCET_SIZE_Z (1)


class Faucet :public Pendulum //�֌��N���X
{
public:
	Faucet(void) {}
	virtual ~Faucet(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;

protected:
};