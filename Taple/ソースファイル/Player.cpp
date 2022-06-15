//==========================================
//								  Player.cpp
//	�v���C���[�֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/10/30 ����J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

//===== �C���N���[�h�� =====
#include "Player.h"
#include <math.h>
#include "Defines.h"
#include "Tape.h"
#include "Texture.h"
#include "GimmickManager.h"
#include "CameraManager.h"
#include "GamePad.h"
#include "Input.h"


//===== �萔�E�}�N����` =====
#define PLAYER_SCALE	(1.0f/16)
#define PLAYER_POS_X	(0.0f)	// �����ʒu(X)
#define PLAYER_POS_Y	(5.0f)	// �����ʒu(Y)


ID3D11ShaderResourceView *g_pTex;


// �R���X�g���N�^
Player::Player()
	: m_fRotSpeed(0)
	, m_fDir(1.0f)
	, m_fYaw(0.0f)
	, m_fTargetSizeCnt(0.0f)
	, m_isGround(false)
	, m_isGrab(false)
	, m_isExtendTape(false)
	, m_isRoll(false)
	, m_canRoll(true)
	, m_pBodyModel(nullptr)
	, m_pEyeModel(nullptr)
	, m_pMouthModel(nullptr)
	, m_pTape(nullptr)
	, m_pTapeSE(nullptr)
	, m_targetRange(10.0f, 10.5f, 4)
{
	m_pos = { PLAYER_POS_X, PLAYER_POS_Y, 0 };
}



// �f�R���X�g���N�^
Player::~Player()
{
	Uninit();
}


bool Player::Init(void)
{
	// �e�[�v�̐���
	m_pTape = new Tape();
	m_pTape->SetParent(this);
	m_pTape->Init();
	m_pTape->SetSpeed(2.0f / 2);

	m_pCube = new Cube();

	// ���f���̐���
	m_pBodyModel = new Model();
	m_pBodyModel->LoadModel(ASSET("Model/Player/tepukunn_karada_gf.fbx"));
	m_pEyeModel = new Model();
	m_pEyeModel->LoadModel(ASSET("Model/Player/tepukunn_me.fbx"));
	m_pMouthModel = new Model();
	m_pMouthModel->LoadModel(ASSET("Model/Player/tepukunn_kuti.fbx"));

	LoadTextureFromFile(ASSET("target.png"), &g_pTex);

	m_pTapeSE = new Sound();
	m_pTapeSE->Load(ASSET("Sound/SE/Tape.mp3"));

	return true;
}


void Player::Uninit(void)
{
	SAFE_DELETE(m_pBodyModel);
	SAFE_DELETE(m_pEyeModel);
	SAFE_DELETE(m_pMouthModel);
	SAFE_DELETE(m_pCube);
	SAFE_DELETE(m_pTape);
	SAFE_DELETE(m_pTapeSE);
	m_pTarget = nullptr;
	m_pTargetList.clear();
	SAFE_RELEASE(g_pTex);
}


void Player::Update()
{
	Move();	// �ړ�
	ControlTape();	// �e�[�v�֌W


	// ���X�ɕ����]��
	if (m_rot.y != m_fYaw)
	{
		float roll;
		roll = m_fYaw - m_rot.y;
		roll *= 0.2f;
		m_rot.y += roll;
	}

	// �^�[�Q�b�g�̖ڈ���g�k
	if (m_pTarget)
	{
		m_fTargetSizeCnt += 2.0f;
		if (m_fTargetSizeCnt >= 360.0f)
		{
			m_fTargetSizeCnt -= 360.0f;
		}
	}
	else
	{
		m_fTargetSizeCnt = 0.0f;
	}

	// �J�����̈ړ�
	CameraMgr::SetLook(m_pos);

	if (m_rot.z >= 360.0f)
	{
		m_rot.z -= 360.0f;
	}
	else if (m_rot.z < 0.0f)
	{
		m_rot.z += 360.0f;
	}
}


void Player::Draw(void)
{
	SHADER->SetWorld(
		DirectX::XMMatrixScaling(1.2f, 1.2f, 1.2f)
		* DirectX::XMMatrixRotationRollPitchYaw(m_rot.x, DEG_TO_RAD(m_rot.y), DEG_TO_RAD(m_rot.z))
		* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	);
	m_pBodyModel->Draw();

	SHADER->SetWorld(
		DirectX::XMMatrixScaling(PLAYER_SCALE, PLAYER_SCALE, PLAYER_SCALE)
		* DirectX::XMMatrixRotationRollPitchYaw(0.0f,DEG_TO_RAD(m_rot.y), 0.0f)
		* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	);
	m_pEyeModel->Draw();
	m_pMouthModel->Draw();

	SHADER->SetTexture(NULL);

	if (m_pTape)
	{
		m_pTape->Draw();
	}

	// �^�[�Q�b�g�̖ڈ�
	if (m_pTarget)
	{
		SHADER->SetWorld(
			DirectX::XMMatrixScaling(
				0.9f + sinf(DEG_TO_RAD(m_fTargetSizeCnt)) * 0.2f,
				0.9f + sinf(DEG_TO_RAD(m_fTargetSizeCnt)) * 0.2f,
				0.9f + sinf(DEG_TO_RAD(m_fTargetSizeCnt)) * 0.2f)
			* DirectX::XMMatrixTranslation(
				m_pTarget->GetPos().x + m_pTarget->GetTargetPos().x,
				m_pTarget->GetPos().y + m_pTarget->GetTargetPos().y,
				m_pTarget->GetPos().z + m_pTarget->GetTargetPos().z)
		);
		SHADER->SetTexture(g_pTex);
		m_pCube->Draw();
		SHADER->SetTexture(NULL);
	}
}


void Player::ReSpawn(void)
{
	m_pos = { PLAYER_POS_X, PLAYER_POS_Y, 0 };
	m_move = { 0.0f, 0.0f, 0.0f };
	m_fRoll = 0.0f;

	m_pTape->SetTarget(m_pTape);
	m_pTape->SetExtend(true);
	m_isGrab = false;
	m_canRoll = true;
	m_pTarget = nullptr;
}


void Player::Roll(float rollSpeed)
{
	m_rot.z += rollSpeed;
}


void Player::Move(void)
{
	if (m_isGrab)
	{
		if (!m_pTarget)
		{
			m_isGrab = false;
			m_isRoll = true;
		}
		else
		{
			m_pTarget->UpdatePlayer(this);
		}
		return;
	}

	// 1�b�Ԃ�10�i��
	const float Move = 10.0f / 60;

	// �ڒn���Ă���Ȃ�ړ��ʂ�����
	if (m_isGround)
	{
		m_move = DirectX::XMFLOAT3(m_move.x * 0.4f, m_move.y, m_move.z);
	}
	else
	{
		m_move = DirectX::XMFLOAT3(m_move.x * 0.98f, m_move.y, m_move.z);
	}

	// �ړ�
	if (m_isGround)
	{// �n��
		m_move.x += GamePad::GetLeftStick().x * Move;
		if (IsKeyPress('A'))
		{
			m_move.x -= Move;
		}
		if (IsKeyPress('D'))
		{
			m_move.x += Move;
		}
	}
	else
	{// ��
		m_move.x += GamePad::GetLeftStick().x * Move / 50;
		if (IsKeyPress('A'))
		{
			m_move.x -= Move / 50;
		}
		if (IsKeyPress('D'))
		{
			m_move.x += Move / 50;
		}
	}

	// �d��
	m_move.y -= GRAVITY;

	// ��]���X�V
	m_fRotSpeed = -((fabsf(m_move.x) / (1.0f * PI)) * 180.0f);

	if (0.0f < m_move.x)
	{
		m_fDir = 1.0f;
		m_fYaw = 0.0f;
	}
	else if(m_move.x < 0.0f)
	{
		m_fDir = -1.0f;
		m_fYaw = 180.0f;
	}

	// �ړ��𔽉f
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	// ��]�𔽉f
	m_rot.x = 0.0f;
	m_rot.z += m_fRotSpeed;


	// ��������
	if (m_pos.y <= -10)
	{
		ReSpawn();
	}

	// �ڒn����̃��Z�b�g(�����蔻�菈���Ŕ��肪�Ƃ���)
	m_isGround = false;
}

void Player::ControlTape(void)
{
	std::vector<Gimmick*> *gimmicks = GIMMICKS->GetGimickList();
	m_pTargetList.clear();

	if (!m_isGrab && !m_isRoll)
	{
		for (Gimmick *gimmick : *gimmicks)
		{
			// �^�[�Q�b�g�Ώۂ���Ȃ���Ώ������Ȃ�
			if (!gimmick->isTarget())
			{
				continue;
			}

			DirectX::XMFLOAT3 pos(gimmick->GetPos());
			DirectX::XMFLOAT3 targetPos(gimmick->GetTargetPos());

			targetPos.x += pos.x;
			targetPos.y += pos.y;
			targetPos.z += pos.z;

			DirectX::XMFLOAT3 center;
			center.x = m_pos.x + m_fDir * m_targetRange.x / 2.0f;
			center.y = m_pos.y + m_targetRange.y / 3.0f;
			center.z = m_pos.z + m_targetRange.z / 2.0f;

			if (center.x - m_targetRange.x / 2.0f < targetPos.x && targetPos.x < center.x + m_targetRange.x / 2.0f &&
				center.y - m_targetRange.y / 2.0f < targetPos.y && targetPos.y < center.y + m_targetRange.y / 2.0f)
			{
				m_pTargetList.push_back(gimmick);
			}
		}

		if (m_pTargetList.empty())
		{
			m_pTarget = nullptr;
		}
		else
		{

			for (Gimmick *gimmick : m_pTargetList)
			{
				if (gimmick == m_pTarget)
				{
					break;
				}

				if (gimmick == *(--m_pTargetList.end()))
				{
					m_pTarget = *m_pTargetList.begin();
				}
			}

			//----- �^�[�Q�b�g�؂�ւ� -----
			if (GamePad::IsButtonTrigger(GamePadButton::LEFT_SHOULDER) || IsKeyTrigger(VK_SHIFT))
			{
				if (m_pTarget != nullptr)
				{
					if (m_pTarget == *(--m_pTargetList.end()))
					{
						m_pTarget = *m_pTargetList.begin();
					}
					else
					{
						std::list<Gimmick*>::iterator itr;
						for (itr = m_pTargetList.begin(); itr != m_pTargetList.end(); ++itr)
						{
							if (m_pTarget != *itr)	continue;

							++itr;
							m_pTarget = *itr;
							break;
						}
					}
				}
				else
				{
					m_pTarget = *m_pTargetList.begin();
				}
			}

			//----- �e�[�v�ˏo -----
			if (GamePad::IsButtonTrigger(GamePadButton::A) || IsKeyTrigger('J') && !m_isExtendTape)
			{
				m_pTape->SetTarget(m_pTarget);
				m_pTape->SetExtend(true);
				m_pTape->SetDraw(true);
				m_isExtendTape = true;
				m_pTapeSE->Play();
			}
		}
	}

	//----- �e�[�v�����(�؂藣��) -----
	if (!m_isRoll && m_isGrab && m_canRoll &&
		(GamePad::IsButtonTrigger(GamePadButton::B) || IsKeyTrigger(('K')) && m_isExtendTape))
	{
		m_pTape->SetTarget(m_pTape);
		m_pTape->SetExtend(true);
		m_isRoll = true;
	}
	// ����蒆
	if (m_isRoll)
	{
		m_pTape->SetTarget(m_pTape);
	}

	// �e�[�v���v���C���[�ɒǏ]������
	m_pTape->SetBottomPos(DirectX::XMFLOAT3(m_pos.x, m_pos.y + 0.5f, m_pos.z));
	// �e�[�v�̍X�V
	m_pTape->Update();
}
