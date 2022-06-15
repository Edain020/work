//==========================================
//								  Number.cpp
//	UI(”š)ŠÖ˜A
//@§ìÒ:AT12D171 No.11 ¬”©‘å‹G
//
//````````XV—š—ğ`````````
// 2020/11/27 §ìŠJn
//`````````````````````

//===== ƒCƒ“ƒNƒ‹[ƒh•” =====
#include "Number.h"
#include "Texture.h"
#include "Defines.h"
#include "Shader.h"


//----- Ã“Iƒƒ“ƒo•Ï”‚Ì’è‹` -----
ID3D11ShaderResourceView* Number::m_pNumberTex = {};	// ”š‚ÌƒeƒNƒXƒ`ƒƒ



Number::Number()
	: m_nNum(9)
	, m_pos(0, 0, 0)
	, m_size(1, 1, 1)
{

	m_pVtx = new Vertex[4];

	int i;	// ƒ‹[ƒv—p
	for (i = 0; i < 4; ++i)
	{
		m_pVtx[i].color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	}

	m_pVtx[0].pos = DirectX::XMFLOAT3(-0.5f,  0.5f, 0.0f);
	m_pVtx[1].pos = DirectX::XMFLOAT3( 0.5f,  0.5f, 0.0f);
	m_pVtx[2].pos = DirectX::XMFLOAT3(-0.5f, -0.5f, 0.0f);
	m_pVtx[3].pos = DirectX::XMFLOAT3( 0.5f, -0.5f, 0.0f);


	UpdateUV();

	// ƒoƒbƒtƒ@ì¬
	m_buffer.CreateVertexBuffer(m_pVtx, sizeof(Vertex), 4, true);

	// ‚Ü‚¾ƒeƒNƒXƒ`ƒƒ‚ª“Ç‚İ‚Ü‚ê‚Ä‚¢‚È‚©‚Á‚½‚çƒeƒNƒXƒ`ƒƒ‚ğ“Ç‚İ‚Ş
	if (!m_pNumberTex)
	{
		LoadTextureFromFile(ASSET("number.png"), &m_pNumberTex);
	}
}


Number::~Number()
{
	Uninit();
}


void Number::Init(void)
{
}


void Number::Uninit(void)
{
	SAFE_RELEASE(m_pNumberTex);
	SAFE_DELETE_ARRAY(m_pVtx);
}


void Number::Update(void)
{

}


void Number::Draw(void)
{
	SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
	SHADER->SetTexture(m_pNumberTex);
	m_buffer.Write(m_pVtx);
	m_buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	SHADER->SetTexture(NULL);
}


void Number::SetNum(int num)
{
	m_nNum = num;
	UpdateUV();
}


void Number::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}


void Number::SetSize(DirectX::XMFLOAT3 size)
{
	m_size = size;
}


void Number::UpdateUV(void)
{
	int u = m_nNum % 5;
	int v = m_nNum / 5;

	m_pVtx[0].uv = DirectX::XMFLOAT2(1.0f / 5.0f *  u, 1.0f / 2 * v);
	m_pVtx[1].uv = DirectX::XMFLOAT2(1.0f / 5.0f * (u + 1), 1.0f / 2 * v);
	m_pVtx[2].uv = DirectX::XMFLOAT2(1.0f / 5.0f *  u, 1.0f / 2 * (v + 1));
	m_pVtx[3].uv = DirectX::XMFLOAT2(1.0f / 5.0f * (u + 1), 1.0f / 2 * (v + 1));
}
