//==========================================
//									bitmap.h
//�@�����:AT11B192 No.17 ������G
//�`�`�`�`�`�`�`�`�X�V�����`�`�`�`�`�`�`�`�`
//2020/02/07
// �v���O��������J�n
//2020/02/18
// �֐��R�����g�̋L�q
//�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`�`

#ifndef _BITMAP_H_
#define _BITMAP_H_

//===== �C���N���[�h�� =====
#include <windows.h>

//===== �萔�E�}�N����` =====
#define FILEHEADERSIZE	(14)
#define INFOHEADERSIZE	(40)
#define HEADERSIZE		(FILEHEADERSIZE+INFOHEADERSIZE)


//===== �\���̐錾 =====

//------------------
//RBG�f�[�^��ۑ����邽�߂̍\����
//------------------
typedef struct {
	unsigned char r;	
	unsigned char g;
	unsigned char b;
} RGB;

//------------------
//�r�b�g�}�b�v�f�[�^��ۑ����邽�߂̍\����
//------------------
typedef struct {
	unsigned int height;	//�摜�̍���
	unsigned int width;		//�摜�̒���
	RGB *data;				//RGB�f�[�^
	CHAR_INFO *cell;
} IMAGE;


//===== �v���g�^�C�v�錾 ======

//--------------------------------------
//�֐����FRead_Bmp
//���@���Fconst char*, unsigned int, unsigned int
//(�ǂݍ��ރt�@�C���̖��O�A�~�����f�[�^�̃T�C�Y(�����A����))
//�߂�l�FIMAGE* (�ǂݍ��񂾃r�b�g�}�b�v�̏��)
//���@�e�F�r�b�g�}�b�v�f�[�^���w�肵���傫���ɏk�ڂ�ύX���ēǂݍ���
//--------------------------------------
IMAGE *Read_Bmp(const char*, unsigned int, unsigned int);
//--------------------------------------
//�֐����FFree_Image
//���@���FIMAGE* (�����������r�b�g�}�b�v�f�[�^)
//�߂�l�F�Ȃ�
//���@�e�F�ǂݍ��񂾃r�b�g�}�b�v�f�[�^���������A�������̈���������
//--------------------------------------
void Free_Image(IMAGE*);

#endif // !_BITMAP_H_
