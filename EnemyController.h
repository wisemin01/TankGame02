#pragma once
#include "GameObject.h"


class EnemyController :
	public GameObject
{
public:
	GameObject * pPlayer;

	float fDelay;
	float fFrameSkip;

	float fSMin;
	float fSMax;
public:
	EnemyController();
	virtual ~EnemyController();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(float sMin ,float sMax);

public:
	static int iDeathEnemyCount;
};

