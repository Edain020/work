#ifndef _BACK_WALL_H_
#define _BACK_WALL_H_

#include "GameObject.h"
#include "Defines.h"


#define MAX_WALL_NUM (20)

class BackWall : public GameObject
{
public:
	BackWall() {}
	virtual ~BackWall();

	void Init(StageKind stage);
	virtual void Draw();

private:

	DirectX::XMFLOAT3 m_wallPos[MAX_WALL_NUM];
	ID3D11ShaderResourceView *m_WallTex;
};



#endif // !_BACK_WALL_H_
