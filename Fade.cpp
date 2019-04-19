#include "DXUT.h"
#include "Fade.h"


Fade::Fade()
	: bNoneDelete(false)
{
}


Fade::~Fade()
{
}

void Fade::Init()
{
	AC(Transform);
	AC(Renderer);
	
	renderer->SetTexture("BLACK");
	renderer->eRenderType = SCREEN;

	transform->vPosition = v3Center;
	iCount = 0;
}

void Fade::Update(float dt)
{
	if (iCount > 0) {

		if (bDown)
		{
			renderer->tColor.a -= (fSpeed) / 255.f;
			if ((renderer->tColor.a) <= 0) {
				bDown = false;
				OnAlpha0();
				iCount--;
			}
		}
		else
		{
			renderer->tColor.a += (fSpeed) / 255.f;
			if ((renderer->tColor.a) >= 1.0f) {
				bDown = true;
				OnAlpha255();
				iCount--;
			}
		}

	}
	else
	{
		if (!bNoneDelete)
		{
			Kill();
		}
	}
}

void Fade::Render()
{
}

void Fade::Destroy()
{
}

void Fade::Setup(int type, int count, float speed, function<void()> on255, function<void()> on0)
{
	if (type == 255)
	{
		renderer->tColor.a = 0;
		bDown = false;
	}
	else
	{
		renderer->tColor.a = 1;
		bDown = true;
	}

	iCount = count;
	fSpeed = speed;

	OnAlpha0 = on0;
	OnAlpha255 = on255;
}
