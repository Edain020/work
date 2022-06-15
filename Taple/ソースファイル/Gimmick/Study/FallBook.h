//==========================================
//									  FallBook.h
//	�{�֘A
//�@�����:AT12D171 No.12 ���䋪��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/01/05 ����J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "../Gimmick.h"
#include "../../DrawBuffer.h" 
#include "../../FBX/FBXPlayer.h"
#include "../../Sound.h"


//===== �萔�E�}�N����` =====
#define FALL_BOOK_SIZE_X (1)
#define FALL_BOOK_SIZE_Y (7)
#define FALL_BOOK_SIZE_Z (1)


//===== �N���X��` =====
class FallBook :public Gimmick	// �{�N���X
{
public:
	FallBook(void);
	virtual ~FallBook(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void UpdatePlayer(Player *player);
	virtual void Draw(void);

private:
	bool m_isFallDown;
	float m_fAngle;
	float m_fFallSpeed;

	static Model *m_pModel;
	static Sound *m_pSE;
protected:
};
