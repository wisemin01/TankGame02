#include "DXUT.h"
#include "Enemy.h"

#include "Bullet.h"
#include "Player.h"

#include "Item.h"
#include "Explode.h"
#include "EnemyController.h"

Enemy::Enemy()
	: pTarget(nullptr)
{
}


Enemy::~Enemy()
{
}

void Enemy::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Collider);
	AC(Rigidbody);
	AC(Life);

	SetTag("ENEMY");

	transform->vScale = Vector3(0.8, 0.8, 0);

	renderer->SetTexture("ENEMY");
	collider->Create(175, 290, [](Collider*) {});
	rigidbody->bUseGravity = false;
	life->Setup(5, [&]() { OnDeath(); });

	eState = MOVE;

	pStateFunc[0] = &Enemy::MoveUpdate;
	pStateFunc[1] = &Enemy::AttackUpdate;
}

void Enemy::Update(float dt)
{
	if (Player::bPlayerLive == false)
		pTarget = nullptr;

	if (eState == MOVE)
		(this->*pStateFunc[0])();
	else if (eState == ATTACK)
		(this->*pStateFunc[1])();

	rigidbody->AddForce(vDir, fSpeed);

	if (pTarget &&
		transform->vPosition.y > pTarget->transform->vPosition.y + vOffset.y)
	{
		Lerp(&transform->vPosition.y, transform->vPosition.y,
			pTarget->transform->vPosition.y + vOffset.y, dt * 2);
	}
}

void Enemy::Render()
{
}

void Enemy::Destroy()
{
}

void Enemy::AttackUpdate()
{
	if (renderer->tFrame.cur)
	{
		eState = MOVE;
		renderer->tFrame(0, 0, 0);

		Bullet* bullet = InstanceEx(Bullet)();
		bullet->Setup(transform->vPosition, Vector3(0, 1, 0), "BULLET_E", 30, 1, 1,
			ATTACK_TO_PLAYER);
		bullet->rigidbody->AddForce(0, 100);
	}
}

void Enemy::MoveUpdate()
{
	if (pTarget)
	{
		Vector3 vEnd = pTarget->transform->vPosition + vOffset;
		vDir = vEnd - transform->vPosition;

		if (D3DXVec3Length(&vDir) < 200) {
			eState = ATTACK;
			renderer->tFrame(0, 3, 0.4);
		}

		D3DXVec3Normalize(&vDir, &vDir);
	}
	else
	{
		vDir = Vector3(0, -1, 0);
	}
}

void Enemy::OnDeath()
{
	Kill();
	SOUND.DuplicatePlay("EXPLODE1", 0);
	EnemyController::iDeathEnemyCount++;

	InstanceEx(Explode)(6)->Setup(transform->vPosition, "EXPLODE_B", 0.15);
	if (GetRandom(0, 1))
		InstanceEx(Item)(5)->RandomSetup(transform->vPosition);
}

void Enemy::Setup(Vector3 position, Vector3 offset, GameObject* target)
{
	transform->vPosition = position;
	vOffset = offset;

	pTarget = target;
	fSpeed = 30;
}
