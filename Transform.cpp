#include "DXUT.h"
#include "Transform.h"

#include "GameObject.h"

Transform::Transform()
	: vPosition(0, 0, 0),
	vScale(1.0, 1.0, 1.0),
	vOffset(0, 0, 0),
	fRot(0)
{

}


Transform::~Transform()
{
}

void Transform::Init()
{
	gameObject->transform = this;
}

void Transform::Destroy()
{
	if (gameObject->transform == this)
		gameObject->transform = nullptr;
}

void Transform::ApplyTransform()
{
	RESOURCE.ApplyWorldTransform(vPosition + vOffset, vScale, fRot);
}
