#include "DXUT.h"
#include "Fluffy.h"


Fluffy::Fluffy()
{
}


Fluffy::~Fluffy()
{
}

void Fluffy::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Rigidbody);

	rigidbody->bUseGravity = false;
	bUp = false;
	bEnd = false;
	bFluffy = true;
	bLerp = false;
}

void Fluffy::Update(float dt)
{
	Vector3 dir = vEnd - transform->vPosition;

	if (!bEnd && D3DXVec3Length(&dir) > 5) {

		if (bLerp)
			Lerp(&transform->vPosition, transform->vPosition, vEnd, dt * 1.6f);
		else {
			D3DXVec3Normalize(&dir, &dir);
			rigidbody->AddForce(dir, fSpeed);
		}
	}
	else
	{
		bEnd = true;

		if (bFluffy)
		{
			if (bUp)
			{
				rigidbody->AddForce(Vector3(0, -1, 0), fSpeed);

				if (transform->vPosition.y < vEnd.y - (fHeight / 2.f))
					bUp = false;
			}
			else
			{
				rigidbody->AddForce(Vector3(0, 1, 0), fSpeed);

				if (transform->vPosition.y > vEnd.y + (fHeight / 2.f))
					bUp = true;
			}
		}
		else
			Lerp(&transform->vPosition.y, transform->vPosition.y, vEnd.y, dt * 30);

		Lerp(&transform->vPosition.x, transform->vPosition.x, vEnd.x, dt * 10);
	}
}

void Fluffy::Render()
{
}

void Fluffy::Destroy()
{
}

void Fluffy::Setup(RsKey key, Vector3 startPos, Vector3 targetPos,
	float speed, float height, bool bFluffy)
{
	renderer->SetTexture(key);

	transform->vPosition = startPos;
	vEnd = targetPos;

	fSpeed = speed;
	fHeight = height;
	Fluffy::bFluffy = bFluffy;
}

void Fluffy::Setup(Texture * pTex, Vector3 startPos,
	Vector3 targetPos, float speed, float height, bool bFluffy)
{
	renderer->SetTexture(pTex);

	transform->vPosition = startPos;
	vEnd = targetPos;

	fSpeed = speed;
	fHeight = height;
	Fluffy::bFluffy = bFluffy;
}
