//==========================================
//									  Book.h
//	�{�֘A
//�@�����:AT12D171 No.12 ���䋪��
//		   AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/11/** ����J�n
//		11/30 
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "Gimmick.h"


//===== �萔�E�}�N����` =====
#define BOOK_SIZE_X (7)
#define BOOK_SIZE_Y (2)
#define BOOK_SIZE_Z (1)


//===== �N���X��` =====
class Book :public Gimmick	// �{�N���X
{
public:
	Book(void) {}
	virtual ~Book(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;
protected:
};
