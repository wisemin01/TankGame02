#include "DXUT.h"
#include "Plain.h"

Plain* Plain::pMainPlain = nullptr;

Plain::Plain()
{
}


Plain::~Plain()
{
}

void Plain::Init()
{
	AC(Transform);
	AC(Renderer);

	iNowRender = NONE_SELECT;
}

void Plain::Update(float dt)
{
	if (iNowRender == NONE_SELECT)
		bDisplay = false;
	else
		bDisplay = true;

	renderer->tFrame(iNowRender, iNowRender, 0);
}

void Plain::Render()
{
}

void Plain::Destroy()
{
	if (pMainPlain == this)
		pMainPlain = nullptr;
}

void Plain::Show(int renderIndex)
{
	if (iNowRender == renderIndex)
		iNowRender = NONE_SELECT;
	else
		iNowRender = renderIndex;
}

void Plain::Setup(Vector3 pos, Texture * multiTex)
{
	transform->vPosition = pos;
	renderer->SetTexture(multiTex);
}

void Plain::SetMain()
{
	pMainPlain = this;
}
