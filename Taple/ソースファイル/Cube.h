//==========================================
//									  Cube.h
//	—§•û‘ÌŠÖ˜A
//@§ìÒ:AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ğ`````````
// 2020/10/07 §ìŠJn
//`````````````````````

// ƒCƒ“ƒNƒ‹[ƒhƒK[ƒh
#pragma once


//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "DrawBuffer.h"


//===== ƒNƒ‰ƒX’è‹` =====
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
	float m_xzAngle;	// XZ²ã‚Å‚ÌŠp“x(0‹‚Å-Z‚ÌˆÊ’u)
	float m_yAngle;		// XZ²ã‚Å‰ñ“]‚µ‚½Šp“x(0‹‚Å…•½)
	DrawBuffer m_buffer;
	Vertex *m_pVtx;
};
