//==========================================
//						    GimmickManager.h
//	ƒMƒ~ƒbƒNŠÇ—ŠÖ˜A
//@§ìÒ:AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ğ`````````
// 2020/11/30 §ìŠJn
//`````````````````````

//ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include <vector>
#include "Gimmick\Gimmick.h"


//===== ’è”Eƒ}ƒNƒ’è‹` =====
#define GIMMICKS GetGimmickMgr()


//===== ƒNƒ‰ƒX’è‹` =====
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


//===== ƒvƒƒgƒ^ƒCƒvéŒ¾ =====
GimmickMgr* GetGimmickMgr();
