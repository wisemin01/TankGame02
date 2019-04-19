#include "DXUT.h"
#include "TrackingBullet.h"

#include "Explode.h"

TrackingBullet::TrackingBullet()
{
}


TrackingBullet::~TrackingBullet()
{
}

void TrackingBullet::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Rigidbody);
	AC(Life);
	pTrackRange = AC(Collider);
	AC(Collider);

	rigidbody->bUseGravity = false;
	transform->vScale = Vector3(0.5, 0.5, 0.5);

	life->Setup(1, [&]() { OnDeath(); });
	eTargetId = NONE_ID;
}

void TrackingBullet::Update(float dt)
{
	fFrameSkip += dt;

	GameObject* pTarget = OBJECT.GetObjectAsId(eTargetId);

	if (pTarget)
	{
		vDirection = pTarget->transform->vPosition - transform->vPosition;

		D3DXVec3Normalize(&vDirection, &vDirection);

	}
	else
	{
		eTargetId = NONE_ID;
	}

	if (fFrameSkip >= fDelay)
	{
		Kill();
	}

	transform->fRot = atan2f(vDirection.y, vDirection.x);
	rigidbody->AddForce(vDirection, fSpeed);
}

void TrackingBullet::Render()
{
}

void TrackingBullet::Destroy()
{

}

void TrackingBullet::OnDeath()
{
	auto explode = InstanceEx(Explode)(6);
	explode->Setup(transform->vPosition, "EXPLODE", 0.15);
	explode->transform->vScale = Vector3(0.5, 0.5, 0);

	Kill();
}

void TrackingBullet::Setup(Vector3 pos, Vector3 dir, RsKey key, float speed, float damage, float delay)
{
	transform->vPosition = pos;
	vDirection = dir;

	renderer->SetTexture(key);

	fSpeed = speed;
	fDamage = damage;

	fDelay = delay;
	fFrameSkip = 0;

	pTrackRange->Create(2000, 2000,
		[&](Collider* other) {OnRangeCollision(other); });
	collider->CreateAsTexture(renderer->pTex,
		[&](Collider* other) {OnCollision(other); });

	pTrackRange->bTrigger = true;
}

void TrackingBullet::OnCollision(Collider * other)
{
	if (other->gameObject->CompareTag("ENEMY") ||
		other->gameObject->CompareTag("MINE") ||
		other->gameObject->CompareTag("METEOR") ||
		other->gameObject->CompareTag("STONE"))
	{
		Life* other_pLife = other->gameObject->life;

		if (other_pLife)
		{
			other->gameObject->life->Attack(fDamage);
			OnDeath();
		}
	}
}

void TrackingBullet::OnRangeCollision(Collider * other)
{
	if (other->gameObject->CompareTag("ENEMY") ||
		other->gameObject->CompareTag("MINE") ||
		other->gameObject->CompareTag("METEOR") ||
		other->gameObject->CompareTag("STONE"))
	{
		if (eTargetId == NONE_ID)
			eTargetId = other->gameObject->GetObjectID();
	}
}
