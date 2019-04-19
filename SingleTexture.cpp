#include "DXUT.h"
#include "SingleTexture.h"


SingleTexture::SingleTexture()
{
}


SingleTexture::~SingleTexture()
{
	SAFE_RELEASE(pTex);
}

void SingleTexture::AddTexture(RsKey path, int count)
{
	if (FAILED(D3DXCreateTextureFromFileExA(DEVICE, path.c_str(),
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0, D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT,
		D3DCOLOR_XRGB(10, 10, 10), &tInfo, 0, &pTex)))
	{
		CONSOLE_LOG(path << " " << typeid(SingleTexture).name() << " TEXTURE LOAD FAILED");
	}
}

Texture * SingleTexture::GetTexture(int count)
{
	return this;
}
