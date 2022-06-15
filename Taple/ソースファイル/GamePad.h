//==========================================
//								   GamePad.h
//�@�Q�[���p�b�h�֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/11/18 ����J�n
//		11/19 �R���g���[���[�̃X�e�[�^�X����{�^���̓��͏����擾����̂Ɏg�p����}�X�N�̈ꗗ��萔��(GamePadButton)
//			  �{�^���̔���(Press,Trigger,Release)������
//		11/20 �g���K�[�̔���(Press,Trigger,Release)������
//			  �X�e�B�b�N�̔���(-1.0�`1.0�ŌX�����擾)������
//			  GamePadButton��enum class����class�ɕύX
//		11/26 �C���N���[�h����DirectXMath.h��ǉ�
//			  �X�e�B�b�N�̔����X,Y���ʂ̊֐��ɂȂ��Ă����̂���ɂ܂Ƃ߂�
//		11/27 ����̊֐������ׂăC�����C����
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include <Windows.h>
#include <DirectXMath.h>
#include <Xinput.h>

// xinput.lib�������N����
#pragma comment (lib, "xinput.lib")


//===== �萔�E�}�N����` =====
#define GAMEPAD_TRIGGER_THRESHOLD	(100)
#define GAMEPAD_STICK_MAX		(32767)


//===== �N���X��` =====
class GamePadButton	// ���͂��擾���邱�Ƃ̂ł���{�^���̈ꗗ
{
	// �C���X�^���X�����֎~
private:
	GamePadButton();

public:
	static const WORD NONE				= 0x0000;	// ���������Ă��Ȃ�
	static const WORD DPAD_UP			= 0x0001;	// �\���L�[��
	static const WORD DPAD_DOWN			= 0x0002;	// �\���L�[��
	static const WORD DPAD_LEFT			= 0x0004;	// �\���L�[��
	static const WORD DPAD_RIGHT		= 0x0008;	// �\���L�[�E
	static const WORD START				= 0x0010;	// �X�^�[�g�{�^��
	static const WORD BACK				= 0x0020;	// �o�b�N�{�^��
	static const WORD LEFT_THUMB		= 0x0040;	// ���X�e�B�b�N��������(L3)
	static const WORD RIGHT_THUMB		= 0x0080;	// �E�X�e�B�b�N��������(R3)
	static const WORD LEFT_SHOULDER		= 0x0100;	// LB(L1)
	static const WORD RIGHT_SHOULDER	= 0x0200;	// RB(R1)
	static const WORD A					= 0x1000;	// A(�~)
	static const WORD B					= 0x2000;	// B(�Z)
	static const WORD X					= 0x4000;	// X(��)
	static const WORD Y					= 0x8000;	// Y(��)
};


class GamePad	// �Q�[���p�b�h�̓��͂��Ƃ�N���X
{
// �C���X�^���X�����֎~
private:
	GamePad();

public:
	//===== �����o�֐� =====
	//----- �l�又�� -----

	//--------------------------------------
	//�֐����FInit
	//���@���F�Ȃ�
	//�߂�l�FHRESULT �R���g���[���[���q�����Ă��邩�ǂ���
	//���@�e�F����������
	//--------------------------------------
	static HRESULT Init(void);
	//--------------------------------------
	//�֐����FUninit
	//���@���F�Ȃ�
	//�߂�l�F�Ȃ�
	//���@�e�F�I������
	//--------------------------------------
	static void Uninit(void);
	//--------------------------------------
	//�֐����FUpdate
	//���@���F�Ȃ�
	//�߂�l�F�Ȃ�
	//���@�e�F�X�V����
	//--------------------------------------
	static void Update(void);


	//----- �{�^�� -----

	//--------------------------------------
	//�֐����FIsButtonPress
	//���@���Fconst WORD button ������Ƃ�{�^��
	//�߂�l�Fbool ������Ă��邩
	//���@�e�F�{�^����������Ă��邩
	//--------------------------------------
	static bool IsButtonPress(const WORD button) { return button == GamePadButton::NONE ? m_state.Gamepad.wButtons == 0 : m_state.Gamepad.wButtons & button; }
	//--------------------------------------
	//�֐����FIsButtonTrigger
	//���@���Fconst WORD button ������Ƃ�{�^��
	//�߂�l�Fbool �����ꂽ��
	//���@�e�F�{�^���������ꂽ��
	//--------------------------------------
	static bool IsButtonTrigger(const WORD button) { return (m_state.Gamepad.wButtons ^ m_oldState.Gamepad.wButtons) & m_state.Gamepad.wButtons & button; }
	//--------------------------------------
	//�֐����FIsButtonRelease
	//���@���Fconst WORD button ������Ƃ�{�^��
	//�߂�l�Fbool �����ꂽ��
	//���@�e�F�{�^���������ꂽ��
	//--------------------------------------
	static bool IsButtonRelease(const WORD button) { return (m_oldState.Gamepad.wButtons ^ m_state.Gamepad.wButtons) & m_oldState.Gamepad.wButtons & button; }
//	static const bool IsButtonRepeat(WORD);	������


	//----- �g���K�[ -----

	//--------------------------------------
	//�֐����FGetRightTrigger
	//���@���F�Ȃ�
	//�߂�l�FBYTE �ǂꂾ���������܂�Ă��邩(0�`255)
	//���@�e�F�E�̃g���K�[���ǂꂾ��������Ă��邩
	//--------------------------------------
	static BYTE GetRightTrigger(void) { return m_state.Gamepad.bRightTrigger; }
	//--------------------------------------
	//�֐����FIsRightTriggerPress
	//���@���F�Ȃ�
	//�߂�l�Fbool ������Ă��邩
	//���@�e�F�E�g���K�[��������Ă��邩
	//--------------------------------------
	static bool IsRightTriggerPress(void) { return m_state.Gamepad.bRightTrigger > GAMEPAD_TRIGGER_THRESHOLD; }
	//--------------------------------------
	//�֐����FIsRightTriggerTrigger
	//���@���F�Ȃ�
	//�߂�l�Fbool �����ꂽ��
	//���@�e�F�E�g���K�[�������ꂽ��
	//--------------------------------------
	static bool IsRightTriggerTrigger(void) { return (m_state.Gamepad.bRightTrigger > GAMEPAD_TRIGGER_THRESHOLD) && (m_oldState.Gamepad.bRightTrigger <= GAMEPAD_TRIGGER_THRESHOLD); }
	//--------------------------------------
	//�֐����FIsRightTriggerRelease
	//���@���F�Ȃ�
	//�߂�l�Fbool �����ꂽ��
	//���@�e�F�E�g���K�[�������ꂽ��
	//--------------------------------------
	static bool IsRightTriggerRelease(void) { return (m_state.Gamepad.bRightTrigger <= GAMEPAD_TRIGGER_THRESHOLD) && (m_oldState.Gamepad.bRightTrigger > GAMEPAD_TRIGGER_THRESHOLD); }
//	static bool IsRightTriggerRepeat(void);	������

	//--------------------------------------
	//�֐����FGetLeftTrigger
	//���@���F�Ȃ�
	//�߂�l�FBYTE �ǂꂾ���������܂�Ă��邩(0�`255)
	//���@�e�F���̃g���K�[���ǂꂾ��������Ă��邩
	//--------------------------------------
	static BYTE GetLeftTrigger(void) { return m_state.Gamepad.bLeftTrigger; }
	//--------------------------------------
	//�֐����FIsLeftTriggerPress
	//���@���F�Ȃ�
	//�߂�l�Fbool ������Ă��邩
	//���@�e�F���g���K�[��������Ă��邩
	//--------------------------------------
	static bool IsLeftTriggerPress(void) { return m_state.Gamepad.bLeftTrigger > GAMEPAD_TRIGGER_THRESHOLD; }
	//--------------------------------------
	//�֐����FIsLeftTriggerTrigger
	//���@���F�Ȃ�
	//�߂�l�Fbool �����ꂽ��
	//���@�e�F���g���K�[�������ꂽ��
	//--------------------------------------
	static bool IsLeftTriggerTrigger(void) { return (m_state.Gamepad.bLeftTrigger > GAMEPAD_TRIGGER_THRESHOLD) && (m_oldState.Gamepad.bLeftTrigger <= GAMEPAD_TRIGGER_THRESHOLD); }
	//--------------------------------------
	//�֐����FIsLeftTriggerRelease
	//���@���F�Ȃ�
	//�߂�l�Fbool �����ꂽ��
	//���@�e�F���g���K�[�������ꂽ��
	//--------------------------------------
	static bool IsLeftTriggerRelease(void) { return (m_state.Gamepad.bLeftTrigger <= GAMEPAD_TRIGGER_THRESHOLD) && (m_oldState.Gamepad.bLeftTrigger > GAMEPAD_TRIGGER_THRESHOLD); }
//	static const bool IsLeftTriggerRepeat(void);	������


	//----- �X�e�B�b�N -----

	//--------------------------------------
	//�֐����FGetRightStick
	//���@���F�Ȃ�
	//�߂�l�FDirectX::XMFLOAT2 �X��(x���Ay�� (-1.0�`1.0))
	//���@�e�F�E�X�e�B�b�N�̌X�����擾
	//--------------------------------------
	static DirectX::XMFLOAT2 GetRightStick(void) { return DirectX::XMFLOAT2(static_cast<float>(m_state.Gamepad.sThumbRX) / GAMEPAD_STICK_MAX, static_cast<float>(m_state.Gamepad.sThumbRY) / GAMEPAD_STICK_MAX); }
	//--------------------------------------
	//�֐����FGetLeftStick
	//���@���F�Ȃ�
	//�߂�l�FDirectX::XMFLOAT2 �X��(x���Ay�� (-1.0�`1.0))
	//���@�e�F���X�e�B�b�N�̌X�����擾
	//--------------------------------------
	static DirectX::XMFLOAT2 GetLeftStick(void) { return DirectX::XMFLOAT2(static_cast<float>(m_state.Gamepad.sThumbLX) / GAMEPAD_STICK_MAX, static_cast<float>(m_state.Gamepad.sThumbLY) / GAMEPAD_STICK_MAX); }

private:
	//===== �����o�ϐ� =====
	static XINPUT_STATE m_state;	// �Q�[���p�b�h�̏��
	static XINPUT_STATE m_oldState;	// �O��̃Q�[���p�b�h�̏��
};
