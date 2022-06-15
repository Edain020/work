#ifndef _BATTLE_H_
#define _BATTLE_H_

//===== インクルード部 =====
#include "unit.h"

void InitBattle(void);
void UpdateBattle(void);
void DrawBattle(void);
void EndBattle(void);

void Battle(UNIT*);

#endif // !_BATTLE_H_
