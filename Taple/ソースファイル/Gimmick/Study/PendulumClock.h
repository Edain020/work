//==========================================
//									  PendulumClock.h
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
#define PENDULUM_CLOCKL_SIZE_X (3)
#define PENDULUM_CLOCKL_SIZE_Y (3)
#define PENDULUM_CLOCKL_SIZE_Z (1)


class PendulumClock :public Gimmick //��e�N���X
{
public:
	PendulumClock(void);
	virtual ~PendulumClock(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

private:
	static Model *m_pModel;
protected:
};

