#pragma once
#include "Component.h"


class Transform :
	public Component
{
public:
	Vector3 vPosition;
	Vector3 vScale;
	Vector3 vOffset;

	float fRot;
public:
	Transform();
	virtual ~Transform();

	virtual void Init() override;
	virtual void Destroy() override;

	void ApplyTransform();
};

