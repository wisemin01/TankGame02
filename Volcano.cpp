#include "DXUT.h"
#include "Volcano.h"

#include "Meteor.h"

Volcano::Volcano()
{
}


Volcano::~Volcano()
{
}

void Volcano::Init()
{
	AC(Transform);
	AC(Renderer);

	fFrameSkip = 0.0f;
	iAttackCount = 0;
	bAttackOn = false;

	renderer->SetTexture("VOLCANO");
	renderer->eRenderType = SCREEN;
}

void Volcano::Update(float dt)
{
	if (bAttackOn)
	{
		if (iAttackCount <= 0)
		{
			bAttackOn = false;
			fAttackDelay = 8.0f;
			renderer->tFrame(0, 0, 0);
			return;
		}

		fFrameSkip += dt;

		if (fFrameSkip > fDropDelay)
		{
			// DROP METEOR
			Drop();

			iAttackCount--;
			fFrameSkip = 0;
			fDropDelay = GetRandom<float>(0.5f, 1.0f);
		}
	}
	else
	{
		fFrameSkip += dt;

		if (fFrameSkip > fAttackDelay)
		{
			bAttackOn = true;
			fFrameSkip = 3.0f;
			fDropDelay = 1.0f;

			renderer->tFrame(0, 3, 0.33f);
			iAttackCount = GetRandom<int>(8, 10);

			CAMERA.Shake(3.0f, 30);
		}
	}

	transform->vOffset.y = -(CAMERA_POS.y);
}

void Volcano::Render()
{
}

void Volcano::Destroy()
{
}

void Volcano::Setup(float x, float y)
{
	transform->vPosition = Vector3(x, y, 0);
	fAttackDelay = 5.0f;
}

void Volcano::Drop()
{
	Vector3 pos = CAMERA_POS +
		Vector3(GetRandom<int>(HALFSIZEX, HALFSIZEX + WINSIZEX), -HALFSIZEY, 0);

	float sca = GetRandom<float>(0.5, 1.0);

	InstanceEx(Meteor)(-3)->Setup(pos, v3Normal * sca);
}
