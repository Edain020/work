// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "Gimmick.h"


//===== �N���X��` =====
class Pendulum : public Gimmick
{
public:
	Pendulum();
	~Pendulum();

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void UpdatePlayer(Player *player);

	void SetPendulum(GameObject *obj) { m_pPendulum = obj; }

protected:
	float m_fLength;
	float m_fMinLength;
	float m_fMove;
	float m_fRollSpeed;

	GameObject *m_pPendulum;
};