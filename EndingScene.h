#pragma once
#include "Scene.h"
class EndingScene :
	public Scene
{
	GameObject* pEnding;
	Number *pNumber;

	int iMaxFrame;

	bool bScreenUI;
	bool bScreenScore;
public:
	EndingScene();
	virtual ~EndingScene();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void Load() override;
};

