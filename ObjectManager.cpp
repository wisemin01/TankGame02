#include "DXUT.h"
#include "ObjectManager.h"

#include "GameObject.h"

ObjectManager::ObjectManager()
{
}

ObjectManager::~ObjectManager()
{
	ClearObject();
}

void ObjectManager::Update(float dt)
{
	// RENDERING LIST CLEAR
	listRender.clear();

	// OBJECT LOOP
	for (auto iter = listObject.begin(); iter != listObject.end();)
	{
		GameObject * obj = (*iter);

		if (!obj->bDeath)
		{
			if (obj->bActive)
			{
				// ADD RENDERLING LIST
				if (obj->bDisplay)
					listRender.push_back(obj);

				obj->Update(dt);
				obj->UpdateComponent(dt);
			}
			iter++;
		}
		else
		{
			if (obj->eObjectId != NONE_ID)
				RemoveId(obj->eObjectId);

			ObjectDestroy(obj);
			iter = listObject.erase(iter);
		}
	}

	// RENDERING LIST SORT
	listRender.sort(GameObject::CompareLayer);
	listRender.sort(GameObject::CompareY);
}

void ObjectManager::Render()
{
	for (auto iter : listRender)
	{
		iter->RenderComponent();
		iter->Render();
	}
}

void ObjectManager::ClearObject()
{
	for (auto iter : listObject)
	{
		ObjectDestroy(iter);
	}
	listObject.clear();
	vecIdList.clear();
}

void ObjectManager::ObjectDestroy(GameObject * object)
{
	if (object) { object->DestroyComponent(); object->Destroy(); delete object; object = nullptr; }
}

ObjectId ObjectManager::CreateObjectId(GameObject * object)
{
	vecIdList.push_back(object);
	return vecIdList.size() - 1;
}

void ObjectManager::RemoveId(ObjectId id)
{
	vecIdList[id] = nullptr;
}

GameObject * ObjectManager::GetObjectAsId(ObjectId id)
{
	if (id > vecIdList.size()
		|| id == NONE_ID)
		return nullptr;
	else return vecIdList[id];
}
