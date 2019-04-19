#include "DXUT.h"
#include "Explode.h"


Explode::Explode()
{
}


Explode::~Explode()
{
}

void Explode::Init()
{
	AC(Transform);
	AC(Renderer);
}

void Explode::Update(float dt)
{
	if (!bLoop && renderer->tFrame.cur == renderer->tFrame.end)
		Kill();
}

void Explode::Render()
{
}

void Explode::Destroy()
{
}

void Explode::Setup(Vector3 pos, RsKey key, float delay, bool isLoop)
{
	bLoop = isLoop;

	transform->vPosition = pos;
	renderer->SetTexture(key);	
	renderer->tFrame(0, renderer->pTex->Size() - 1, delay);
}
