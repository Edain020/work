//====== �C���N���[�h�� =====
#include "Tape.h"
#include "Defines.h"
#include "Texture.h"
#include "Player.h"


ID3D11ShaderResourceView* Tape::m_pTexture = {};


Tape::Tape()
	: m_pParent(nullptr)
	, m_pTarget(nullptr)
	, m_bottomPos(0.0f, 0.0f, 0.0f)
	, m_topPos(0.0f, 0.0f, 0.0f)
	, m_fAngle(0.0f)
	, m_fSpeed(0.0f)
	, m_isExtend(false)
	, m_isDraw(false)
{
}


Tape::~Tape()
{
	Uninit();
}


bool Tape::Init()
{
	m_pCube = new Cube();
	m_size = DirectX::XMFLOAT3(0.0f, 0.1f, 0.2f);
	if (m_pTexture == nullptr)
	{
		LoadTextureFromFile(ASSET("Model/Player/orange.jpg"), &m_pTexture);
	}
	return true;
}


void Tape::Uninit()
{
	SAFE_DELETE(m_pCube);
	SAFE_RELEASE(m_pTexture);
}


void Tape::Update()
{
	// �L�т��ԂȂ���s
	if (m_isExtend && m_isDraw)
	{
		// �e�[�v�̐悩��^�[�Q�b�g�ւ̕������v�Z
		DirectX::XMFLOAT3 targetPos(m_pTarget->GetPos());
		if (Gimmick* gimmick = dynamic_cast<Gimmick*>(m_pTarget))
		{
			targetPos.x += gimmick->GetTargetPos().x;
			targetPos.y += gimmick->GetTargetPos().y;
			targetPos.z += gimmick->GetTargetPos().z;
		}
		float targetAngle;
		targetAngle = atan2f(targetPos.y - m_topPos.y, targetPos.x - m_topPos.x);
	
		// �e�[�v�̐���^�[�Q�b�g�Ɍ����ĐL�΂�
		m_topPos.x += cosf(targetAngle) * m_fSpeed;
		m_topPos.y += sinf(targetAngle) * m_fSpeed;
		
		// �e�[�v�̐悪�^�[�Q�b�g�Ɉ��ȏ�ߕt���Ă�����^�[�Q�b�g������
		if ((targetPos.y - m_topPos.y) * (targetPos.y - m_topPos.y) + (targetPos.x - m_topPos.x) * (targetPos.x - m_topPos.x) < (m_fSpeed * m_fSpeed))
		{
			if (m_pTarget == this || m_pTarget == m_pParent->GetTarget())
			{
				m_topPos = targetPos;
				m_isExtend = false;
				m_pParent->SetGrab(true);
			}
			else
			{
				m_pParent->SetRoll(true);
			}
		}
	}
	else if (m_isDraw)
	{
		m_topPos = m_pTarget->GetPos();
		if (Gimmick* gimmick = dynamic_cast<Gimmick*>(m_pTarget))
		{
			m_topPos.x += gimmick->GetTargetPos().x;
			m_topPos.y += gimmick->GetTargetPos().y;
			m_topPos.z += gimmick->GetTargetPos().z;
		}
	}
	else
	{
		m_topPos = m_bottomPos;
	}

	// ���S���W���e�[�v�̌��ƃe�[�v�̐�̒��Ԃɐݒ肷��
	m_pos.x = m_bottomPos.x + ((m_topPos.x - m_bottomPos.x) / 2.0f);
	m_pos.y = m_bottomPos.y + ((m_topPos.y - m_bottomPos.y) / 2.0f);

	// �����̐ݒ�
	m_size.x = sqrtf((m_topPos.x - m_bottomPos.x) * (m_topPos.x - m_bottomPos.x) + (m_topPos.y - m_bottomPos.y) * (m_topPos.y - m_bottomPos.y));
	
	// �p�x�̌v�Z�A�ݒ�
	m_fAngle = RAD_TO_DEG(atan2f(m_topPos.y - m_bottomPos.y, m_topPos.x - m_bottomPos.x));
	m_rot.z = DEG_TO_RAD(m_fAngle);

	// ��~���Ƀe�[�v�̒��������ȉ��Ȃ��\��
	if (!m_isExtend && m_isDraw && m_size.x <= 1.0f)
	{
		m_isDraw = false;
		m_pParent->SetGrab(false);
		m_pParent->SetExtendTape(false);
		m_pParent->SetRoll(false);
	}
}


void Tape::Draw()
{
	// ��\���ݒ�Ȃ�`�悵�Ȃ�
	if (!m_isDraw)
	{
		return;
	}

	SHADER->SetWorld(
		DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z)
		* DirectX::XMMatrixRotationRollPitchYaw(m_rot.x, m_rot.y, m_rot.z)
		* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	);
	SHADER->SetTexture(m_pTexture);
	m_pCube->Draw();
	SHADER->SetTexture(NULL);
}


void Tape::SetBottomPos(DirectX::XMFLOAT3 pos)
{
	// �ړ�����ʂƓ��������e�[�v�̐���ړ�������
	m_topPos.x += pos.x - m_bottomPos.x;
	m_topPos.y += pos.y - m_bottomPos.y;

	m_bottomPos = pos;
}
