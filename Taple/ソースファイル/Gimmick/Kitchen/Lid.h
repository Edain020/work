//==========================================
//									Lid.h
//	�{�֘A
//�@�����:AT12D171 No.29 ���{�a��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/11/** ����J�n
//		12/11 �W�i�e��p�j
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "../Gimmick.h"


//===== �萔�E�}�N����` =====
#define LID_SIZE_X (1)
#define LID_SIZE_Y (6)
#define LID_SIZE_Z (1)


class Lid :public Gimmick // �W�N���X
{
public:
	Lid(void);
	virtual ~Lid(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void UpdatePlayer(Player *player);
	virtual void Draw(void);

private:
	bool m_isFallDown;
	float m_fAngle;
	float m_fFallSpeed;

	static Model *m_pModel;
protected:
};

