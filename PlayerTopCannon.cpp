#include "DXUT.h"
#include "PlayerTopCannon.h"

#include "Player.h"

#include "Bullet.h"

PlayerTopCannon::PlayerTopCannon()
{
}


PlayerTopCannon::~PlayerTopCannon()
{
}
void PlayerTopCannon::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Rigidbody);

	transform->vScale = Vector3(0.5, 0.5, 0);
	rigidbody->bUseGravity = false;
	renderer->SetTexture("TOP_CANNON");
	renderer->vCenter = Vector3(28, 32, 0);
}

void PlayerTopCannon::Update(float dt)
{
	Vector3 target = INPUT.GetMouse();

	CAMERA.ApplyToWorldTransform(target);

	Vector3 dir = target - transform->vPosition;
	D3DXVec3Normalize(&dir, &dir);

	if (INPUT.GetInputKeyDown(VK_LBUTTON))
	{
		Bullet* bullet = InstanceEx(Bullet)(0);
		bullet->Setup(transform->vPosition, dir, "BULLET_T",
			60, 1, 1, ATTACK_TO_TOP_ENEMY);
		bullet->rigidbody->AddForce(dir, 2000);
	}

	if (Player::bPlayerLive == false) {
		pPlayer = nullptr;
		Kill();
	}

	if (pPlayer) {
		transform->vPosition = pPlayer->transform->vPosition + vOffset;
		transform->fRot = atan2f(dir.y, dir.x);
	}
}

void PlayerTopCannon::Render()
{
}

void PlayerTopCannon::Destroy()
{
}

void PlayerTopCannon::Setup(Player * player, Vector3 offset)
{
	pPlayer = player;
	vOffset = offset;
}
