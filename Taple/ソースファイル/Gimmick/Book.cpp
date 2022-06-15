//==========================================
//									Book.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//		   AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ð`````````
// 2020/11/** §ìŠJŽn
//		11/30 
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Book.h"
#include "../Shader.h"
#include "../Defines.h"


Model* Book::m_pModel = nullptr;



Book::~Book()
{
	Uninit();
}


bool Book::Init(void)
{
	m_gimmickType = GIMMICK_BOOK;
	m_size.x = BOOK_SIZE_X;
	m_size.y = BOOK_SIZE_Y;
	m_size.z = BOOK_SIZE_Z;

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Book/Book_Yoko.fbx"));
	}
	return true;
}


void Book::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void Book::Draw()
{
	SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
}
