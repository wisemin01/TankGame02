#include "DXUT.h"
#include "Rigidbody.h"

#include "GameObject.h"

Vector3 Rigidbody::vGravity = Vector3(0, 9.8f, 0);

Rigidbody::Rigidbody()
{
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::Init()
{
	gameObject->rigidbody = this;

	vForce		 = v3Zero;
	vVelocity	 = v3Zero;
	vAttenuation = Vector3(0.95f, 0.98f, 0);
	bUseGravity = true;

	fMass		 = 1.0f;
}

void Rigidbody::Update(float dt)
{
	if (bUseGravity)
		vForce += vGravity * fMass;

	vVelocity += vForce * dt;
	vForce = v3Zero;

	gameObject->transform->vPosition += vVelocity;

	vVelocity.x *= vAttenuation.x;
	vVelocity.y *= vAttenuation.y;
}

void Rigidbody::Destroy()
{
	if (gameObject->rigidbody == this)
		gameObject->rigidbody = nullptr;
}
