//==========================================
//						      Microwave.h
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
#define MICROWAVE_SIZE_X (10)
#define MICROWAVE_SIZE_Y (6)
#define MICROWAVE_SIZE_Z (1)


class Microwave :public Gimmick //�t�b�N�N���X
{
public:
	Microwave(void) {}
	virtual ~Microwave(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;

protected:
};
