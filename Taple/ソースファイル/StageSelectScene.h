
// インクルードガード
#pragma once


//===== インクルード部 =====
#include "Model.h"
#include "Image.h"
#include "Sound.h"
#include "Defines.h"
#include "Texture.h"


//===== クラス定義 =====
class StageSelectScene
{
public:
	StageSelectScene(void)
		: m_stage(STAGE_MAX)
		, m_angle(0.0f)
		, m_currentAngle(0.0f)
		, m_cnt(0)
	{}
	~StageSelectScene(void) {}

	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	StageKind GetStage(void);

private:
	int m_stage;
	float m_angle;
	float m_currentAngle;
	int m_cnt;

	ID3D11ShaderResourceView *m_pTex;

	Model *m_pStageIcon[STAGE_MAX];
	Image *m_pStageImage[STAGE_MAX];
	Image *m_pStageName[STAGE_MAX];

	Image *m_pNext;
	Image *m_pSceneIcon;

	Sound *m_pBGM;
	Sound *m_pSelectSE;
	Sound *m_pNextSE;
	
};

