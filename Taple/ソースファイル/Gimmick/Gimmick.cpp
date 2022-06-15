//==========================================
//								 Gimmick.cpp
//	ƒMƒ~ƒbƒNŠÖ˜A
//@§ìÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//		   AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ğ`````````
// 2020/11/** §ìŠJn
//		11/30 
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
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
