//==========================================
//						  GimmickManager.cpp
//	ƒMƒ~ƒbƒNŠÇ—ŠÖ˜A
//@§ìŽÒ:AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ð`````````
// 2020/11/30 §ìŠJŽn
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "GimmickManager.h"
#include "Defines.h"
#include "Collision.h"
#include "main.h"
#include "Player.h"


//===== ƒOƒ[ƒoƒ‹•Ï” =====
GimmickMgr g_gimmickMgr;



void GimmickMgr::Init()
{
}


void GimmickMgr::Uninit()
{
	ClearGimmicks();
}


void GimmickMgr::Update()
{
	for (Gimmick *gimmick : m_gimmicks)
	{
		gimmick->Update();
	}
}


void GimmickMgr::Draw()
{
	for (Gimmick *gimmick : m_gimmicks)
	{
		gimmick->Draw();
	}
}


void GimmickMgr::ClearGimmicks()
{
	for (Gimmick *gimmick : m_gimmicks)
	{
		SAFE_DELETE(gimmick);
	}

	m_gimmicks.clear();
	m_gimmicks.shrink_to_fit();
}


void GimmickMgr::SetCollision(GameObject *object)
{
	for (Gimmick *gimmick : m_gimmicks)
	{
		if (gimmick->isSingle())
		{
			RegisterCollision(object, gimmick);
		}
		else
		{
			gimmick->SetCollision(object);
		}
	}
}


GimmickMgr* GetGimmickMgr()
{
	return &g_gimmickMgr;
}
