#pragma once
#include "Singleton.h"

class GameObject;
class ObjectManager :
	public Singleton<ObjectManager>
{
private:
	list<GameObject*> listObject;
	list<GameObject*> listRender;

	vector<GameObject*> vecIdList;
public:
	ObjectManager();
	virtual ~ObjectManager();

	template <class T>
	T* AddObject(int layer = 0, bool display = true, bool active = true)
	{
		T* object = new T;
		object->Init();

		object->iRenderLayer = layer;
		object->bDisplay	 = display;
		object->bActive		 = active;

		listObject.push_back(object);

		return object;
	}

	template <class T>
	T* FindObject(RsKey tag)
	{
		for (auto iter : listObject)
			if (iter->CompareTag(tag)) return iter;

		return nullptr;
	}

	void Update(float dt);
	void Render();

	void ClearObject();

	void ObjectDestroy(GameObject* object);

	ObjectId CreateObjectId(GameObject* object);
	void RemoveId(ObjectId id);
	GameObject* GetObjectAsId(ObjectId id);
};

#define OBJECT ObjectManager::GetInstance()

// 새 오브젝트를 인스턴스화 시킵니다.
#define Instance(t) OBJECT.AddObject<t>()

// 인자 목록 : (int)layer, (bool)isDisplay, (bool)isActive
#define InstanceEx(t) OBJECT.AddObject<t>