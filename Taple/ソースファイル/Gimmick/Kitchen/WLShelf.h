//======================================================
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
#define WLSHELF_SIZE_X (9)
#define WLSHELF_SIZE_Y (1)
#define WLSHELF_SIZE_Z (1)


class WLShelf :public Gimmick //�L�b�`���I�N���X
{
public:
	WLShelf(void) {}
	virtual ~WLShelf(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;

protected:
};
