// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "CharacterBase.h"
#include "Model.h"


//===== �N���X��` =====
class TitleObj : public CharacterBase
{
public:
	TitleObj();
	~TitleObj();

	bool Init();
	void Uninit();
	void Update();
	void Draw();

private:
	Model *m_pBodyModel;	// �e�[�v�{�̂̃��f��
	Model *m_pEyeModel;		// �e�[�v�̖ڂ̃��f��
	Model *m_pMouthModel;	// �e�[�v�̌��̃��f��
};
