//=============================================
//								RiceCooker.h
//	�{�֘A
//�@�����:AT12D171 No.29 ���{�a��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`�`
// 2020/11/** ����J�n
//		12/11  ���ъ�
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once

//===== �C���N���[�h�� =====
#include "../Gimmick.h"


//===== �萔�E�}�N����` =====
#define RICECOOKER_SIZE_X (8)
#define RICECOOKER_SIZE_Y (5)
#define RICECOOKER_SIZE_Z (1)



class RiceCooker :public Gimmick // �e��N���X
{
public:
	RiceCooker(void);
	virtual ~RiceCooker(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

	virtual void SetCollision(GameObject *object);

private:
	static Model *m_pModel;

	GameObject *m_pCollision[2];
	GameObject *m_pDeathArea;
protected:
};
