//==========================================
//									Ladle.h
//	�{�֘A
//�@�����:AT12D171 No.29  ���{�a��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/11/** ����J�n
//		12/11
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "../Gimmick.h"

//===== �萔�E�}�N����` =====
#define LADLE_SIZE_X (3)
#define LADLE_SIZE_Y (0)
#define LADLE_SIZE_Z (1)


class Ladle :public Gimmick //�t�b�N�N���X
{
public:
	Ladle(void) {}
	virtual ~Ladle(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;

protected:
};

