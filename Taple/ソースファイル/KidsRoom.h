// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "Sound.h"


//===== �N���X��` =====
class KidsRoom
{
public:
	KidsRoom() {}
	~KidsRoom() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	Sound *m_pBGM;
};
