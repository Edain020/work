//==========================================1
//								  Study.cpp
//	ƒXƒe[ƒWî•ñFŽq‹Ÿ•”‰®
//@§ìŽÒ:AT12D171 No.12 ”’ˆä‹ª–ç
//
//````````XV—š—ð`````````
// 2020/12/04 §ìŠJŽn
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Study.h"
#include "Defines.h"
#include "GimmickManager.h"
#include "Gimmick\Gimmick.h"

#include "Gimmick/Study/LiftBook.h"
#include "Gimmick/Study/LeftBookShelf.h"
#include "Gimmick/Study/RightBookShelf.h"
#include "Gimmick/Study/Nail.h"
#include "Gimmick/Study/TowBooks_Vertical.h"
#include "Gimmick/Study/TowBook_Sideways.h"
#include "Gimmick/Study/BooksBlock.h"
#include "Gimmick/Study/StudyBook.h"
#include "Gimmick/Study/thorn.h"
#include "Gimmick/Study/FallBook.h"
#include "Gimmick/Study/PendulumClock.h"
#include "Gimmick/Study/BookShelfBack.h"



bool Study::Init()
{
	Gimmick *pGimmick;
	auto gimmicks = GIMMICKS->GetGimickList();

	gimmicks->reserve(50);

	//ƒIƒuƒWƒFƒNƒg//

	//“®‚­–{
	//‰¡‚WˆÚ“®
	pGimmick = new LiftBook(false, 8, 0, false);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(LIFT_BOOK_SIZE_X / 2 + 39, -LIFT_BOOK_SIZE_Y / 2 + 2, 0));
	pGimmick->Init();

	pGimmick = new LiftBook(false, 8, 0, true);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(LIFT_BOOK_SIZE_X / 2 + 54, -LIFT_BOOK_SIZE_Y / 2 + 1, 0));
	pGimmick->Init();

	pGimmick = new LiftBook(false, 8, 0, false);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(LIFT_BOOK_SIZE_X / 2 + 56, -LIFT_BOOK_SIZE_Y / 2 + 13, 0));
	pGimmick->Init();

	//c‚SˆÚ“®
	pGimmick = new LiftBook(true, 4, 0, false);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(LIFT_BOOK_SIZE_X / 2 - 2, -LIFT_BOOK_SIZE_Y / 2 + 15, 0));
	pGimmick->Init();


	pGimmick = new LiftBook(true, 4, 0, false);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(LIFT_BOOK_SIZE_X / 2 + 5, -LIFT_BOOK_SIZE_Y / 5 + 15, 0));
	pGimmick->Init();

	//c‚UˆÚ“®
	pGimmick = new LiftBook(true, 6, 0, false);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(LIFT_BOOK_SIZE_X / 2 - 8, -LIFT_BOOK_SIZE_Y / 2 + 17, 0));
	pGimmick->Init();

	pGimmick = new LiftBook(true, 6, 0, true);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(LIFT_BOOK_SIZE_X / 2 + 21, -LIFT_BOOK_SIZE_Y / 2 + 15, 0));
	pGimmick->Init();

	pGimmick = new LiftBook(true, 6, 0, false);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(LIFT_BOOK_SIZE_X / 2 + 26, -LIFT_BOOK_SIZE_Y / 2 + 8, 0));
	pGimmick->Init();

	pGimmick = new LiftBook(true, 6, 0, false);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(LIFT_BOOK_SIZE_X / 2 + 39, -LIFT_BOOK_SIZE_Y / 2 + 17, 0));
	pGimmick->Init();

	pGimmick = new LiftBook(true, 6, 0, false);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(LIFT_BOOK_SIZE_X / 2 + 95, -LIFT_BOOK_SIZE_Y / 2 + 6, 0));
	pGimmick->Init();

	//¶–{’I
	pGimmick = new LeftBookShelf();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(-9, 32, 0));
	pGimmick->Init();

	//‰E–{’I
	pGimmick = new RightBookShelf();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(70, 32, 0));
	pGimmick->Init();

	//“B
	pGimmick = new Nail();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(NAIL_SIZE_X / 2 + 13, -NAIL_SIZE_Y / 2 + 7, 0));
	pGimmick->Init();

	pGimmick = new Nail();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(NAIL_SIZE_X / 2 + 15, -NAIL_SIZE_Y / 2 + 15, 0));
	pGimmick->Init();

	pGimmick = new Nail();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(NAIL_SIZE_X / 2 + 3, -NAIL_SIZE_Y / 2 + 28, 0));
	pGimmick->Init();

	pGimmick = new Nail();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(NAIL_SIZE_X / 2 + 66, -NAIL_SIZE_Y / 2 + 7, 0));
	pGimmick->Init();

	pGimmick = new Nail();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(NAIL_SIZE_X / 2 + 67, -NAIL_SIZE_Y / 2 + 19, 0));
	pGimmick->Init();

	pGimmick = new Nail();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(NAIL_SIZE_X / 2 + 86, -NAIL_SIZE_Y / 2 + 18, 0));
	pGimmick->Init();

	pGimmick = new Nail();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(NAIL_SIZE_X / 2 + 80, -NAIL_SIZE_Y / 2 + 28, 0));
	pGimmick->Init();

	//–{‚Ì‘g‚Ý‡‚í‚¹c
	pGimmick = new TowBooks_V();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(-8, 6, 0));
	pGimmick->Init();

	//–{‚Ì‘g‚Ý‡‚í‚¹‰¡
	pGimmick = new TowBooks_S();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(72, 12, 0));
	pGimmick->Init();

	//–{‚Ì‘g‚Ý‡‚í‚¹‰ò
	pGimmick = new BooksBlock();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(13, 7, 0));
	pGimmick->Init();

	//–{
	pGimmick = new StudyBook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(STUDY_BOOK_SIZE_X / 2 + 44, -STUDY_BOOK_SIZE_Y / 2 + 12, 0));
	pGimmick->Init();

	pGimmick = new StudyBook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(STUDY_BOOK_SIZE_X / 2 + 44, -STUDY_BOOK_SIZE_Y / 2 + 22, 0));
	pGimmick->Init();

	pGimmick = new StudyBook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(STUDY_BOOK_SIZE_X / 2 + 90, -STUDY_BOOK_SIZE_Y / 2, 0));
	pGimmick->Init();

	//ž™
	pGimmick = new thorn();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(THORN_SIZE_X / 2 + 1, -THORN_SIZE_Y / 2 + 22, 0));
	pGimmick->Init();

	pGimmick = new thorn();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(THORN_SIZE_X / 2 + 77, -THORN_SIZE_Y / 2 + 22, 0));
	pGimmick->Init();

	//“|‚ê‚é–{
	pGimmick = new FallBook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(FALL_BOOK_SIZE_X / 2 + 12, -FALL_BOOK_SIZE_Y / 2 + 6, 0));
	pGimmick->Init();

	pGimmick = new FallBook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(FALL_BOOK_SIZE_X / 2 + 19, -FALL_BOOK_SIZE_Y / 2 + 28, 0));
	pGimmick->Init();

	//–{’I”wŒi
	pGimmick = new BookShelfBack();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(-9, 32, 1));
	pGimmick->Init();


	pGimmick = new BookShelfBack();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(70, 32, 1));
	pGimmick->Init();

	//U‚èŽqŽžŒv‰º‚Ì•”•ª
	pGimmick = new PendulumClock();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(PENDULUM_CLOCKL_SIZE_X / 2 + 57, -PENDULUM_CLOCKL_SIZE_Y / 2 + 30, 0));
	pGimmick->Init();


	gimmicks->shrink_to_fit();

	// BGM
	m_pBGM = new Sound();
	m_pBGM->Load(ASSET("Sound/BGM/Study.mp3"), true);
	m_pBGM->SetVolume(0.2f);
	m_pBGM->Play();

	return true;
}


void Study::Uninit()
{
	GIMMICKS->ClearGimmicks();

	// BGM
	m_pBGM->Stop();
	SAFE_DELETE(m_pBGM);
}


void Study::Update()
{
	GIMMICKS->Update();
}


void Study::Draw()
{
	GIMMICKS->Draw();
}
