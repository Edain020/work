//==========================================
//								 Collision.h
//@“–‚½‚è”»’èŠÖ˜A
//@§ìÒ:AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ğ`````````
// 2020/10/30 §ìŠJn
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” ======
#include <Windows.h>
#include "GameObject.h"


//===== ƒvƒƒgƒ^ƒCƒvéŒ¾ ======
HRESULT InitCollision();
void UninitCollision();
void UpdateCollision();

void RegisterCollision(GameObject *pA, GameObject *pB);
bool CheckCollision(GameObject *pA, GameObject *pB);
