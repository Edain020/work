//==========================================
//								 Dish.h
//	�{�֘A
//�@�����:AT12D171 No.29 ���{�a��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/11/** ����J�n
//		12/11
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "../Gimmick.h"


//===== �萔�E�}�N����` =====
#define DISH_SIZE_X (1)
#define DISH_SIZE_Y (4)
#define DISH_SIZE_Z (1)


class Dish :public Gimmick //�M�N���X
{
public:
	Dish(void);
	Dish(float DesPawnPos); // ��������W���
	virtual ~Dish(void);

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual void OnCollision(GameObject *other);

private:
	DirectX::XMFLOAT3 m_spawnPos;
	int m_spawnCount; 
	bool m_isSpawn;
	int m_fallCount;
	float m_fallSpeed;
	float m_DeathPawnPos;	// �������W(������艺�ɗ������������)

	static Model *m_pModel;

protected:
};