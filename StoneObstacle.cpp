#include "DXUT.h"
#include "StoneObstacle.h"

#include "Player.h"

StoneObstacle::StoneObstacle()
{
}


StoneObstacle::~StoneObstacle()
{
}

void StoneObstacle::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Collider);
	AC(Life)->Setup(1, [&]() { OnDeath(); });

	SetTag("STONE");

	renderer->SetTexture("STONE");
	collider->Create(120, 120, [&](Collider* other) { OnCollision(other); });
}

void StoneObstacle::Update(float dt)
{
	if (Player::bPlayerLive == false)
		Kill();
}

void StoneObstacle::Render()
{
}

void StoneObstacle::Destroy()
{
}

void StoneObstacle::Setup(Vector3 position, Vector3 size, float fRot)
{
	transform->vPosition = position;
	transform->vScale = size;
	transform->fRot = fRot;
}

void StoneObstacle::OnCollision(Collider * other)
{
	if (other->gameObject->CompareTag("PLAYER")) {
		//CONSOLE_LOG("COLLISION");
	
		other->gameObject->life->Attack(1);
		OnDeath();
	}
}

void StoneObstacle::OnDeath()
{
	Kill();
}
