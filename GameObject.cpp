#include "DXUT.h"
#include "GameObject.h"
#include "Component.h"

#include "Transform.h"
#include "Renderer.h"
#include "Rigidbody.h"
#include "Collider.h"

GameObject::GameObject()
{
}


GameObject::~GameObject()
{

}

void GameObject::UpdateComponent(float dt)
{
	for (auto iter : listComponent)
		if (iter->bActive)
			iter->Update(dt);
}

void GameObject::RenderComponent()
{
	for (auto iter : listComponent)
		iter->Render();
}

void GameObject::DestroyComponent()
{
	for (auto iter : listComponent)
	{
		iter->Destroy();
		SAFE_DELETE(iter);
	}
	listComponent.clear();
}

ObjectId GameObject::GetObjectID()
{
	if (eObjectId == NONE_ID)
	{
		eObjectId = OBJECT.CreateObjectId(this);
	}

	return eObjectId;
}

bool GameObject::CompareLayer(GameObject * t1, GameObject * t2)
{
	if (t1->iRenderLayer < t2->iRenderLayer)
		return true;
	else
		return false;
}

bool GameObject::CompareY(GameObject * t1, GameObject * t2)
{
	if (!t1->transform || !t2->transform)
		return false;

	if (t1->iRenderLayer == t2->iRenderLayer)
		return t1->transform->vPosition.y < t2->transform->vPosition.y;
	else
		return false;
}