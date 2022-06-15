//==========================================
//								  Study.cpp
//	ƒXƒe[ƒWî•ñF‘Ö
//@§ìÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ğ`````````
// 2020/12/04 §ìŠJn
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Sound.h"


//===== ƒNƒ‰ƒX’è‹` =====
class Study
{
public:
	Study() {}
	~Study() {}

	bool Init();
	void Uninit();
	void Update();
	void Draw();

private:
	Sound *m_pBGM;
};