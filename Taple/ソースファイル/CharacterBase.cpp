//==========================================
//						   CharacterBase.cpp
//@ƒLƒƒƒ‰ƒNƒ^[ŠÖ˜A
//@§ìŽÒ:AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ð`````````
// 2020/10/28 §ìŠJŽn
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "CharacterBase.h"
#include "Texture.h"
#include "Defines.h"



// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
CharacterBase::CharacterBase(void)
	: m_fYaw(0)
	, m_fPitch(0)
	, m_fRoll(0)
{
	// ƒLƒƒƒ‰ƒNƒ^[‚Í“®‚­ƒIƒuƒWƒFƒNƒg‚¾‚ë‚¤
	m_collisionType = COLLISION_DYNAMIC;
}


// ƒfƒXƒgƒ‰ƒNƒ^
CharacterBase::~CharacterBase(void)
{
	Uninit();
}


void CharacterBase::Draw(void)
{
	SHADER->SetWorld(
		DirectX::XMMatrixRotationRollPitchYaw(m_fPitch, m_fYaw, m_fRoll)
		* DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z)
		* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pCube->Draw();
}
