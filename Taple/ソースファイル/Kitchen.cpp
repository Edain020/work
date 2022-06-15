//==========================================
//								  KitchenRoom.cpp
//	ƒXƒe[ƒWî•ñFƒLƒbƒ`ƒ“
//@§ìŽÒ:AT12D171 No.29 ¼–{aŒá
//````````XV—š—ð`````````
// 2020/12/04 §ìŠJŽn
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Kitchen.h"
#include "Defines.h"
#include "GimmickManager.h"
#include "Gimmick\Gimmick.h"

#include "Gimmick\Kitchen\Knife.h"
#include "Gimmick\Kitchen\Hook.h"
#include "Gimmick\Kitchen\Cupboard.h"
#include "Gimmick\Kitchen\BigCupboard.h"
#include "Gimmick\Kitchen\Stand.h"
#include "Gimmick\Kitchen\Stove.h"
#include "Gimmick\Kitchen\StoveFire.h"
#include "Gimmick\Kitchen\Ladle.h"
#include "Gimmick\Kitchen\Container.h"
#include "Gimmick\Kitchen\Lid.h"
#include "Gimmick\Kitchen\CuttingBoard.h"
#include "Gimmick\Kitchen\Dish.h"
#include "Gimmick\Kitchen\Washingcupboard.h"
#include "Gimmick\Kitchen\Oven.h"
#include "Gimmick\Kitchen\Microwave.h"
#include "Gimmick\Kitchen\Faucet.h"
#include "Gimmick\Kitchen\RiceCooker.h"
#include "Gimmick\Kitchen\Seasning.h"
#include "Gimmick\Kitchen\WLShelf.h"
#include "Gimmick\Kitchen\HLShelf.h"


void Kitchen::Init()
{
	Gimmick *pGimmick;
	auto gimmicks = GIMMICKS->GetGimickList();

	gimmicks->reserve(50);


	// ƒRƒ“ƒ‘ä
	pGimmick = new Stand();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(STAND_SIZE_X / 2 -9 , -STAND_SIZE_Y / 2 - 1 + 0.5f , 0));
	pGimmick->Init();

	pGimmick = new Stand();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(STAND_SIZE_X / 2  +65, -STAND_SIZE_Y / 2 - 1 + 0.5f, 0));
	pGimmick->Init();


	// ƒRƒ“ƒ
	pGimmick = new Stove();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(STOVE_SIZE_X / 2 + 8 , -STOVE_SIZE_Y / 2 + 0, 0));
	pGimmick->Init();

	// ‰Š
	pGimmick = new StoveFire();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(STOVE_SIZE_X / 2 + 8, (-STOVE_SIZE_Y / 2 + 0) + STOVE_SIZE_Y, 0));
	pGimmick->Init();


	// ƒtƒbƒN
	pGimmick = new Hook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(HOOK_SIZE_X / 2 +4, -HOOK_SIZE_Y / 2 +8, 0));
	pGimmick->Init();

	pGimmick = new Hook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(HOOK_SIZE_X / 2 +10, -HOOK_SIZE_Y / 2 +11, 0));
	pGimmick->Init();

	pGimmick = new Hook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(HOOK_SIZE_X / 2 +17, -HOOK_SIZE_Y / 2 + 15, 0));
	pGimmick->Init();


	// •ï’š‚ÌƒtƒbƒN
	pGimmick = new Hook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(HOOK_SIZE_X / 2 +33, -HOOK_SIZE_Y / 2 +15, 0));
	pGimmick->Init();

	pGimmick = new Hook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(HOOK_SIZE_X / 2 +67, -HOOK_SIZE_Y / 2 +20, 0));
	pGimmick->Init();


	// 5˜AƒtƒbƒN
	pGimmick = new Hook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(HOOK_SIZE_X / 2 +62, -HOOK_SIZE_Y / 2 + 30, 0));
	pGimmick->Init();
	
	pGimmick = new Hook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(HOOK_SIZE_X / 2 +57, -HOOK_SIZE_Y / 2 +30 , 0));
	pGimmick->Init();

	pGimmick = new Hook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(HOOK_SIZE_X / 2 + 52, -HOOK_SIZE_Y / 2 +30, 0));
	pGimmick->Init();

	pGimmick = new Hook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(HOOK_SIZE_X / 2 + 47, -HOOK_SIZE_Y / 2 + 30, 0));
	pGimmick->Init();

	pGimmick = new Hook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(HOOK_SIZE_X / 2 + 42, -HOOK_SIZE_Y / 2 + 30, 0));
	pGimmick->Init();

	
	pGimmick = new Hook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(HOOK_SIZE_X / 2 + 37, -HOOK_SIZE_Y / 2 + 34, 0));
	pGimmick->Init();
	
	pGimmick = new Hook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(HOOK_SIZE_X / 2 + 30, -HOOK_SIZE_Y / 2 + 36, 0));
	pGimmick->Init();


	// 5˜AƒtƒbƒN
	pGimmick = new Hook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(HOOK_SIZE_X / 2 + 22, -HOOK_SIZE_Y / 2 + 36, 0));
	pGimmick->Init();
	
	pGimmick = new Hook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(HOOK_SIZE_X / 2 + 17, -HOOK_SIZE_Y / 2 + 36, 0));
	pGimmick->Init();
	
	pGimmick = new Hook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(HOOK_SIZE_X / 2 + 12, -HOOK_SIZE_Y / 2 + 36, 0));
	pGimmick->Init();
	
	pGimmick = new Hook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(HOOK_SIZE_X / 2 + 7, -HOOK_SIZE_Y / 2 + 36, 0));
	pGimmick->Init();
	
	pGimmick = new Hook();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(HOOK_SIZE_X / 2 +2, -HOOK_SIZE_Y / 2 + 36, 0));
	pGimmick->Init();
	

	// ‚¨‹Ê
	pGimmick = new Ladle();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(LADLE_SIZE_X / 2 +16, -LADLE_SIZE_Y / 2 + 9, 0));
	pGimmick->Init();


	// —eŠí(…“ü‚è)
	pGimmick = new Container();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(CONTAINER_SIZE_X / 2.0f + 19  , -CONTAINER_SIZE_Y / 2.0f + 4 , 0));
	pGimmick->Init();


	// ŠW
	pGimmick = new Lid();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(
		DirectX::XMFLOAT3(
			CONTAINER_SIZE_X / 2.0f + 19 + CONTAINER_SIZE_X / 2.0f + LID_SIZE_X / 2.0,
			CONTAINER_SIZE_Y / 2.0f + 4  + LID_SIZE_X / 2.0f,
			0));
	pGimmick->Init();


	// ‚Ü‚È”Â
	pGimmick = new CuttingBoard();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(CUTTINGBOARD_SIZE_X / 2 + 26, -CUTTINGBOARD_SIZE_Y / 2 + 0, 0));
	pGimmick->Init();


	// ƒiƒCƒt
	pGimmick = new Knife(true, 4, 0);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(KNIFE_SIZE_X / 2 +30 , -KNIFE_SIZE_Y / 2 +7, 0));
	pGimmick->Init();

	pGimmick = new Knife(true,4, 60);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(KNIFE_SIZE_X / 2 + 36, -KNIFE_SIZE_Y / 2 + 7, 0));
	pGimmick->Init();


	// ŽM
	pGimmick = new Dish(-10);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(DISH_SIZE_X / 2 + 47, -DISH_SIZE_Y / 2 + 13, 0));
	pGimmick->Init();

	pGimmick = new Dish(-10);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(DISH_SIZE_X / 2 + 60, -DISH_SIZE_Y / 2 + 8, 0));
	pGimmick->Init();

	pGimmick = new Dish(-10);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(DISH_SIZE_X / 2 + 62, -DISH_SIZE_Y / 2 + 10, 0));
	pGimmick->Init();


	// ã‚ÌŽM
	pGimmick = new Dish(14);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(DISH_SIZE_X / 2 + 71, -DISH_SIZE_Y / 2 +23, 0));
	pGimmick->Init();

	pGimmick = new Dish(14);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(DISH_SIZE_X / 2 +75, -DISH_SIZE_Y / 2 +25, 0));
	pGimmick->Init();

	pGimmick = new Dish(14);
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(DISH_SIZE_X / 2 + 78, -DISH_SIZE_Y / 2 + 27, 0));
	pGimmick->Init();
	

	// ô‚¢•¨HŠí’I
	pGimmick = new WashingCuoboard();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(WASHINGCUPBOARD_SIZE_X / 2 +68, -WASHINGCUPBOARD_SIZE_Y / 2+13, 0));
	pGimmick->Init();


	// HŠí’I
	pGimmick = new Cupboard();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(CUPBOARD_SIZE_X / 2 + 43, -CUPBOARD_SIZE_Y / 2 + 19, 0));
	pGimmick->Init();


	// ‘å‚«‚¢HŠí’I
	pGimmick = new BigCupboard();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(BIGCUPBOARD_SIZE_X / 2 -4, -BIGCUPBOARD_SIZE_Y / 2 + 19, 0));
	pGimmick->Init();


	// L’I‰¡
	pGimmick = new WLShelf();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(WLSHELF_SIZE_X / 2 - 12, -WLSHELF_SIZE_Y / 2 + 32, 0));
	pGimmick->Init();

	// L’Ic
	pGimmick = new HLShelf();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(HLSHELF_SIZE_X / 2 - 12, -HLSHELF_SIZE_Y / 2 + 37, 0));
	pGimmick->Init();


	// ŽÖŒû
	pGimmick = new Faucet();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(FAUCET_SIZE_X / 2 + 55, -FAUCET_SIZE_Y / 2 + 7 , 0));
	pGimmick->Init();


	// ƒI[ƒuƒ“
	pGimmick = new Oven();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(OVEN_SIZE_X / 2 + 23, -OVEN_SIZE_Y / 2 + 26, 0));
	pGimmick->Init();


	// “dŽqƒŒƒ“ƒW
	pGimmick = new Microwave();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(MICROWAVE_SIZE_X / 2 + 12 + 0.5f, -MICROWAVE_SIZE_Y / 2 + 25, 0));
	pGimmick->Init();
	

	// †”ÑŠí
	pGimmick = new RiceCooker();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(SEASNING_SIZE_X / 2 + 4 + 3.0f, -SEASNING_SIZE_Y / 2 + 24, 0));
	pGimmick->Init();


	// ’²–¡—¿
	pGimmick = new Seasning();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(SEASNING_SIZE_X / 2 + 60, -SEASNING_SIZE_Y / 2 + 22, 0));
	pGimmick->Init();

	pGimmick = new Seasning();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(SEASNING_SIZE_X / 2 + 57, -SEASNING_SIZE_Y / 2 + 22, 0));
	pGimmick->Init();

	pGimmick = new Seasning();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(SEASNING_SIZE_X / 2 + 54, -SEASNING_SIZE_Y / 2 + 22, 0));
	pGimmick->Init();

	pGimmick = new Seasning();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(SEASNING_SIZE_X / 2 + 50, -SEASNING_SIZE_Y / 2 + 22, 0));
	pGimmick->Init();

	pGimmick = new Seasning();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(SEASNING_SIZE_X / 2 + 47, -SEASNING_SIZE_Y / 2 + 22, 0));
	pGimmick->Init();

	pGimmick = new Seasning();
	gimmicks->push_back(pGimmick);
	pGimmick->SetPos(DirectX::XMFLOAT3(SEASNING_SIZE_X / 2 + 44, -SEASNING_SIZE_Y / 2 + 22, 0));
	pGimmick->Init();


	gimmicks->shrink_to_fit();

	// BGM
	m_pBGM = new Sound();
	m_pBGM->Load(ASSET("Sound/BGM/Kitchen.mp3"), true);
	m_pBGM->SetVolume(0.2f);
	m_pBGM->Play();
}


void Kitchen::Uninit()
{
	GIMMICKS->ClearGimmicks();

	// BGM
	m_pBGM->Stop();
	SAFE_DELETE(m_pBGM);
}


void Kitchen::Update()
{
	GIMMICKS->Update();
}


void Kitchen::Draw()
{
	GIMMICKS->Draw();
}
