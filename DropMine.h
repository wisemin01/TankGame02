#pragma once
#include "GameObject.h"
class DropMine :
	public GameObject
{
	using DropMineFunc = void(DropMine::*)(void);
public:
	Vector3 vOffset;
	Vector3 vDir;
	GameObject* pTarget;

	STATE eState;

	float fSpeed;

	DropMineFunc pStateFunc[2];
public:
	DropMine();
	virtual ~DropMine();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void AttackUpdate();
	void MoveUpdate();

	void OnDeath();

	void Setup(Vector3 position, Vector3 offset, GameObject* target);
};

