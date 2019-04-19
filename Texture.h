#pragma once
class Texture abstract
{
public:
	LPDIRECT3DTEXTURE9 pTex;
	D3DXIMAGE_INFO tInfo;
public:
	Texture();
	virtual ~Texture();

	virtual void AddTexture(RsKey path, int count = 0) PURE;
	virtual Texture* GetTexture(int count = -1) PURE;

	virtual size_t Size() PURE;

	Texture* operator ()(int iTextureFrame = -1)
	{
		return GetTexture(iTextureFrame);
	}
};

