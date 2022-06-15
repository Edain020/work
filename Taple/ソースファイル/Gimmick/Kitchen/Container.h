//=============================================
//									Container.h
//	�{�֘A
//�@�����:AT12D171 No.29 ���{�a��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`�`
// 2020/11/** ����J�n
//		12/11  �e��
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once

//===== �C���N���[�h�� =====
#include "../Gimmick.h"


//===== �萔�E�}�N����` =====
#define CONTAINER_SIZE_X (6)
#define CONTAINER_SIZE_Y (5)
#define CONTAINER_SIZE_Z (1)



class Container :public Gimmick // �e��N���X
{
public:
	Container(void);
	virtual ~Container(void);

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
