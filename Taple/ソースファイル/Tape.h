// �C���N���[�h�K�[�h
#pragma once


//===== �C���N���[�h�� =====
#include "Gimmick\Gimmick.h"


//===== �O���錾 =====
class Player;


//===== �N���X��` =====
class Tape : public GameObject
{
public:
	Tape();
	virtual ~Tape();

	virtual bool Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	void SetParent(Player *pParent) { m_pParent = pParent; }
	void SetTarget(GameObject *pTarget) { m_pTarget = pTarget; }
	void SetBottomPos(DirectX::XMFLOAT3 pos);
	void SetSpeed(float speed) { m_fSpeed = speed; }
	void SetExtend(bool isExtend) { m_isExtend = isExtend; }
	void SetDraw(bool isDraw) { m_isDraw = isDraw; }

private:
	Player *m_pParent;
	GameObject *m_pTarget;
	DirectX::XMFLOAT3 m_bottomPos;
	DirectX::XMFLOAT3 m_topPos;
	float m_fAngle;
	float m_fSpeed;

	bool m_isExtend;
	bool m_isDraw;

	static ID3D11ShaderResourceView *m_pTexture;
};
