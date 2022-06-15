//==========================================
//									 Model.h
//	���f���֘A
//�@�����:AT12D171 No.11 ������G
//
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
// 2020/10/16 ����J�n
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "DrawBuffer.h"
#include "FBX/FBXPlayer.h"


//===== �N���X��` =====
class Model	// 3D���f���p�N���X
{
public:
	Model();
	~Model();

	bool LoadModel(const char* pFilePath);
	void Draw();

private:
	// �Q�[���̃L�����N�^�[�͕����̃p�[�c�Ő��藧���Ă���
	// ���̃p�[�c�������b�V���ƌĂ�
	// ��{�I�Ɉ�̃��b�V���ň�̒��_�o�b�t�@������
	// ���f�����ƂɃ��b�V���̐����Ⴄ���߁A���_�o�b�t�@�𓮓I�Ɋm�ۂ���
	DrawBuffer *m_pBuffer;

	FBXPlayer m_fbx;	// FBX�t�@�C������N���X
};
