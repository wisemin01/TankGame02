#include "DXUT.h"
#include "Renderer.h"

#include "GameObject.h"
#include "Transform.h"

Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}

void Renderer::Init()
{
	gameObject->renderer = this;
	tColor = 0xffffffff;
	tFrame(0, 0, 0);
}

void Renderer::Update(float dt)
{
	tFrame(dt);
}

void Renderer::Render()
{
	if (!pTex) return;

	RESOURCE.SetRenderType(eRenderType);
	gameObject->transform->ApplyTransform();
	RESOURCE.Draw((*pTex)(tFrame.cur), vCenter, tColor);
}

void Renderer::Destroy()
{
	if (gameObject->renderer == this)
		gameObject->renderer = nullptr;
}
