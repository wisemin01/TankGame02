#include "DXUT.h"
#include "Item.h"

#include "Player.h"

Item::Item()
{
}


Item::~Item()
{
}

void Item::Init()
{
	AC(Renderer);
	AC(Transform);
	AC(Collider);
	AC(Rigidbody);
}

void Item::Update(float dt)
{
	float pY = COLLISION.GetPixelModule()->GetHeightAsHeightMap(transform->vPosition.x);

	if (transform->vPosition.y >= pY)
	{
		rigidbody->bActive = false;
		transform->vPosition.y = pY - collider->Height() / 2.f + 10;
	}
}

void Item::Render()
{
}

void Item::Destroy()
{
}

void Item::RandomSetup(Vector3 pos)
{
	eType = (ITEM_TYPE)GetRandom(0, (int)ITEM_END - 1);

	renderer->SetTexture(GETTEXTURE("ITEM", eType));
	transform->vPosition = pos;
	collider->Create(100.f, 100.f, [&](Collider* other) {
		if (other->gameObject->CompareTag("PLAYER"))
		{
			Player* p = reinterpret_cast<Player*>(other->gameObject);

			if (eType == SPEED_UP)
				p->UseItem(eType, -1);
			else
				p->UseItem(eType, 15);
			Kill();
		}
		});
}
