#include "DXUT.h"
#include "Nuclear.h"
#include "Explode.h"

Nuclear::Nuclear()
{
}


Nuclear::~Nuclear()
{
}

void Nuclear::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Collider);

	xIndex = -955;

	renderer->SetTexture("NUCLEAR");
	collider->CreateAsTexture(renderer->pTex, [&](Collider* other) {
		if (other->gameObject->CompareTag("ENEMY") ||
			other->gameObject->CompareTag("MINE") ||
			other->gameObject->CompareTag("METEOR") ||
			other->gameObject->CompareTag("STONE"))
		{
			if (Life* life = other->gameObject->life) {
				life->Attack(100);
				auto explode = InstanceEx(Explode)(6);
				explode->Setup(other->gameObject->transform->vPosition,
					"EXPLODE", 0.15);
			}
		}
		});

	CAMERA.Shake(2.f, 50);
}

void Nuclear::Update(float dt)
{
	xIndex += dt * 500;

	transform->vPosition = CAMERA_POS + Vector3(xIndex, HALFSIZEY, 0);

	if (xIndex > WINSIZEX + 955)
		Kill();
}

void Nuclear::Render()
{
}

void Nuclear::Destroy()
{
}
