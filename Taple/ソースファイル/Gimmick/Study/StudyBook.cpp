//==========================================
//									StudyBook.cpp
//	–{ŠÖ˜A
//@§ìŽÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ð`````````
// 2020/01/05 §ìŠJŽn
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "StudyBook.h"
#include "../../Shader.h"
#include "../../Defines.h"


Model* StudyBook::m_pModel = nullptr;



StudyBook::StudyBook()
{
}


StudyBook::~StudyBook()
{
	Uninit();
}


bool StudyBook::Init(void)
{
	m_gimmickType = GIMMICK_BOOK;
	m_size.x = STUDY_BOOK_SIZE_X;
	m_size.y = STUDY_BOOK_SIZE_Y;
	m_size.z = STUDY_BOOK_SIZE_Z;

	if (m_pModel == nullptr)
	{
		m_pModel = new Model();
		m_pModel->LoadModel(ASSET("Model/Study//StudyBook/StudyBook_Yoko.fbx"));
	}
	return true;
}


void StudyBook::Uninit(void)
{
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pModel);
}


void StudyBook::Update()
{
}


void StudyBook::Draw()
{
	SHADER->SetWorld(DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	m_pModel->Draw();
}
