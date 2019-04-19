#include "DXUT.h"
#include "EnemyController.h"

#include "Enemy.h"
#include "DropMine.h"
#include "Player.h"

int EnemyController::iDeathEnemyCount = 0;

EnemyController::EnemyController()
{
	EnemyController::iDeathEnemyCount = 0;
}


EnemyController::~EnemyController()
{
}

void EnemyController::Init()
{
}

void EnemyController::Update(float dt)
{
	if (Player::bPlayerLive == false)
		pPlayer = nullptr;

	fFrameSkip += dt;

	if (pPlayer)
	{
		if (fFrameSkip >= fDelay)
		{
			fFrameSkip = 0;
			fDelay = GetRandom(fSMin, fSMax);

			Vector3 spawn = pPlayer->transform->vPosition + Vector3(1000, -200, 0);

			int type = GetRandom(0, 1);

			if (type)
				InstanceEx(Enemy)(0)->Setup(spawn, Vector3(GetRandom(300, 500), GetRandom(-400, -200), 0),
					pPlayer);
			else
				InstanceEx(DropMine)(0)->Setup(spawn, Vector3(GetRandom(300, 450), GetRandom(-400, -200), 0),
					pPlayer);
		}
	}
	else
	{
		pPlayer = OBJECT.FindObject<GameObject>("PLAYER");
	}
}

void EnemyController::Render()
{
}

void EnemyController::Destroy()
{
}

void EnemyController::Setup(float sMin, float sMax)
{
	if (sMin > sMax)
	{
		fSMax = sMin;
		fSMin = sMax;
	}
	else
	{
		fSMax = sMax;
		fSMin = sMin;
	}

	fDelay = GetRandom(sMin, sMax);
	fFrameSkip = 0;

	pPlayer = OBJECT.FindObject<GameObject>("PLAYER");
}
