//==========================================
//									  TowBooks_S.h
//	�{�֘A
//�@�����:AT12D171 No.12 ���䋪��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/01/03 ����J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "../Gimmick.h"
#include "../../DrawBuffer.h" 
#include "../../FBX/FBXPlayer.h"


//===== �萔�E�}�N����` =====
#define TOW_BOOKS_S_SIZE_X (7)
#define TOW_BOOKS_S_SIZE_Y (2)
#define TOW_BOOKS_S_SIZE_Z (1)

#define TOW_BOOKS_S_PART_NUM (2)

#define UP_BOOK_SIZE_X (6)
#define UP_BOOK_SIZE_Y (1)

#define DOWN_BOOK_SIZE_X (7)
#define DOWN_BOOK_SIZE_Y (1)


class TowBooks_S :public Gimmick //�{�N���X
{
public:
	TowBooks_S(void);
	virtual ~TowBooks_S(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual void SetCollision(GameObject *object);

private:
	static Model *m_pModel;
	GameObject *m_pCollision[8];
protected:
};

