//==========================================
//							  DrawBuffer.cpp
//	�`��֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/10/07 ����J�n
//		10/09 �C���f�b�N�X�o�b�t�@��ǉ�
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

//===== �C���N���[�h�� =====
#include "DrawBuffer.h"



DrawBuffer::DrawBuffer() : m_pVertexBuffer(NULL), m_vtxSize(0), m_vtxCount(0), m_pIndexBuffer(NULL), m_idxCount(0)
{

}



DrawBuffer::~DrawBuffer()
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);
}



HRESULT DrawBuffer::CreateVertexBuffer(void *pVtx, UINT size, UINT count, bool isWrite)
{
	//===== �o�b�t�@�̏���ݒ� =====
	D3D11_BUFFER_DESC bufDesc = {};

	// �o�b�t�@�̑傫��
	bufDesc.ByteWidth = size * count;
	// �o�b�t�@�̎g�p���@
	if (isWrite)
	{
		bufDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else
	{
		bufDesc.Usage = D3D11_USAGE_DEFAULT;
	}
	// �o�b�t�@�̎g�p��
	bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	//----- �o�b�t�@�̏����l��ݒ� -----
	D3D11_SUBRESOURCE_DATA subResource = {};
	// �������Ɏg���f�[�^�̒u���ꏊ�̎w��
	subResource.pSysMem = pVtx;
	// ���_�o�b�t�@�̍쐬
	HRESULT hr;
	ID3D11Device *pDevice = GetDevice();
	hr = pDevice->CreateBuffer(
		&bufDesc, &subResource,
		&m_pVertexBuffer);

	//----- ���̂ق��̏���ݒ� -----
	if (SUCCEEDED(hr))
	{
		m_vtxSize = size;
		m_vtxCount = count;
	}

	return hr;
}



HRESULT DrawBuffer::CreateIndexBuffer(const long* pIdx, UINT count)
{
	//===== �o�b�t�@�̏���ݒ� =====
	D3D11_BUFFER_DESC bufDesc = {};
	
	// �o�b�t�@�̑傫��
	bufDesc.ByteWidth = sizeof(long) * count;
	// �o�b�t�@�̎g�p���@
	bufDesc.Usage = D3D11_USAGE_DEFAULT;
	// �o�b�t�@�̎g�p��
	bufDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	//----- �o�b�t�@�̏����l��ݒ� -----
	D3D11_SUBRESOURCE_DATA subResource = {};
	// �������Ɏg���f�[�^�̒u���ꏊ�̎w��
	subResource.pSysMem = pIdx;
	// �C���f�b�N�X�o�b�t�@�̍쐬
	HRESULT hr;
	ID3D11Device *pDevice = GetDevice();
	hr = pDevice->CreateBuffer(
		&bufDesc, &subResource,
		&m_pIndexBuffer);

	//----- ���̂ق��̏���ݒ� -----
	if (SUCCEEDED(hr))
	{
		m_idxCount = count;
	}

	return hr;
}


// �o�b�t�@�̏�������
void DrawBuffer::Write(void *pData)
{
	HRESULT hr;
	ID3D11DeviceContext *pContext = GetContext();
	D3D11_MAPPED_SUBRESOURCE mapResource;
	hr = pContext->Map(
	m_pVertexBuffer, 0,
	D3D11_MAP_WRITE_DISCARD,
	0, &mapResource);

	// Map�֐��ŏ�������OK�ł����
	// ���s
	if (SUCCEEDED(hr))
	{
		memcpy_s(
			mapResource.pData,
			m_vtxSize * m_vtxCount,
			pData,
			m_vtxSize * m_vtxCount);
	}

	// �������ݏI��
	pContext->Unmap(m_pVertexBuffer, 0);
}



void DrawBuffer::Draw(D3D11_PRIMITIVE_TOPOLOGY primitive)
{
	ID3D11DeviceContext *pContext = GetContext();
	// ���_�������̑傫��
	UINT stride = m_vtxSize;
	// ���_�f�[�^�̓ǂݎ��J�n�ʒu
	UINT offset = 0;

	// �v���~�e�B�u�̐ݒ�
	// TriangleList�c���_��3���ɋ�؂��ĕ`��
	// ��) [0,1,2] [3,4,5]
	//
	// TriangleStrip�c�Q�Əꏊ��������炵�Ȃ���`��
	// ��) [0,1,2] [1,2,3] [2,3,4] [3,4,5]
	pContext->IASetPrimitiveTopology(primitive);

	// �`��Ɏg�p����o�b�t�@�̐ݒ�
	pContext->IASetVertexBuffers(
		0,	// GPU�ւ̊��蓖�Đ�
		1,	// ���_�o�b�t�@�̐�
		&m_pVertexBuffer,	// ���_�o�b�t�@
		&stride,	// ���_�̃T�C�Y
		&offset		// �ǂݎ��J�n�ʒu
	);

	// �`��
	// �C���f�b�N�X�o�b�t�@�̗L���ŕ`�揈�����኱�قȂ�
	if (m_idxCount > 0)
	{
		// �`��Ɏg�p����C���f�b�N�X�o�b�t�@��ݒ�
		pContext->IASetIndexBuffer(
			m_pIndexBuffer,
			// �C���f�b�N�X�������̑傫��
			// 4byte = 32bit
			// 2byte = 64bit
			DXGI_FORMAT_R32_UINT,
			0);

		// �C���f�b�N�X�o�b�t�@���g�p���ĕ`��
		pContext->DrawIndexed(
			m_idxCount, 0, 0);
	}
	else
	{	// ���_�o�b�t�@�݂̂ŕ`��
		pContext->Draw(m_vtxCount, 0);
	}
}
