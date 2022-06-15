//==========================================
//								 Gimmick.cpp
//	�M�~�b�N�֘A
//�@�����:AT12D171 No.12 ���䋪��
//		   AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/11/** ����J�n
//		11/30 
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

//===== �C���N���[�h�� =====
#include "Gimmick.h"
#include "../Defines.h"
#include "../Player.h"



Gimmick::Gimmick()
	: m_targetPos(0, 0, 0)
	, m_gimmickType(GIMMICK_NONE)
	, m_isTarget(false)
	, m_isSingle(true)
{
}


Gimmick::~Gimmick()
{
	Uninit();
}


void Gimmick::Uninit(void)
{
	SAFE_DELETE(m_pCube);
}
