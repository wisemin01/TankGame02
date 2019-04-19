#include "DXUT.h"
#include "Life.h"

#include "GameObject.h"

void Life::Init()
{
	gameObject->life = this;
}

void Life::Update(float dt)
{
	if (!bDeath) {
		if (iCurHp <= 0)
		{
			bDeath = true;
			pOnDeath();
		}
	}
}

void Life::Destroy()
{
	if (gameObject->life == this)
		gameObject->life = nullptr;
}
