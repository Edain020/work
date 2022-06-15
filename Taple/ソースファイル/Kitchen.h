//==========================================
//								  KitchenRoom
//	ƒXƒe[ƒWî•ñFƒLƒbƒ`ƒ“ƒ‹[ƒ€
//@§ìÒ:AT12D171 No.29 ¼–{aŒá
//
//````````XV—š—ğ`````````
// 2020/12/04 §ìŠJn
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Sound.h"


//===== ƒNƒ‰ƒX’è‹` =====
class Kitchen
{
public:
	Kitchen() {}
	~Kitchen() {}

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:
	Sound * m_pBGM;
};