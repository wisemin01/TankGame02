#pragma once
#include "GameObject.h"

class Player;
class PlayerController :
	public GameObject
{
public:
	int iPlayerLife;
	int iNowStage;

	Player* pPlayer;

	bool bRespawnOn;

	Texture* pProgressBar;
	Texture* pMiniTank;
	Texture* pItem;
	Texture* pLife;
	Texture* pTime;

	Number tNumber;

	float fFrameSkip;
	float fMapSize;
	float fProgress;

public:
	PlayerController();
	virtual ~PlayerController();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void PlayerSpawn();

	int ProcessScore();

public:
	
	static int iPlayerScore[2];
	static int iEndingType;

	static void ScoreReset();
};

