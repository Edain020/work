// インクルードガード
#pragma once


//===== インクルード部 =====
#include "CharacterBase.h"
#include "Model.h"


//===== クラス定義 =====
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
	Model *m_pBodyModel;	// テープ本体のモデル
	Model *m_pEyeModel;		// テープの目のモデル
	Model *m_pMouthModel;	// テープの口のモデル
};
