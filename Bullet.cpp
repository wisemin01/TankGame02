#include "DXUT.h"
#include "Bullet.h"

#include "Explode.h"

Bullet::Bullet()
{
}


Bullet::~Bullet()
{
}

void Bullet::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Collider);
	AC(Rigidbody);
	AC(Life);

	rigidbody->bUseGravity = false;
	transform->vScale = Vector3(0.5, 0.5, 0.5);

	life->Setup(1, [&]() { OnDeath(); });
}

void Bullet::Update(float dt)
{
	rigidbody->AddForce(vDirection, fSpeed);

	transform->fRot = atan2f(vDirection.y, vDirection.x);

	fFrameSkip += dt;

	if (fFrameSkip >= fDelay)
	{
		OnDeath();
	}
}

void Bullet::Render()
{
}

void Bullet::Destroy()
{
}

void Bullet::OnDeath()
{
	auto explode = InstanceEx(Explode)(6);
	explode->Setup(transform->vPosition, "EXPLODE", 0.15);
	explode->transform->vScale = Vector3(0.5, 0.5, 0);

	Kill();
}

void Bullet::Setup(Vector3 pos, Vector3 dir, RsKey key, float speed, float damage, float delay, int tType)
{
	vDirection = dir;
	fSpeed = speed;
	fDamage = damage;
	fFrameSkip = 0;
	fDelay = delay;

	eType = tType;

	transform->vPosition = pos;
	renderer->SetTexture(key);

	collider->CreateAsTexture(renderer->pTex, [&](Collider* other) { OnCollision(other); });
}

void Bullet::OnCollision(Collider * other)
{
	switch (eType)
	{
	case ATTACK_TO_PLAYER:
		if (other->gameObject->CompareTag("PLAYER"))
		{
			other->gameObject->life->Attack(fDamage);
			OnDeath();
		}
		break;
	case ATTACK_TO_TOP_ENEMY:
	case ATTACK_TO_BOTTOM_ENEMY:
		if (other->gameObject->CompareTag("METEOR"))
		{
			other->gameObject->life->Attack(fDamage);
			OnDeath();
		}
		else if (other->gameObject->CompareTag("ENEMY"))
		{
			other->gameObject->life->Attack(fDamage);
			OnDeath();
		}
		else if (other->gameObject->CompareTag("STONE"))
		{
			other->gameObject->life->Attack(fDamage);
			OnDeath();
		}
		else if(other->gameObject->CompareTag("MINE"))
		{
			other->gameObject->life->Attack(fDamage);
			OnDeath();
		}
		break;
	}
	
}
