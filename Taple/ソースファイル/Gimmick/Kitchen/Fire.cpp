//==========================================
//							StoveFire.cpp
//	UI(��)�֘A
//�@�����:AT12D171 No.29 ���{�a��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// //�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

//===== �C���N���[�h�� =====
#include "Fire.h"
#include "../../Defines.h"
#include "../../Texture.h"
#include "../../Shader.h"
#include "../../CameraManager.h"
#include "../../Player.h"
#include <random>


//===== �萔�E�}�N����` =====
#define FIRE_TEX_SPLIT_U	(4)	// �������̃e�N�X�`��������
#define FIRE_TEX_SPLIT_V	(4)	// �c�����̃e�N�X�`��������


//----- �ÓI�����o�ϐ��̒�` -----
ID3D11ShaderResourceView* Fire::m_pTex = {};	// �΂̃e�N�X�`��



Fire::Fire()
	: m_nTexCnt(0)
	, m_nTexNum(0)
	, m_pVtx(nullptr)
{
}


Fire::~Fire()
{
	Uninit();
}


bool Fire::Init(void)
{
	m_pVtx = new Vertex[4];

	int i;	// ���[�v�p
	for (i = 0; i < 4; ++i)
	{
		m_pVtx[i].color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	float halfSize = 0.5f;
	m_pVtx[0].pos = DirectX::XMFLOAT3(-halfSize,  halfSize, 0.0f);	// 0.����
	m_pVtx[1].pos = DirectX::XMFLOAT3( halfSize,  halfSize, 0.0f);	// 1.�E��
	m_pVtx[2].pos = DirectX::XMFLOAT3(-halfSize, -halfSize, 0.0f);	// 2.����
	m_pVtx[3].pos = DirectX::XMFLOAT3( halfSize, -halfSize, 0.0f);	// 3.�E��

	std::random_device rand;	// ����������
	m_nTexNum = rand() % 16;
	UpdateUV();

	// �C���f�b�N�X�f�[�^
	long idx[] =
	{
		0,1,2, 1,3,2,// ��O
	};

	// �o�b�t�@�쐬
	m_buffer.CreateVertexBuffer(m_pVtx, sizeof(Vertex), 4, true);
	m_buffer.CreateIndexBuffer(idx, sizeof(idx) / sizeof(long));

	// �܂��e�N�X�`�����ǂݍ��܂�Ă��Ȃ�������e�N�X�`����ǂݍ���
	if (!m_pTex)
	{
		LoadTextureFromFile(ASSET("Billboard/Fire.png"), &m_pTex);
	}

	return true;
}


void Fire::Uninit(void)
{
	SAFE_RELEASE(m_pTex);
	SAFE_DELETE_ARRAY(m_pVtx);
}


void Fire::Update(void)
{
	m_nTexCnt++;
	if (m_nTexCnt >= 5)
	{
		std::random_device rand;
		m_nTexNum = (m_nTexNum + 1) % (FIRE_TEX_SPLIT_U * FIRE_TEX_SPLIT_V);
		UpdateUV();
		m_nTexCnt = 0;
	}
}


void Fire::Draw(void)
{
	//----- �r���{�[�h -----
	DirectX::XMMATRIX invCameraM = CameraMgr::GetInverseCameraMatrix();
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMStoreFloat4x4(&mat, invCameraM);
	mat._41 = 0;
	mat._42 = 0;
	mat._43 = 0;
	// Y���Œ�ŉ�]
	mat._21 = 0;
	mat._22 = 1;
	mat._23 = 0;
	invCameraM = DirectX::XMLoadFloat4x4(&mat);
	SHADER->SetWorld(
		DirectX::XMMatrixScaling(// �g�k
//			m_size.x * 1.2f - (rand() % static_cast<int>(m_size.x * 10) / 10.0f * 0.4f),
//			m_size.y * 1.2f - (rand() % static_cast<int>(m_size.y * 10) / 10.0f * 0.4f),
//			m_size.z)
			m_size.x, m_size.y, m_size.z)
		* invCameraM												// ��]
		* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));	// �ړ�
	SHADER->SetTexture(m_pTex);
	m_buffer.Write(m_pVtx);
	m_buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	SHADER->SetTexture(NULL);
}


void Fire::OnCollision(GameObject *other)
{
	// ���������瑦������
	if (other->isPlayer())
	{
		dynamic_cast<Player*>(other)->ReSpawn();
	}
}


void Fire::UpdateUV(void)
{
	int u = m_nTexNum % FIRE_TEX_SPLIT_U;
	int v = m_nTexNum / FIRE_TEX_SPLIT_U;

	m_pVtx[0].uv = DirectX::XMFLOAT2(1.0f / FIRE_TEX_SPLIT_U *    u   , 1.0f / FIRE_TEX_SPLIT_V *    v);
	m_pVtx[1].uv = DirectX::XMFLOAT2(1.0f / FIRE_TEX_SPLIT_U * (u + 1), 1.0f / FIRE_TEX_SPLIT_V *    v);
	m_pVtx[2].uv = DirectX::XMFLOAT2(1.0f / FIRE_TEX_SPLIT_U *    u   , 1.0f / FIRE_TEX_SPLIT_V * (v + 1));
	m_pVtx[3].uv = DirectX::XMFLOAT2(1.0f / FIRE_TEX_SPLIT_U * (u + 1), 1.0f / FIRE_TEX_SPLIT_V * (v + 1));
}
