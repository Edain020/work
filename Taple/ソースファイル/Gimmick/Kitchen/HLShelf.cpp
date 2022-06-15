//=====================================================
//									HLShelf.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.29 ¼–{aŒá
//
//````````XV—š—ð``````````````
// 2020/11/** §ìŠJŽn
//		12/10 ƒLƒbƒ`ƒ“’I
//``````````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "HLShelf.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* HLShelf::m_pModel = nullptr;



HLShelf::~HLShelf()
{
	Uninit();
}


bool HLShelf::Init()
{
	m_gimmickType = GIMMICK_HLSHELF;
	m_size.x = HLSHELF_SIZE_X;
	m_size.y = HLSHELF_SIZE_Y;
	m_size.z = HLSHELF_SIZE_Z;

//	m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
//		m_pModel = new Model();
		//m_pModel->LoadModel(ASSET("Model/Kitchen/HLShelf/pushHLShelf.fbx"));
	}
	return true;
}


void HLShelf::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void HLShelf::Draw()
{
//	SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
//	m_pCube->Draw();

	//SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	//m_pModel->Draw();
}
