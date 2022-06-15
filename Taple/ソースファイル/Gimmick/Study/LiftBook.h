//==========================================
//									  LiftBook.h
//	�{�֘A
//�@�����:AT12D171 No.12 ���䋪��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/12/10 ����J�n 
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "../../DrawBuffer.h" 
#include "../../FBX/FBXPlayer.h"
#include "../Gimmick.h"


//===== �萔�E�}�N����` =====
#define LIFT_BOOK_SIZE_X (5)
#define LIFT_BOOK_SIZE_Y (1)
#define LIFT_BOOK_SIZE_Z (1)


class LiftBook :public Gimmick //�����{
{
public:
	LiftBook(void);
	LiftBook(bool isVertical, float radius, float seed, bool isPulsStart);
	virtual ~LiftBook(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	
	virtual void OnCollision(GameObject *other);

private:
	DirectX::XMFLOAT3 m_startPos;
	bool m_isVertical;
	bool m_isPulsStart;
	float m_fRadius;
	float m_fDeg;

	static Model *m_pModel;
protected:

};


