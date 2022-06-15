//==========================================
//								 GamePad.cpp
//�@�Q�[���p�b�h�֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/11/18 ����J�n
//		11/19 �{�^���̔���(Press,Trigger,Release)������
//		11/20 �g���K�[�̂������l��萔��(GAMEPAD_TRIGGER_THRESHOLD)
//			  �g���K�[�̔���(Press,Trigger,Release)������
//			  �X�e�B�b�N�̌X���̍ő�l��萔��(GAMEPAD_STICK_TILT_MAX)
//			  �X�e�B�b�N�̔���(-1.0�`1.0�ŌX�����擾)������
//		11/26 �C���N���[�h����DirectXMath.h��ǉ�
//			  �X�e�B�b�N�̔����X,Y���ʂ̊֐��ɂȂ��Ă����̂���ɂ܂Ƃ߂�
//		11/27 ����̊֐������ׂăC�����C����
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �x���}�~
#pragma warning(disable : 4995)


//====== �C���N���[�h�� =====
#include "GamePad.h"

// �ÓI�����o�ϐ��̒�`
XINPUT_STATE GamePad::m_state = {};
XINPUT_STATE GamePad::m_oldState = {};



//--------------------------------------
//�֐����FInit
//���@���F�Ȃ�
//�߂�l�FHRESULT �R���g���[���[���q�����Ă��邩�ǂ���
//���@�e�F����������
//--------------------------------------
HRESULT GamePad::Init(void)
{
	//===== �ϐ��錾 =====
	DWORD dwResult;	// ���s����

	// �R���g���[���[���q�����Ă��邩�ǂ����m�F
	dwResult = XInputGetState(0, &m_state);
	// XInput��L����(�Ăяo���K�v�Ȃ�)
	XInputEnable(true);
	
	if (dwResult == ERROR_SUCCESS)
	{
		return S_OK;
	}
	else
	{
		return S_FALSE;
	}
}


//--------------------------------------
//�֐����FUninit
//���@���F�Ȃ�
//�߂�l�F�Ȃ�
//���@�e�F�I������
//--------------------------------------
void GamePad::Uninit(void)
{
	// XInput������(�o�C�u���[�V�����Ȃǂ𒆒f)
	XInputEnable(false);
}


//--------------------------------------
//�֐����FUpdate
//���@���F�Ȃ�
//�߂�l�F�Ȃ�
//���@�e�F�X�V����
//--------------------------------------
void GamePad::Update(void)
{
	// �O��̓��͏���ޔ�
	m_oldState = m_state;
	// �R���g���[���[�̏�Ԃ��擾
	XInputGetState(0, &m_state);

	// �X�e�B�b�N�̌X���̃}�C�i�X�����ƃv���X�����̍���␳����
	if (m_state.Gamepad.sThumbRX < -GAMEPAD_STICK_MAX)
	{
		m_state.Gamepad.sThumbRX = -GAMEPAD_STICK_MAX;
	}
	if (m_state.Gamepad.sThumbLX < -GAMEPAD_STICK_MAX)
	{
		m_state.Gamepad.sThumbLX = -GAMEPAD_STICK_MAX;
	}
	// �X�e�B�b�N�̌X�����f�b�h�]�[�������Ȃ�0�ɂ���(�X�e�B�b�N�ɗV�т���������)
	if ((m_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(m_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		m_state.Gamepad.sThumbLX = 0;
		m_state.Gamepad.sThumbLY = 0;
	}
	if ((m_state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && m_state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(m_state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE && m_state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		m_state.Gamepad.sThumbRX = 0;
		m_state.Gamepad.sThumbRY = 0;
	}
}
