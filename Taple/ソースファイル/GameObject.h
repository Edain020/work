//==========================================
//								GameObject.h
//�@�Q�[���I�u�W�F�N�g�֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/10/28 ����J�n
//		12/12 �Փˎ��̏������s���֐�OnCollision��ǉ�
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include <DirectXMath.h>
#include "Cube.h"
#include "Shader.h"


// �����蔻������{����Ƃ��̃I�u�W�F�N�g�̎��
enum ObjectCollisionType
{
	COLLISION_STATIC,	// �Î~���Ă��镨��
	COLLISION_DYNAMIC,	// �����Ă��镨��
	COLLISION_OVERLAP	// �ђʂ��镨��
};


//===== �N���X��` =====
class GameObject
{
public:
	//===== �����o�֐� =====
	GameObject();
	virtual ~GameObject();

	//----- �l�又�� -----
	virtual bool Init();
	virtual void Uninit();
	virtual void Update() {}
	virtual void Draw();

	//----- �����蔻�� -----
	virtual void OnCollision(GameObject *other) {}

	//----- �Q�b�^�[ -----
	DirectX::XMFLOAT3 GetPos() { return m_pos; }
	DirectX::XMFLOAT3 GetSize() { return m_size; }
	DirectX::XMFLOAT3 GetMove() { return m_move; }
	ObjectCollisionType GetCollisionType() { return m_collisionType; }

	//----- �Z�b�^�[ -----
	void SetPos(const DirectX::XMFLOAT3 pos)	{ m_pos = pos; }
	void SetSize(const DirectX::XMFLOAT3 size)	{ m_size = size; }
	void SetMove(DirectX::XMFLOAT3 move)		{ m_move = move; }


	virtual bool isPlayer(void) { return false; }
	virtual bool isClimb(void) { return false; }

private:

protected:
	//===== �����o�ϐ� =====
	DirectX::XMFLOAT3 m_pos;	// ���W
	DirectX::XMFLOAT3 m_size;	// �傫��
	DirectX::XMFLOAT3 m_move;	// �ړ���
	DirectX::XMFLOAT3 m_rot;	// ��]��

	ObjectCollisionType m_collisionType;// �����蔻��̎��

	//===== �����o�I�u�W�F�N�g =====
	Cube *m_pCube;	// �ȈՃ��f��
};
