#pragma once

class Component;

class Transform;
class Renderer;
class Collider;
class Rigidbody;
class Life;

enum ID_TYPE
{
	NONE_ID = -1
};

class GameObject
{
private:
	list<Component*> listComponent;
	string szTag;
public:
	Transform* transform = nullptr;
	Renderer* renderer = nullptr;
	Collider* collider = nullptr;
	Rigidbody* rigidbody = nullptr;
	Life* life = nullptr;

	ObjectId eObjectId = NONE_ID;

	bool bActive = true;
	bool bDisplay = true;
	bool bDeath = false;

	int iRenderLayer = 0;

public:
	GameObject();
	virtual ~GameObject();

	virtual void Init() {}
	virtual void Update(float dt) {}
	virtual void Render() {}
	virtual void Destroy() {}

	virtual void Kill() { bDeath = true; }

	void UpdateComponent(float dt);
	void RenderComponent();
	void DestroyComponent();

	bool CompareTag(const string& tag) { return szTag == tag; }
	void SetTag(const string& tag) { szTag = tag; }

	ObjectId GetObjectID();

public:
	template <class T>
	T* AddComponent()
	{
		T* c = new T;
		c->gameObject = this;
		c->Init();

		listComponent.push_back(c);

		return c;
	}

	template <class T>
	T* GetComponent()
	{
		for (auto iter : listComponent)
		{
			if (typeid(iter).name() == typeid(T*).name())
				return iter;
		}
		return nullptr;
	}

public:
	static bool CompareLayer(GameObject* t1, GameObject* t2);
	static bool CompareY(GameObject* t1, GameObject* t2);
};

