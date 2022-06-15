//=============================================
//									  Stove.h
//	�{�֘A
//�@�����:AT12D171 No.29 ���{�a��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`�`
// 2020/11/** ����J�n
//		12/11  �R����
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "../Gimmick.h"


//===== �萔�E�}�N����` =====
#define STOVE_SIZE_X (7)
#define STOVE_SIZE_Y (1)
#define STOVE_SIZE_Z (1)



class Stove :public Gimmick // �R�����N���X
{
public:
	Stove() {}
	virtual ~Stove(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

	virtual bool isClimb(void) { return true; }

private:
	static Model *m_pModel;

protected:
};



