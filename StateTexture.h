#pragma once
#include "Texture.h"

class StateTexture :
	public Texture
{
private:
	Texture * pTex[3];
public:
	StateTexture();
	virtual ~StateTexture();

	virtual void AddTexture(RsKey path, int count = 0);
	virtual Texture* GetTexture(int count = -1);

	virtual size_t Size() { return 1; }

public:
	static int iStateFrameCount;
};

