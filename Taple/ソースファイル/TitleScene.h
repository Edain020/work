
// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "TitleObj.h"
#include "Image.h"
#include "Sound.h"


//===== �N���X��` =====
class TitleScene
{
public:
	TitleScene(void) {}
	~TitleScene(void) {}

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	TitleObj	*m_pTitleObj;

	Image	*m_pTitleBack;
	Image	*m_pTitleLogo;
	Image	*m_pNext;
	Image	*m_pSceneIcon;

	Sound		*m_pBGM;
	Sound		*m_pSE;
};
