//==========================================
//						    GimmickManager.h
//	�M�~�b�N�Ǘ��֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/11/30 ����J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

//�C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include <vector>
#include "Gimmick\Gimmick.h"


//===== �萔�E�}�N����` =====
#define GIMMICKS GetGimmickMgr()


//===== �N���X��` =====
class GimmickMgr
{
public:
	GimmickMgr() {}
	~GimmickMgr() { Uninit(); }

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void ClearGimmicks();

	void SetCollision(GameObject *object);

	std::vector<Gimmick*>* GetGimickList(void) { return &m_gimmicks; }

private:
	std::vector<Gimmick*> m_gimmicks;
};


//===== �v���g�^�C�v�錾 =====
GimmickMgr* GetGimmickMgr();
