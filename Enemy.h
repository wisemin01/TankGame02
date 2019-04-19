#pragma once
#include "GameObject.h"

class Enemy :
	public GameObject
{
	using EnemyFunc = void(Enemy::*)(void);
public:
	Vector3 vOffset;
	Vector3 vDir;
	GameObject* pTarget;

	STATE eState;

	float fSpeed;

	EnemyFunc pStateFunc[2];
public:
	Enemy();
	virtual ~Enemy();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void AttackUpdate();
	void MoveUpdate();

	void OnDeath();

	void Setup(Vector3 position, Vector3 offset, GameObject* target);
};

