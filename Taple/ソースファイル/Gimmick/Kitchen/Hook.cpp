//==========================================
//									Hook.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.29  ¼–{aŒá
//
//````````XV—š—ð`````````
// 2020/11/** §ìŠJŽn
//		12/06 
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Hook.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* Hook::m_pModel = nullptr;



Hook::~Hook()
{
	Uninit();
}


bool Hook::Init()
{

	m_gimmickType = GIMMICK_HOOK;
	m_size.x = HOOK_SIZE_X;
	m_size.y = HOOK_SIZE_Y;
	m_size.z = HOOK_SIZE_Z;

	m_targetPos.y = -HOOK_SIZE_Y / 2.0f;

	//m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Kitchen/Hook/fukku_single.fbx"));
	}
	return true;
}


void Hook::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void Hook::Draw()
{	
	//SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x,m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();

	SHADER->SetWorld(DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f) *DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
	SHADER->SetTexture(NULL);
}
