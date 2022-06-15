//==========================================
//									  Cube.h
//	�����̊֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/10/07 ����J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "DrawBuffer.h"


//===== �N���X��` =====
class Cube
{
public:
	Cube();
	~Cube();

	void SetPos(float x, float y, float z);
	void SetSize(float width, float height, float depth);

	void Draw();
		
private:
	float m_posX, m_posY, m_posZ;
	float m_width, m_height, m_depth;
	float m_xzAngle;	// XZ����ł̊p�x(0����-Z�̈ʒu)
	float m_yAngle;		// XZ����ŉ�]�����p�x(0���Ő���)
	DrawBuffer m_buffer;
	Vertex *m_pVtx;
};
