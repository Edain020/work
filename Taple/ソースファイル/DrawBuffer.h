//==========================================
//								DrawBuffer.h
//	�`��֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/10/07 ����J�n
//		10/09 �C���f�b�N�X�o�b�t�@��ǉ�
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include <Windows.h>
#include "DirectX.h"
#include <DirectXMath.h>


//===== �\���̒�` =====
struct Vertex	// ���_���
{
	DirectX::XMFLOAT3 pos;		// x,y,z
	DirectX::XMFLOAT4 color;	// r,g,b,a
	DirectX::XMFLOAT2 uv;		// u,v
};


//===== �N���X��` =====
class DrawBuffer	// �`��֘A�p
{
public:
	DrawBuffer();
	~DrawBuffer();

	HRESULT CreateVertexBuffer(
		// �`��ɕK�v�Ȓ��_�̃f�[�^
		void *pVtx,
		// �������̒��_�̃f�[�^�T�C�Y
		UINT size,
		// �`�悷�钸�_�̐�
		UINT count,
		// ���_�o�b�t�@�̏����������\��
		bool isWrite = false
	);

	HRESULT CreateIndexBuffer(
		const long* pIdx,
		UINT count
	);

	// �o�b�t�@�̏�������
	void Write(void *pData);

	// �o�b�t�@�̕`��
	void Draw(
		// �|���S���̕`����@
		D3D11_PRIMITIVE_TOPOLOGY primitive);

private:
	// ���_�o�b�t�@
	ID3D11Buffer *m_pVertexBuffer;
	// ���_�̃f�[�^�T�C�Y
	UINT m_vtxSize;
	// ���_�̐�
	UINT m_vtxCount;

	// �C���f�b�N�X�o�b�t�@
	ID3D11Buffer *m_pIndexBuffer;
	// �C���f�b�N�X�̐�
	UINT m_idxCount;
};
