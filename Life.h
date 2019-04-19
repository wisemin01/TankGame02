#pragma once
#include "Component.h"

class Life :
	public Component
{
public:
	int iCurHp = 0;
	int iMaxHp = 0;

	function<void()> pOnDeath;

	bool bDeath = false;
public:
	Life() {}
	virtual ~Life() {}

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Destroy() override;

	inline void Attack(int damage) { iCurHp -= damage; }

	inline void Setup(int hp, function<void()> death) { iCurHp = iMaxHp = hp; pOnDeath = death; }
};