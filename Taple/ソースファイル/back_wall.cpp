#include "back_wall.h"
#include "Shader.h"
#include "Texture.h"
#include "Defines.h"

#define WALL_SIZE_X (50)
#define WALL_SIZE_Y (50)



BackWall::~BackWall()
{
	SAFE_RELEASE(m_WallTex);
}


void BackWall::Init(StageKind stage)
{
	m_pCube = new Cube();

	m_pos = DirectX::XMFLOAT3(WALL_SIZE_X / 2 - 100, WALL_SIZE_Y / 2, +10);
	m_size = DirectX::XMFLOAT3(WALL_SIZE_X, WALL_SIZE_Y, 1);

	for (int i = 0; i < MAX_WALL_NUM; i++)
	{
		if (i == MAX_WALL_NUM / 2)
		{
			m_pos.x = WALL_SIZE_X / 2 - 100;
			m_pos.y = WALL_SIZE_Y / 2 - 50;
		}
		m_wallPos[i] = m_pos;
		m_pos.x += WALL_SIZE_X;
	}

	switch (stage)
	{
	case STAGE_KIDSROOM:
		LoadTextureFromFile(ASSET("BG/Wall.jpg"), &m_WallTex);
		break;
//	case STAGE_STUDY:
//		LoadTextureFromFile(ASSET("BG/Wall.jpg"), &m_WallTex);
//		break;
	case STAGE_KITCHEN:
		LoadTextureFromFile(ASSET("BG/Kitchen.jpg"), &m_WallTex);
		break;
	default:
		break;
	}
}


void BackWall::Draw()
{
	SHADER->SetTexture(m_WallTex);
	for (int i = 0; i < MAX_WALL_NUM; i++)
	{
		SHADER->SetWorld(
			DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			*DirectX::XMMatrixTranslation(m_wallPos[i].x, m_wallPos[i].y, m_wallPos[i].z)
		);
		m_pCube->Draw();
	}
	SHADER->SetTexture(NULL);
}