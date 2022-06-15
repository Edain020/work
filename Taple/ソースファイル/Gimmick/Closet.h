//==========================================
//									  Closet.h
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
#include "../DrawBuffer.h" 
#include "../FBX/FBXPlayer.h"


//===== �萔�E�}�N����` =====
#define CLOSET_SIZE_X (10)
#define CLOSET_SIZE_Y (16)
#define CLOSET_SIZE_Z (1)


//===== �N���X��` =====
class Closet :public Gimmick //�N���[�[�b�g�N���X
{
public:
	Closet(void) {}
	virtual ~Closet(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;
protected:
};
