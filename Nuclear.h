#pragma once
#include "GameObject.h"
class Nuclear :
	public GameObject
{
private:
	float xIndex;
public:
	Nuclear();
	virtual ~Nuclear();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;
};

