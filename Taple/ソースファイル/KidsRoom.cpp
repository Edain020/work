//===== インクルード部 =====
#include "KidsRoom.h"
#include "Defines.h"
#include "GimmickManager.h"
#include "Gimmick\Gimmick.h"

#include "Gimmick\Desk.h"
#include "Gimmick\Crepas.h"
#include "Gimmick\Pin.h"
#include "Gimmick\Book.h"
#include "Gimmick\Eraser.h"
#include "Gimmick\Ruler.h"
#include "Gimmick\Closet.h"



void KidsRoom::Init()
{
	Gimmick *pGimmick;
	auto gimmicks = GIMMICKS->GetGimickList();

	gimmicks->reserve(50);

	//机
	pGimmick = new Desk();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(DESK_SIZE_X / 2 - 15 + 0.5f, -DESK_SIZE_Y / 2 - 1 + 0.5f, 0));

	pGimmick = new Desk();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(DESK_SIZE_X / 2 + 20 + 0.5f, -DESK_SIZE_Y / 2 - 1 + 0.5f, 0));

	pGimmick = new Desk();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(DESK_SIZE_X / 2 + 53 + 0.5f, -DESK_SIZE_Y / 2 - 1 + 0.5f, 0));

	pGimmick = new Desk();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(DESK_SIZE_X / 2 + 93 + 0.5f, -DESK_SIZE_Y / 2 - 1 + 0.5f, 0));

	pGimmick = new Desk();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(DESK_SIZE_X / 2 + 133 + 0.5f, -DESK_SIZE_Y / 2 - 1 + 0.5f, 0));

	pGimmick = new Desk();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(DESK_SIZE_X / 2 + 204 + 0.5f, -DESK_SIZE_Y / 2 - 1 + 0.5f, 0));

	//本
	pGimmick = new Book();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(BOOK_SIZE_X / 2 + 77, -BOOK_SIZE_Y / 2 + 1 + 0.5f, 0));

	pGimmick = new Book();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(BOOK_SIZE_X / 2 + 94, -BOOK_SIZE_Y / 2 + 1 + 0.5f, 0));

	pGimmick = new Book();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(BOOK_SIZE_X / 2 + 117, -BOOK_SIZE_Y / 2 + 1 + 0.5f, 0));

	//クレパス
	pGimmick = new Crepas();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(CREPAS_SIZE_X / 2 + 21, CREPAS_SIZE_Y / 2, 0));


	//消しゴム
	pGimmick = new Eraser(true, 5, 0);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(ERASER_SIZE_X / 2 + 125 + 0.5f, -ERASER_SIZE_Y / 2 + 2, 0));
	pGimmick->Init();

	pGimmick = new Eraser(true, 5, 180);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(ERASER_SIZE_X / 2 + 129 + 0.5f, -ERASER_SIZE_Y / 2 + 2, 0));
	pGimmick->Init();

	pGimmick = new Eraser(false, 5, 0);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(ERASER_SIZE_X / 2 + 168 + 0.5f - 7, -ERASER_SIZE_Y + 6, 0));
	pGimmick->Init();


	//画鋲
	pGimmick = new Pin();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(PIN_SIZE_X / 2 + 53, -PIN_SIZE_Y / 2 + 5, 0));


	pGimmick = new Pin();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(PIN_SIZE_X / 2 + 77, -PIN_SIZE_Y / 2 + 6, 0));

	pGimmick = new Pin();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(PIN_SIZE_X / 2 + 88, -PIN_SIZE_Y / 2 + 8, 0));

	pGimmick = new Pin();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(PIN_SIZE_X / 2 + 115, -PIN_SIZE_Y / 2 + 6, 0));

	pGimmick = new Pin();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(PIN_SIZE_X / 2 + 133, -PIN_SIZE_Y / 2 + 13, 0));

	pGimmick = new Pin();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(PIN_SIZE_X / 2 + 166, -PIN_SIZE_Y / 2 + 5, 0));

	pGimmick = new Pin();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(PIN_SIZE_X / 2 + 181, -PIN_SIZE_Y / 2 + 9, 0));

	pGimmick = new Pin();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(PIN_SIZE_X / 2 + 198, -PIN_SIZE_Y / 2 + 9, 0));

	//定規
	pGimmick = new Ruler();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(RULER_SIZE_X / 2 + 136 + 0.5f, -RULER_SIZE_Y / 2 + 6, 0));

	//タンス
	pGimmick = new Closet();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(CLOSET_SIZE_X / 2 + 169 + 0.5f, -CLOSET_SIZE_Y / 2 + 0 + 0.5f, 0));

	pGimmick = new Closet();
	gimmicks->push_back(pGimmick);
	pGimmick->Init();
	pGimmick->SetPos(DirectX::XMFLOAT3(CLOSET_SIZE_X / 2 + 183 + 0.5f, -CLOSET_SIZE_Y / 2 + 3 + 0.5f, 0));


	gimmicks->shrink_to_fit();

	// BGM
	m_pBGM = new Sound();
	m_pBGM->Load(ASSET("Sound/BGM/KidsRoom.mp3"), true);
	m_pBGM->SetVolume(0.2f);
	m_pBGM->Play();
}


void KidsRoom::Uninit()
{
	GIMMICKS->ClearGimmicks();

	// BGM
	m_pBGM->Stop();
	SAFE_DELETE(m_pBGM);
}


void KidsRoom::Update()
{
	GIMMICKS->Update();
}


void KidsRoom::Draw()
{
	GIMMICKS->Draw();
}
