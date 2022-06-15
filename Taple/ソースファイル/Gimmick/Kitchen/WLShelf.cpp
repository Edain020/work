//=====================================================
//									WLShelf.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.29 ¼–{aŒá
//
//````````XV—š—ð``````````````
// 2020/11/** §ìŠJŽn
//		12/10 ƒLƒbƒ`ƒ“’I
//``````````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "WLShelf.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* WLShelf::m_pModel = nullptr;



WLShelf::~WLShelf()
{
	Uninit();
}


bool WLShelf::Init()
{
	m_gimmickType = GIMMICK_WLSHELF;
	m_size.x = WLSHELF_SIZE_X;
	m_size.y = WLSHELF_SIZE_Y;
	m_size.z = WLSHELF_SIZE_Z;

	//m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Kitchen/LShelf/tanaL.fbx"));
	}
	return true;
}


void WLShelf::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void WLShelf::Draw()
{	
	//SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pCube->Draw();
	
	SHADER->SetWorld(DirectX::XMMatrixScaling(0.2f, 0.1f, 0.1f) *DirectX::XMMatrixTranslation(m_pos.x-0.5f, m_pos.y+2.3f, m_pos.z));
	m_pModel->Draw();
	SHADER->SetTexture(NULL);
}
