//==========================================
//									  thorn.h
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
#define THORN_SIZE_X (5)
#define THORN_SIZE_Y (1)
#define THORN_SIZE_Z (1)


class thorn :public Gimmick //��e�N���X
{
public:
	thorn(void);
	virtual ~thorn(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static Model *m_pModel;

private:
protected:
};

