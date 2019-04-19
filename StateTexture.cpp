#include "DXUT.h"
#include "StateTexture.h"

#include "MultiTexture.h"

int StateTexture::iStateFrameCount = 0;

StateTexture::StateTexture()
{
	pTex[0] = nullptr;
	pTex[1] = nullptr;
	pTex[2] = nullptr;
}


StateTexture::~StateTexture()
{
	for (int i = 0; i < 3; i++)
	{
		SAFE_DELETE(pTex[i]);
	}
}

void StateTexture::AddTexture(RsKey path, int count)
{
	if (count & ATTACK) {
		pTex[0] = new MultiTexture;
		pTex[0]->AddTexture(path + "A(%d).png", iStateFrameCount);
	}
	if (count & IDLE) {
		pTex[1] = new MultiTexture;
		pTex[1]->AddTexture(path + "I(%d).png", iStateFrameCount);
	}
	if (count & MOVE) {
		pTex[2] = new MultiTexture;
		pTex[2]->AddTexture(path + "M(%d).png", iStateFrameCount);
	}
}

Texture * StateTexture::GetTexture(int count)
{
	if (count == -1)
		return this;
	else
	{
		if (count == ATTACK)
			return pTex[0];
		if (count == IDLE)
			return pTex[1];
		if (count == MOVE)
			return pTex[2];
	}
}
