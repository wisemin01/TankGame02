#pragma once
#include "GameObject.h"
class TrackingBullet :
	public GameObject
{
public:
	ObjectId eTargetId;
	Collider * pTrackRange;

	Vector3 vDirection;

	float fSpeed;
	float fDamage;
	float fFrameSkip;
	float fDelay;
public:
	TrackingBullet();
	virtual ~TrackingBullet();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void OnDeath();

	void Setup(Vector3 pos, Vector3 dir,
		RsKey key, float speed, float damage, float delay);

	void OnCollision(Collider* other);
	void OnRangeCollision(Collider* other);
};

