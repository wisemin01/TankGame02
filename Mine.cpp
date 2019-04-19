#include "DXUT.h"
#include "Mine.h"

#include "Explode.h"
#include "EnemyController.h"

Mine::Mine()
{
}


Mine::~Mine()
{
}

void Mine::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Collider);
	AC(Rigidbody);
	AC(Life);

	SetTag("MINE");

	renderer->SetTexture("MINE");

	life->Setup(1, [&]() {OnDeath(); });

	rigidbody->bActive = false;
	bDropMine = false;

	transform->vScale = Vector3(0.5, 0.5, 0.5);

	collider->CreateAsTexture(renderer->pTex, [&](Collider* other) {OnCollision(other); });
}

void Mine::Update(float dt)
{
	if (transform->vPosition.y >= 900)
		OnDeath();

	if (bDropMine)
	{
		if (COLLISION.GetPixelModule()->GetCollisionCheck(&transform->vPosition))
		{
			float y = COLLISION.GetPixelModule()->GetHeightAsHeightMap(transform->vPosition.x);
			Place(Vector3(transform->vPosition.x, y, 0));
			rigidbody->bActive = false;
		}
	}
}

void Mine::Render()
{
}

void Mine::Destroy()
{
}

void Mine::Place(Vector3 pos)
{
	transform->vPosition = pos;
	transform->vPosition.y += -(collider->Height() / 2.f) + 10;
}

void Mine::Drop(Vector3 pos)
{
	bDropMine = true;
	transform->vPosition = pos;
	rigidbody->bActive = true;
}

void Mine::OnDeath()
{
	Kill();
	SOUND.DuplicatePlay("EXPLODE1", 0);
	EnemyController::iDeathEnemyCount++;

	InstanceEx(Explode)(6)->Setup(transform->vPosition, "EXPLODE", 0.2);
}

void Mine::OnCollision(Collider * other)
{
	if (other->gameObject->CompareTag("PLAYER"))
	{
		other->gameObject->life->Attack(1);
		OnDeath();
	}
}

void Mine::CreateMines(int xIndex, int count, int layer)
{
	float world_width = COLLISION.GetPixelModule()->GetHeightMap()->iHeightMapSize;

	for (int i = 0; i < count; i++)
	{
		Vector3 pos = Vector3(xIndex + i * (world_width / (float)count), 0, 0);

		pos.y = COLLISION.GetPixelModule()->GetHeightAsHeightMap(pos.x);

		if (pos.y == 1000)
			continue;

		InstanceEx(Mine)(layer)->Place(pos);
	}
}
