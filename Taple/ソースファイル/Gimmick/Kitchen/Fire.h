//==========================================
//								StoveFire.h
//	�r���{�[�h(��)�֘A
//�@�����:AT12D171 No.29 ���{�a��
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// //�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "../Gimmick.h"


//===== �N���X��` =====
class Fire : public Gimmick
{
public:
	Fire();
	virtual ~Fire();

	virtual bool Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	virtual void OnCollision(GameObject *other);

private:
	void UpdateUV(void);

	int m_nTexCnt;
	int m_nTexNum;	//�e�N�X�`���ԍ�
	Vertex *m_pVtx;			// ���_���W
	DrawBuffer m_buffer;	// �\���p�̃o�b�t�@

	static ID3D11ShaderResourceView *m_pTex;	// �΂̃e�N�X�`��
};
