//=============================================
//							CuttingBoard.h
//	�{�֘A
//�@�����:AT12D171 No.29 ���{�a��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`�`
// 2020/11/** ����J�n
//		12/11  �܂Ȕ�
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "../Gimmick.h"


//===== �萔�E�}�N����` =====
#define CUTTINGBOARD_SIZE_X (15)
#define CUTTINGBOARD_SIZE_Y (1)
#define CUTTINGBOARD_SIZE_Z (1)



class CuttingBoard :public Gimmick // ��N���X
{
public:
	CuttingBoard(void) {}
	virtual ~CuttingBoard(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Draw(void);

	virtual bool isClimb(void) { return true; }

private:
	static Model *m_pModel;

protected:
};




