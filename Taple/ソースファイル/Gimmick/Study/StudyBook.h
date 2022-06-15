//==========================================
//									  StudyBook.h
//	�{�֘A
//�@�����:AT12D171 No.12 ���䋪��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/01/05 ����J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "../../DrawBuffer.h" 
#include "../../FBX/FBXPlayer.h"
#include "../Gimmick.h"


//===== �萔�E�}�N����` =====
#define STUDY_BOOK_SIZE_X (5)
#define STUDY_BOOK_SIZE_Y (1)
#define STUDY_BOOK_SIZE_Z (1)


//===== �N���X��` =====
class StudyBook :public Gimmick	// �{�N���X
{
public:
	StudyBook(void);
	virtual ~StudyBook(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static Model *m_pModel;

private:
protected:
};
