//==========================================
//									  Nail.h
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
#include "../Pendulum.h"


//===== �萔�E�}�N����` =====
#define NAIL_SIZE_X (0.25f)
#define NAIL_SIZE_Y (0.25f)
#define NAIL_SIZE_Z (1)


class Nail :public Pendulum //��e�N���X
{
public:
	Nail(void);
	virtual ~Nail(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static Model *m_pModel;

private:
protected:
};

