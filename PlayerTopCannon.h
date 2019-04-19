#pragma once
#include "GameObject.h"

class Player;
class PlayerTopCannon :
	public GameObject
{
public:
	Player * pPlayer;
	Vector3 vOffset;
public:
	PlayerTopCannon();
	virtual ~PlayerTopCannon();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(Player* player, Vector3 offset);
};

