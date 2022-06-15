//==========================================
//									  Crepas.h
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
#include "../Sound.h"


//===== �萔�E�}�N����` =====
#define CREPAS_SIZE_X (7)
#define CREPAS_SIZE_Y (1)
#define CREPAS_SIZE_Z (1)


class Crepas :public Gimmick //�N���p�X�N���X
{
public:
	Crepas(void);
	virtual ~Crepas(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void UpdatePlayer(Player *player);
	virtual void Draw(void);
	
	virtual bool isClimb(void) { return true; }

private:
	float m_fMoveDis;
	bool m_isPlaySE;
	bool m_isStopSE;

	static Model *m_pModel;
	static Sound *m_pSE;
protected:
};

