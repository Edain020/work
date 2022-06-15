//==========================================
//									BookShelfBack.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ð`````````
// 2020/01/05 §ìŠJŽn
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "BookShelfBack.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* BookShelfBack::m_pModel = nullptr;



BookShelfBack::BookShelfBack()
{
}


BookShelfBack::~BookShelfBack()
{
	Uninit();
}


bool BookShelfBack::Init(void)
{
	m_gimmickType = GIMMICK_BOOK;
	m_size.x = BOOK_SHELF_BACK_SIZE_X;
	m_size.y = BOOK_SHELF_BACK_SIZE_Y;
	m_size.z = BOOK_SHELF_BACK_SIZE_Z;

	m_pCube = new Cube();

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Study/BookShelfBack/BookShelfBack.fbx"));
	}
	return true;
}


void BookShelfBack::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void BookShelfBack::Update()
{
}


void BookShelfBack::Draw()
{
	//SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x + BOOK_SHELF_BACK_SIZE_X/2, m_pos.y - BOOK_SHELF_BACK_SIZE_Y/2, m_pos.z - 1));
	SHADER->SetWorld(DirectX::XMMatrixRotationRollPitchYaw(0.0f, DEG_TO_RAD(180.0f), 0.0f) * DirectX::XMMatrixTranslation(m_pos.x + BOOK_SHELF_BACK_SIZE_X / 2, m_pos.y - BOOK_SHELF_BACK_SIZE_Y / 2, m_pos.z - 1));
	m_pModel->Draw();

	SHADER->SetTexture(NULL);
}
