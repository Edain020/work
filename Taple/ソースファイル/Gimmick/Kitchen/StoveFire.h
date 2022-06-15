// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "Fire.h"
#include "../Gimmick.h"


//===== �萔�E�}�N����` =====
#define STOVEFIRE_NUM	(4)


//===== �N���X��` =====
class StoveFire	: public Gimmick
{
public:
	StoveFire() {}
	virtual ~StoveFire();

	virtual bool Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	virtual void OnCollision(GameObject *other);

private:
	Fire *m_pFires[STOVEFIRE_NUM];
};
