#pragma once
#include "Scene.h"

class TitleScene :
	public Scene
{
public:
	int iTop3Score[3];
	bool bScoreRender;

	Number* pNumber;
public:
	TitleScene();
	virtual ~TitleScene();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	virtual void Load() override;
	
	void ScoreRender();
};

