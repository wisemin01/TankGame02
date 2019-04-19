#pragma once
#include "Texture.h"
class SingleTexture :
	public Texture
{
public:
	SingleTexture();
	virtual ~SingleTexture();

	virtual void AddTexture(RsKey path, int count = 0);
	virtual Texture* GetTexture(int count = -1);

	virtual size_t Size() { return 1; }
};

