//==========================================
//								 Collision.h
//�@�����蔻��֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/10/30 ����J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� ======
#include <Windows.h>
#include "GameObject.h"


//===== �v���g�^�C�v�錾 ======
HRESULT InitCollision();
void UninitCollision();
void UpdateCollision();

void RegisterCollision(GameObject *pA, GameObject *pB);
bool CheckCollision(GameObject *pA, GameObject *pB);
