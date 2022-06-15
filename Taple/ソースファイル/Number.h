//==========================================
//									Number.h
//	UI(����)�֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/11/27 ����J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "DrawBuffer.h"
#include <DirectXMath.h>


//===== �N���X��` =====
class Number	// 1���̐�����`�悷��N���X
{
public:
	Number();
	~Number();

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetNum(int);
	void SetPos(DirectX::XMFLOAT3);
	void SetSize(DirectX::XMFLOAT3);

	DirectX::XMFLOAT3 GetSize(void) { return m_size; }

private:
	void UpdateUV(void);


	int m_nNum;	// ����(0�`9)
	DirectX::XMFLOAT3 m_pos;	// ���S���W
	DirectX::XMFLOAT3 m_size;	// �傫��
	Vertex *m_pVtx;			// ���_���W
	DrawBuffer m_buffer;	// �\���p�̃o�b�t�@
	static ID3D11ShaderResourceView *m_pNumberTex;	// �����̃e�N�X�`��
};
