#pragma once
#include "GameObject.h"

struct ItemInfo
{
	bool bItemActive;
	float fDelay;
	float fFrameSkip;

	inline void Reset() { bItemActive = false; fDelay = 0; fFrameSkip = 0; }
	inline void Update(float dt) { fFrameSkip += dt; }
};

class PlayerTopCannon;
class Player :
	public GameObject
{
public:
	Texture * pPlayerTexture[3];
	PlayerTopCannon* pTopCannon;

	STATE eState;
	Vector3 cannonPos;
	INT iTankLevel;

	bool bRightLock;
	bool bLeftLock;
	bool bControllLock;

	bool bInvinc;
	bool bDoubleJump;
	bool bOnFloor;

	float fSpeed;
	float fWidth;
	float fWheelWidth;

	int iNuclearCount;

	ItemInfo tItemInfo[ITEM_TYPE::ITEM_END];
public:
	Player();
	virtual ~Player();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void OnRespawn();
private:
	void ProcessAsPixelMap(float dt);
	void ProcessCalculatePlayer(Vector3 moveData);
	void ProcessAttack();
	void ProcessItem(float dt);

	void OnDeath();
	void TankSetting();
	
	Vector3 GetCannonPos();
public:

	void UseItem(ITEM_TYPE item, float lifeTime);
	void UpgradeTank();
	void DegradeTank();

public:
	static Vector3 vRespawnPos;
	static bool bPlayerLive;
};

