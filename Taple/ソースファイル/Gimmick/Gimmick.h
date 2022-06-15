//==========================================
//								   Gimmick.h
//	�M�~�b�N�֘A
//�@�����:AT12D171 No.12 ���䋪��
//		   AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/11/** ����J�n
//		11/30 �݌v��ύX
//		12/11 �M�~�b�N�^�C�v�̎�ނ�ύX
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once

//===== �C���N���[�h�� =====
#include "../GameObject.h"
#include "../Model.h"


// �O���錾
class Player;

//===== �񋓌^�錾 =====
enum GimmickType	// �M�~�b�N�̎��
{
	GIMMICK_NONE,
	GIMMICK_DEFAULT,

	GIMMICK_DESK,
	GIMMICK_BOOK,
	GIMMICK_RULER,
	GIMMICK_CLOSET,
	
	GIMMICK_SHELF_BLOCK,
	GIMMICK_BOOKS_BLOCK,
	
	GIMMICK_ERASER,
	GIMMICK_LIFT_BOOK,
	GIMMICK_PENDULUM,
	
	GIMMICK_CREPAS,
	GIMMICK_PIN,
	
	GIMMICK_CLOCK,

	GIMMICK_THORN,
	GIMMICK_FALL_BOOK,
	GIMMICK_NAIL,

	GIMMICK_BOX,

	//  �L�b�`�����[��
	GIMMICK_KNIFE,              // �i�C�t
	GIMMICK_HOOK,               // �t�b�N
	GIMMICK_CUPBOARD,           // �H��I
	GIMMICK_BIGCUPBOARD,        // �傫���H��I
	GIMMICK_KITCHENSHELVES,     // �L�b�`���I
	GIMMICK_GOALKITCHENSHELVES, // �S�[���L�b�`���I
	GIMMICK_STAND,              // ��
	GIMMICK_STOVE,              // �R����
	GIMMICK_LADLE,              // ����
	GIMMICK_CONTAINER,          // �e��
	GIMMICK_LID,                // �W
	GIMMICK_CUTTINGBOARD,       // �܂Ȕ�
	GIMMICK_DISH,               // �M
	GIMMICK_WASHINGCUPBOARD,    // �􂢕��H��I
	GIMMICK_OVEN,               // �I�[�u��
	GIMMICK_MICROWAVE,          // �d�q�����W
	GIMMICK_FAUCET,             // �֌�
	GIMMICK_RICECOOKER,         // ���ъ�
	GIMMICK_SEASNING,           // ������
	GIMMICK_STOVEFIRE,          // �R����
	GIMMICK_WLSHELF,            // ��L���I
	GIMMICK_HLSHELF,
};


//===== �N���X��` =====
class Gimmick : public GameObject // �M�~�b�N�N���X
{
public:
	//===== �R���X�g���N�^�E�f�X�g���N�^=====

	// �f�t�H���g�R���X�g���N�^
	Gimmick(void);
	// �f�X�g���N�^
	virtual ~Gimmick(void);

	//===== �l�又�� =====
	virtual void Uninit(void);

	// �v���C���[����Ăяo���X�V����
	virtual void UpdatePlayer(Player *player) {}
	// �͂񂾎��ɌĂяo���֐�
	virtual void Grab(Player *player) {}
	// �����蔻�肪��������ꍇ�ɓ����蔻���ݒ肷��֐�
	virtual void SetCollision(GameObject *object) {}


	//===== �Q�b�^�[ =====
	DirectX::XMFLOAT3 GetTargetPos(void) { return m_targetPos; }
	int GetGimmickType(void) { return m_gimmickType; }
	bool isTarget(void) { return m_isTarget; }
	bool isSingle(void) { return m_isSingle; }
	
	//==== �Z�b�^�[ ====
	DirectX::XMFLOAT3 SetTargetPos(const DirectX::XMFLOAT3 pos) { m_targetPos = pos; }

protected:
	//===== �����o�ϐ� =====
	DirectX::XMFLOAT3 m_targetPos;	// �^�[�Q�b�g����ʒu
	GimmickType m_gimmickType;	// �M�~�b�N�̎��
	bool m_isTarget;			// �^�[�Q�b�g�ł��邩�ǂ���
	bool m_isSingle;			// �P�̂��ǂ���
};
