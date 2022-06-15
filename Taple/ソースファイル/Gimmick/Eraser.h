//==========================================
//									  Eraser.h
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
#include "../DrawBuffer.h" 
#include "../FBX/FBXPlayer.h"
#include "Gimmick.h"


//===== �萔�E�}�N����` =====
#define ERASER_SIZE_X (2)
#define ERASER_SIZE_Y (0.5f)
#define ERASER_SIZE_Z (1)


class Eraser :public Gimmick //�����S���N���X
{
public:
	Eraser(void);
	Eraser(bool isVertical, float radius, float deg);
	virtual ~Eraser(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual void OnCollision(GameObject *other);

private:
	DirectX::XMFLOAT3 m_startPos;
	bool m_isVertical;
	float m_fRadius;
	float m_fDeg;

	static Model *m_pModel;
protected:

};


