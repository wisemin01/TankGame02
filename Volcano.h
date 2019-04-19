#pragma once
#include "GameObject.h"


class Volcano :
	public GameObject
{
public:
	float fAttackDelay;
	float fDropDelay;
	float fFrameSkip;

	int iAttackCount;

	bool bAttackOn = false;

public:
	Volcano();
	virtual ~Volcano();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(float x, float y);

private:
	void Drop();
};

