#pragma once
#include "Component.h"


class Rigidbody :
	public Component
{
public:
	Vector3 vForce;
	Vector3 vVelocity;
	Vector3	vAttenuation;

	float	fMass;
	bool	bUseGravity;
public:
	Rigidbody();
	virtual ~Rigidbody();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Destroy() override;

	inline void AddForce(float x, float y) { vForce.x += x; vForce.y += y; }
	inline void AddForce(Vector3 force) { vForce += force; }
	inline void AddForce(Vector3 dir, float force) { vForce += dir * force; }

	float GetTotalForce() { return vForce.x + vForce.y + vForce.z; }

public:
	static Vector3 vGravity;
};

