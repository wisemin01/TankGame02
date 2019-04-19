#pragma once
#include "GameObject.h"


class Bullet :
	public GameObject
{
public:
	
public:
	Vector3 vDirection;

	float fSpeed;
	float fDamage;
	float fFrameSkip;
	float fDelay;

	int eType;
public:
	Bullet();
	virtual ~Bullet();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void OnDeath();

	void Setup(Vector3 pos, Vector3 dir, RsKey key, float speed, float damage, float delay, int attackType = ATTACK_TO_BOTTOM_ENEMY);

	void OnCollision(Collider* other);
};

