//===================================================== =
//									  LShelf.h
//	�{�֘A
//�@�����:AT12D171 No.29 ���{�a��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`�`�`�`�`�`�`
// 2020/11/** ����J�n
//		01/23 L���L�b�`���I
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "../Gimmick.h"


//===== �萔�E�}�N����` =====
#define HLSHELF_SIZE_X (1)
#define HLSHELF_SIZE_Y (5)
#define HLSHELF_SIZE_Z (1)


class HLShelf :public Gimmick //�L�b�`���I�N���X
{
public:
	HLShelf(void) {}
	virtual ~HLShelf(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;

protected:
};
