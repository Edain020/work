//==========================================
//									Knife.h
//	�{�֘A
//�@�����:AT12D171 No.29 ���{�a��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/11/** ����J�n
//		12/04
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "../Gimmick.h"


//===== �萔�E�}�N����` =====
#define KNIFE_SIZE_X (0.25)
#define KNIFE_SIZE_Y (2)
#define KNIFE_SIZE_Z (1)


class Knife :public Gimmick
{
public:
	Knife(void);
	Knife(bool isVertical, float radius, float seed);
	virtual ~Knife(void);

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

