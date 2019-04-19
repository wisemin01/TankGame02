#pragma once
#include "Texture.h"

class MultiTexture :
	public Texture
{
public:
	vector<Texture*> vecTexture;
public:
	MultiTexture();
	virtual ~MultiTexture();

	virtual void AddTexture(RsKey path, int count = 0);
	virtual Texture* GetTexture(int count = -1);

	virtual size_t Size() {return vecTexture.size(); }
};

