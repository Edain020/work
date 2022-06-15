//==========================================
//									  Pin.h
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
#include "Pendulum.h"
#include "../DrawBuffer.h" 
#include "../FBX/FBXPlayer.h"


//===== �萔�E�}�N����` =====
#define PIN_SIZE_X (0.25f)
#define PIN_SIZE_Y (0.25f)
#define PIN_SIZE_Z (1)


class Pin :public Pendulum //��e�N���X
{
public:
	Pin(void);
	virtual ~Pin(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

	static Model *m_pModel;

private:
protected:
};

