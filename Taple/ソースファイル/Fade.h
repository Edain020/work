// �t�F�[�h�A�E�g�c���X�ɈÂ��Ȃ�Ȃ���A
//				   ��ʂ�������(�A�E�g)
// �t�F�[�h�C���c���X�ɖ��邭�Ȃ�Ȃ���
//				 ��ʂ��o��(�C��)

#ifndef _FADE_H_
#define _FADE_H_

#include <Windows.h>
#include "Image.h"

class Fade
{
public:
	HRESULT Init();
	void Uninit();
	void Update();
	void Draw();

	// �t�F�[�h��������
	bool IsFinish();
	// �t�F�[�h���s����
	bool IsExecute();
	// �t�F�[�h�J�n
	void Start(float time, bool isOut);

private:
	bool m_isOut;		// �t�F�[�h�̎��(�t�F�[�h�A�E�g���ǂ���)
	float m_maxTime;	// �t�F�[�h���s����
	float m_time;		// �t�F�[�h�o�ߎ���

	Image *m_pImage;
};


#endif // !_FADE_H_
