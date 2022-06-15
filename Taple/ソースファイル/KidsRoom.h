// インクルードガード
#pragma once


//===== インクルード部 =====
#include "Sound.h"


//===== クラス定義 =====
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
