#pragma once
#include "Scene.h"

class IntroScene :
	public Scene
{
	GameObject* pTitle;

public:
	IntroScene();
	virtual ~IntroScene();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void Load() override;
};

