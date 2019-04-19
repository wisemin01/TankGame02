#include "DXUT.h"
#include "Meteor.h"

#include "StoneObstacle.h"
#include "Explode.h"

#define DEST_Y 850

Meteor::Meteor()
{
}


Meteor::~Meteor()
{
}

void Meteor::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Collider);
	AC(Rigidbody);
	AC(Life);

	SetTag("METEOR");
	renderer->SetTexture("METEOR");
	collider->Create(120, 120, [&](Collider* other) { OnCollision(other); });
	rigidbody->fMass = 0.8f;

	rigidbody->AddForce(0, 20);

	life->Setup(1, [&]() {Kill(); });
	bRenderWarning = true;
	vWarningPos = v3Zero;

	pWarning = GETTEXTURE("METEOR_WARNING");
}

void Meteor::Update(float dt)
{
	rigidbody->AddForce(Vector3(fDirX, 0, 0), 50 * fTimeScale);

	if (transform->vPosition.y > DEST_Y)
	{
		Kill();
	}

	Vector3 camPos = CAMERA_POS;

	if (transform->vPosition.y < camPos.y)
		bRenderWarning = true;
	else
		bRenderWarning = false;

	if (bRenderWarning)
	{
		vWarningPos = Vector3(transform->vPosition.x, camPos.y, 0);
	}

	if (COLLISION.GetPixelModule()->GetCollisionCheck(
		&(transform->vPosition + Vector3(0, collider->Height() / 2.f, 0))))
	{
		Drop();
	}

	transform->fRot += dt * 10 * fTimeScale;

}

void Meteor::Render()
{
	if (bRenderWarning) {
		RESOURCE.SetRenderType(SCROLL);

		RESOURCE.ApplyWorldTransform(vWarningPos, v3Normal, 0);
		RESOURCE.Draw((*pWarning)(0), Vector3(0, 0, 0), 0xffffffff);
	}
}

void Meteor::Destroy()
{
}

void Meteor::Setup(Vector3 pos, Vector3 size)
{
	transform->vPosition = pos;
	transform->vScale = size;

	fDirX = GetRandom(-0.25f, 0.25f);

	fTimeScale = GetRandom(1.0f, 2.5f);
}

void Meteor::OnCollision(Collider * other)
{
	if (other->gameObject->CompareTag("PLAYER"))
	{
		other->gameObject->life->Attack(1);

		InstanceEx(Explode)(6)->Setup(transform->vPosition, "EXPLODE", 0.2);
		Kill();
	}
}

void Meteor::Drop()
{
	Vector3 dropPos = transform->vPosition;

	dropPos.y -= collider->Height() / 2.f;

	InstanceEx(StoneObstacle)(iRenderLayer + 1)->Setup(transform->vPosition, transform->vScale, transform->fRot);
	InstanceEx(Explode)(6)->Setup(transform->vPosition, "EXPLODE", 0.2);

	Kill();
}
