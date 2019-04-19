#include "DXUT.h"
#include "Button.h"


Button::Button()
{
}


Button::~Button()
{
}

void Button::Init()
{
	AC(Transform);
	AC(Renderer);

	renderer->eRenderType = SCREEN;
}

void Button::Update(float dt)
{
	bool hit = GetCollision(renderer->eRenderType);

	if (hit)
	{
		renderer->tFrame(1, 1, 0);
		Lerp(&transform->vScale, transform->vScale, v3Normal*1.2, dt * 5);

		if (INPUT.GetInputKeyDown(VK_LBUTTON))
		{
			pOnFunc();
		}
	}
	else
	{
		renderer->tFrame(0, 0, 0);
		Lerp(&transform->vScale, transform->vScale, v3Normal, dt * 5);
	}
}

void Button::Render()
{
}

void Button::Destroy()
{
}

void Button::Setup(Vector3 pos, float width, float height, function<void()> func, Texture* pTex)
{
	transform->vPosition = pos;
	pOnFunc = func;

	SetRect_F(&rcRange, -width / 2.f, -height / 2.f, width / 2.f, height / 2.f);

	renderer->SetTexture(pTex);
	renderer->eRenderType = SCREEN;
}

bool Button::GetCollision(RENDER_TYPE type)
{
	RECT_F rc;

	SetRect_F(&rc, rcRange.left + transform->vPosition.x,
		rcRange.top + transform->vPosition.y,
		rcRange.right + transform->vPosition.x,
		rcRange.bottom + transform->vPosition.y);

	Vector3 tar = INPUT.GetMouse();

	if (type == SCROLL)
		CAMERA.ApplyToWorldTransform(tar);

	return IntersectRectToVector_F(&rc, &tar);
}
