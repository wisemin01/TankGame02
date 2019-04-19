#include "DXUT.h"
#include "SavePoint.h"

#include "Player.h"

SavePoint::SavePoint()
{
}


SavePoint::~SavePoint()
{
}

void SavePoint::Init()
{
	bPassed = false;

	AC(Transform);
	AC(Renderer);
	AC(Collider);

	renderer->SetTexture("SAVEPOINT");
	renderer->tFrame(0, 0, 0);
	collider->CreateAsTexture(renderer->pTex,
		[&](Collider* other) {
			if (bPassed)
				return;

			if (other->gameObject->CompareTag("PLAYER")) {
				Player::vRespawnPos = transform->vPosition;
				bPassed = true;
				renderer->tFrame(0, 4, 0.1f);
			}
		});
}

void SavePoint::Update(float dt)
{
	if (renderer->tFrame.cur == 4)
		renderer->tFrame(4, 4, 0);
}

void SavePoint::Render()
{
}

void SavePoint::Destroy()
{
}

void SavePoint::Place(Vector3 pos)
{
	transform->vPosition = pos;
	transform->vPosition.y -= (renderer->Height() / 2.f) - 5;
}

void SavePoint::CreateSavePoints(int xIndex, int count, int layer)
{
	float world_width = COLLISION.GetPixelModule()->GetHeightMap()->iHeightMapSize;

	for (int i = 0; i < count; i++)
	{
		Vector3 pos = Vector3(xIndex + i * (world_width / (float)count), 0, 0);

		pos.y = COLLISION.GetPixelModule()->GetHeightAsHeightMap(pos.x);

		if (pos.y == 1000)
			continue;

		InstanceEx(SavePoint)(layer)->Place(pos);
	}
}
