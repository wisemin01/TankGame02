#include "DXUT.h"
#include "DropMine.h"

#include "Player.h"
#include "Explode.h"
#include "Mine.h"
#include "Item.h"
#include "EnemyController.h"

DropMine::DropMine()
{
}


DropMine::~DropMine()
{
}

void DropMine::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Collider);
	AC(Rigidbody);
	AC(Life);

	SetTag("ENEMY");

	transform->vScale = Vector3(0.8, 0.8, 0);

	renderer->SetTexture("DROP_MINE");
	collider->Create(175, 290, [](Collider*) {});
	rigidbody->bUseGravity = false;
	life->Setup(5, [&]() { OnDeath(); });

	eState = MOVE;

	pStateFunc[0] = &DropMine::MoveUpdate;
	pStateFunc[1] = &DropMine::AttackUpdate;
}

void DropMine::Update(float dt)
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

void DropMine::Render()
{
}

void DropMine::Destroy()
{
}

void DropMine::AttackUpdate()
{
	if (renderer->tFrame.cur)
	{
		eState = MOVE;
		renderer->tFrame(0, 0, 0);

		Mine* mine = InstanceEx(Mine)();
		mine->Drop(transform->vPosition);
		mine->rigidbody->AddForce(0, 50);
	}
}

void DropMine::MoveUpdate()
{
	if (pTarget)
	{
		Vector3 vEnd = pTarget->transform->vPosition + vOffset;
		vDir = vEnd - transform->vPosition;

		if (D3DXVec3Length(&vDir) < 200) {
			eState = ATTACK;
			renderer->tFrame(0, 3, 1.2f);
		}

		D3DXVec3Normalize(&vDir, &vDir);
	}
	else
	{
		vDir = Vector3(0, -1, 0);
	}
}

void DropMine::OnDeath()
{
	Kill();

	InstanceEx(Explode)(6)->Setup(transform->vPosition, "EXPLODE_B", 0.15);
	SOUND.DuplicatePlay("EXPLODE1", 0);

	EnemyController::iDeathEnemyCount++;

	if (GetRandom(0, 1))
		InstanceEx(Item)(5)->RandomSetup(transform->vPosition);
}

void DropMine::Setup(Vector3 position, Vector3 offset, GameObject * target)
{
	transform->vPosition = position;
	vOffset = offset;

	pTarget = target;
	fSpeed = 30;
}
