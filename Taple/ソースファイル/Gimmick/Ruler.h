//==========================================
//									  Ruler.h
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
#define RULER_SIZE_X (20)
#define RULER_SIZE_Y (0.25f)
#define RULER_SIZE_Z (1)



class Ruler :public Gimmick
{
public:
	Ruler(void);
	virtual ~Ruler(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	static Model *m_pModel;

private:
protected:
};
