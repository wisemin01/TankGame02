#include "DXUT.h"
#include "Ground.h"


Ground::Ground()
{
}


Ground::~Ground()
{
}

void Ground::Init()
{
	AC(Transform);
	AC(Renderer);
}

void Ground::Setup(Texture * pTex, Vector3 pos)
{
	transform->vPosition = pos;
	renderer->SetTexture(pTex);

	renderer->eRenderType = SCROLL;
	renderer->vCenter = v3Zero;
}

void Ground::SetupCenter(Texture * pTex, Vector3 pos)
{
	transform->vPosition = pos;
	renderer->SetTexture(pTex);

	renderer->eRenderType = SCROLL;
}

void Ground::CreateBackGround(Texture * pTex, HeightMap * pHeightMap, int layer, Vector3 vPivot)
{
	for (int i = 0; i < pHeightMap->iHeightMapCount; i++)
	{
		Texture* pTemp = (*pTex)(pHeightMap->iRandomMapKind[i]);

		InstanceEx(Ground)(layer)->Setup(pTemp,
			vPivot + Vector3(i * pTemp->tInfo.Width, 0, 0));
	}
}