#pragma once

class GameObject;
class Component
{
public:
	GameObject * gameObject = nullptr;
	bool bActive = true;
public:
	Component();
	virtual~Component();

	virtual void Init() {}
	virtual void Update(float dt) {}
	virtual void Render() {}
	virtual void Destroy() {}
};

