//==========================================
//							   Collision.cpp
//�@�����蔻��֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/10/30 ����J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

//===== �C���N���[�h�� =====
#include "Collision.h"
#include "Player.h"


//===== �萔�E�}�N����` =====
// �����蔻����s���g�ݍ��킹�̍ő吔 
// ���ق�Ƃ̓��X�g�\���Ő����̂Ȃ������悢
#define MAX_COLLISION_REGISTER	(1000)


//===== �v���g�^�C�v�錾 =====
// �����o������
void Push(GameObject *pDynamic, GameObject *pStatic);


//===== �O���[�o���ϐ� =====
GameObject *m_pList[MAX_COLLISION_REGISTER][2];
int m_registerNum;	// �o�^������



HRESULT InitCollision(void)
{
	for (int i = 0; i < MAX_COLLISION_REGISTER; ++i)
	{
		m_pList[i][0] = m_pList[i][1] = NULL;
	}

	return S_OK;
}


void UninitCollision(void)
{
	for (int i = 0; i < MAX_COLLISION_REGISTER; ++i)
	{
		m_pList[i][0] = m_pList[i][1] = NULL;
	}
}


void UpdateCollision(void)
{
	// �����蔻�菈��
	for (int i = 0; i < m_registerNum; ++i)
	{
		GameObject *pA = m_pList[i][0];
		GameObject *pB = m_pList[i][1];

		// �o�^����Ă��Ȃ��f�[�^�͎��{���Ȃ�
		if (pA == nullptr || pB == nullptr)
		{
			continue;
		}

		// �l�p�`���m�̓����蔻��
		// 2D�ł�3D�ł�
		// ���S�܂ł̋��� < �����̑傫���𑫂����킹����
		// �͕ς��Ȃ��B�v�Z���鎲�������邾��

		DirectX::XMFLOAT3 aPos = pA->GetPos();
		DirectX::XMFLOAT3 bPos = pB->GetPos();
		DirectX::XMFLOAT3 aSize = pA->GetSize();
		DirectX::XMFLOAT3 bSize = pB->GetSize();

		DirectX::XMFLOAT3 distance(
			fabsf(bPos.x - aPos.x),
			fabsf(bPos.y - aPos.y),
			fabsf(bPos.z - aPos.z)
		);

		bool hitX = distance.x < (aSize.x + bSize.x) * 0.5f;
		bool hitY = distance.y < (aSize.y + bSize.y) * 0.5f;
		bool hitZ = distance.z < (aSize.z + bSize.z) * 0.5f;

		if (hitX && hitY && hitZ)
		{
			pA->OnCollision(pB);
			pB->OnCollision(pA);

			// dynamic - static
			if (pA->GetCollisionType() == COLLISION_DYNAMIC && pB->GetCollisionType() == COLLISION_STATIC)
			{
				Push(pA, pB);
			}
			if (pA->GetCollisionType() == COLLISION_STATIC && pB->GetCollisionType() == COLLISION_DYNAMIC)
			{
				Push(pB, pA);
			}
			// dynamic - dynamic

			// dynamic - overlap
		}
	}
	m_registerNum = 0;
}


void RegisterCollision(GameObject *pA, GameObject *pB)
{
	if (m_registerNum < MAX_COLLISION_REGISTER)
	{
		m_pList[m_registerNum][0] = pA;
		m_pList[m_registerNum][1] = pB;
		++m_registerNum;
	}
}


bool CheckCollision(GameObject *pA, GameObject *pB)
{
	DirectX::XMFLOAT3 aPos = pA->GetPos();
	DirectX::XMFLOAT3 bPos = pB->GetPos();
	DirectX::XMFLOAT3 aSize = pA->GetSize();
	DirectX::XMFLOAT3 bSize = pB->GetSize();

	DirectX::XMFLOAT3 distance(
		fabsf(bPos.x - aPos.x),
		fabsf(bPos.y - aPos.y),
		fabsf(bPos.z - aPos.z)
	);

	bool hitX = distance.x < (aSize.x + bSize.x) * 0.5f;
	bool hitY = distance.y < (aSize.y + bSize.y) * 0.5f;
	bool hitZ = distance.z < (aSize.z + bSize.z) * 0.5f;

	return hitX && hitY && hitZ;
}


void Push(GameObject *pDynamic, GameObject *pStatic)
{
	//----- ���O�Ɋe�I�u�W�F�N�g�̏��𔲂��o�� -----
	DirectX::XMFLOAT3 dPos = pDynamic->GetPos();
	DirectX::XMFLOAT3 sPos = pStatic->GetPos();
	DirectX::XMFLOAT3 dSize = pDynamic->GetSize();
	DirectX::XMFLOAT3 sSize = pStatic->GetSize();
	DirectX::XMFLOAT3 dMove = pDynamic->GetMove();

	//----- �v�Z�ɕK�v�ȏ��𔲂��o�� -----
	// �ړ��ʂ���ړ�������������߂�
	// ���ړ����������1��-1�ŕ\��
	// �O�����Z�q A ? B : C
	// A�̏������������Ă�����B�A�������Ă��Ȃ�������C
	DirectX::XMFLOAT3 dir(
		(dMove.x > 0) ? 1.0f : -1.0f,
		(dMove.y > 0) ? 1.0f : -1.0f,
		(dMove.z > 0) ? 1.0f : -1.0f
	);
	// ���ۂɓ����蔻��ł߂荞�񂾂̂́A�I�u�W�F�N�g�̍��W�����ł͂Ȃ��A
	// �p�������߂荞��ł��邱�Ƃ�����̂ŁA�Ώۂ̊p���v�Z�ŋ��߂�
	DirectX::XMFLOAT3 dPoint(
		dPos.x + dir.x * dSize.x * 0.5f,
		dPos.y + dir.y * dSize.y * 0.5f,
		dPos.z + dir.z * dSize.z * 0.5f
	);
	// �ړ��O�̊p�̍��W
	// ���̂܂܂̈ړ��ʂňړ��O�̍��W��\�����Ƃ���ƕ��������_�̌v�Z�덷�ɂ��A
	// �ړ��x�N�g���̎��_���ʂ̓����ɂ��邱�ƂɂȂ�A�ђʂ��Ă��Ȃ��Ɣ��肳���
	// �����������邽�߂Ɉړ��O�̈ʒu�������Ȃ�悤�Ɍv�Z�̎������A�ړ��ʂ�傫������
	DirectX::XMFLOAT3 prePoint(
		dPoint.x - dMove.x * 1.1f,
		dPoint.y - dMove.y * 1.1f,
		dPoint.z - dMove.z * 1.1f
	);
	// �Փ˂��ꂽ���̊p���v�Z
	// �Փ˂��ꂽ���̊p�͈ړ������𔽓]���������Ɍ������đ傫���̔����𑫂��Ƌ��߂���
	DirectX::XMFLOAT3 sPoint(
		sPos.x - dir.x * sSize.x * 0.5f,
		sPos.y - dir.y * sSize.y * 0.5f,
		sPos.z - dir.z * sSize.z * 0.5f
	);
	// �ʏ�̈�_����ړ��x�N�g���̎n�_�ƏI�_�֌������x�N�g�����v�Z����
	DirectX::XMFLOAT3 vStart(
		prePoint.x - sPoint.x,
		prePoint.y - sPoint.y,
		prePoint.z - sPoint.z
	);
	DirectX::XMFLOAT3 vEnd(
		dPoint.x - sPoint.x,
		dPoint.y - sPoint.y,
		dPoint.z - sPoint.z
	);
	//----- ���ꂼ��̖ʂƌv�Z -----
	// �e�ʂ̖@���x�N�g��
	DirectX::XMFLOAT3 Normal[] =
	{
		DirectX::XMFLOAT3(-dir.x,0,0),
		DirectX::XMFLOAT3(0,-dir.y,0),
		DirectX::XMFLOAT3(0,0,-dir.z),
	};

	for (int i = 0; i < _countof(Normal); ++i)
	{
		// �ʂ̖@���Ƃ̓��ς��v�Z
		float dotS =
			vStart.x * Normal[i].x +
			vStart.y * Normal[i].y +
			vStart.z * Normal[i].z;
		float dotE =
			vEnd.x * Normal[i].x +
			vEnd.y * Normal[i].y +
			vEnd.z * Normal[i].z;
		// ���ꂼ��̓��ς̌��ʂ����ƕ��̒l�ł���Έړ��x�N�g�����ʂ��ђʂ��Ă���
		// ���ƕ��̑g�ݍ��킹���ǂ����͊|���Z�Ŕ���ł���(���~�s=��/���~��=��/���~��=��)
		if (dotS * dotE < 0)
		{
			if (pDynamic->isPlayer())
			{
				Player *pPlayer = dynamic_cast<Player*>(pDynamic);

				if (pStatic->isClimb() && (sPos.y + (sSize.y / 2) <= dPos.y + dSize.y) && (dPos.y < sPos.y + (sSize.y / 2) + (dSize.y / 2) - 0.1f))
				{
					dPos.y += fabsf(dMove.x);
					dMove.y = 0;
					pPlayer->SetGround(true);
				}

				if (Normal[i].y == 1.0f)
				{
					pPlayer->SetGround(true);
				}
			}


			// �ړ��x�N�g���̕����ɂ߂荞�񂾗ʂ�߂��̂ł͂Ȃ��A
			// �ʂ̕����Ɍ������Ė߂�(�߂������͓��ς̒l�Ɠ�����)
			dotE = fabsf(dotE);
			dPos.x += Normal[i].x * dotE;
			dPos.y += Normal[i].y * dotE;
			dPos.z += Normal[i].z * dotE;
			pDynamic->SetPos(dPos);
			// �S�Ă̈ړ��ʂ�0�ɂ��Ă��܂��ƁA���̃I�u�W�F�N�g�Ɖ����o���̌v�Z������ۂ�
			// �ړ��ʂ��Ȃ����ƂɂȂ�̂ŁA�ړ��ʂ�0�ɂ��Ȃ���΂Ȃ�Ȃ���������0�ɂ���B
			dMove.x *= 1 - fabsf(Normal[i].x);
			dMove.y *= 1 - fabsf(Normal[i].y);
			dMove.z *= 1 - fabsf(Normal[i].z);
			pDynamic->SetMove(dMove);
			break;
		}
	}
}
