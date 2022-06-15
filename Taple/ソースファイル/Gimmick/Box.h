//==========================================
//									  Box.h
//	�������ᔠ�i�S�[���j�֘A
//�@�����:AT12D171 No.12 ���䋪��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/12/25 ����J�n 
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "../DrawBuffer.h" 
#include "../FBX/FBXPlayer.h"
#include "Gimmick.h"


//===== �萔�E�}�N����` =====
#define BOX_SIZE_X (7)
#define BOX_SIZE_Y (2)
#define BOX_SIZE_Z (1)


//===== �N���X��` =====
class Box :public Gimmick	// �{�N���X
{
public:
	Box(void)
		: m_fCnt(0.0f)
	{}
	virtual ~Box(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual bool isClimb(void) { return true; }

private:
	static Model *m_pModel;
	static Model *m_pStrModel;

	float m_fCnt;
protected:
};
