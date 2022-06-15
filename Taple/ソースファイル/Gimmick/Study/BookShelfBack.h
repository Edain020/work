//==========================================
//									  BookShelfBack.h
//	�{�I�w�i�֘A
//�@�����:AT12D171 No.12 ���䋪��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/01/22 ����J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "../../DrawBuffer.h" 
#include "../../FBX/FBXPlayer.h"
#include "../Gimmick.h"


//===== �萔�E�}�N����` =====
#define BOOK_SHELF_BACK_SIZE_X (30)
#define BOOK_SHELF_BACK_SIZE_Y (45)
#define BOOK_SHELF_BACK_SIZE_Z (1)


//===== �N���X��` =====
class BookShelfBack :public Gimmick	// �{�I�w�i�N���X
{
public:
	BookShelfBack(void);
	virtual ~BookShelfBack(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;
protected:
};
