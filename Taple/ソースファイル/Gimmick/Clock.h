//==========================================
//									  Clock.h
//	�{�֘A
//�@�����:AT12D171 No.12 ���䋪��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/12/04 ����J�n
//		 
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "Gimmick.h"
#include "../DrawBuffer.h" 
#include "../FBX/FBXPlayer.h"


//===== �萔�E�}�N����` =====
#define CLOCK_SIZE_X (3)
#define CLOCK_SIZE_Y (3)
#define CLOCK_SIZE_Z (1)


class Clock :public Gimmick //��e�N���X
{
public:
	Clock(void);
	Clock(float radius, float seed);
	virtual ~Clock(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);


	static Model *m_pModel;

private:
	DirectX::XMFLOAT3 m_startPos;
	bool m_isVertical;
	float m_fRadius;
	float m_fDeg;
protected:
};

#pragma once
