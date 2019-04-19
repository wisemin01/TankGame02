#include "DXUT.h"
#include "PlayerController.h"
#include "EnemyController.h"

#include "Player.h"
#include "Fade.h"

int PlayerController::iPlayerScore[2];
int PlayerController::iEndingType = HAPPY;

PlayerController::PlayerController()
{
}


PlayerController::~PlayerController()
{
}

void PlayerController::Init()
{
	iPlayerLife = 4;
	pPlayer = nullptr;
	bRespawnOn = false;
	fFrameSkip = 99;
	fProgress = 0.0f;
	
	pProgressBar = GETTEXTURE("PROGRESS_BAR");
	pMiniTank = GETTEXTURE("MINITANK");
	pItem = GETTEXTURE("ITEM_UI");
	pLife = GETTEXTURE("HEART");
	pTime = GETTEXTURE("CLOCK");

	fMapSize = COLLISION.GetPixelModule()->GetHeightMap()->iHeightMapSize;

	if (SCENE.GetSceneName() == "STAGE1")
		iNowStage = 0;
	else if (SCENE.GetSceneName() == "STAGE2")
		iNowStage = 1;

	iPlayerScore[iNowStage] = 0;

	Player::vRespawnPos = Vector3(300, 250, 0);
}

void PlayerController::Update(float dt)
{
	fFrameSkip -= dt;

	if (Player::bPlayerLive == false)
	{
		pPlayer = nullptr;

		if (!bRespawnOn) {
			DelayMsg::Send(2.0f, [&]() {
				InstanceEx(Fade)(100)->Setup(255, 2, 3, [&]() { PlayerSpawn(); }, []() {});
				});
			bRespawnOn = true;
		}

	}
	else if (fFrameSkip <= 0.5)
	{
		pPlayer->Kill();
	}
	else {
		fProgress = pPlayer->transform->vPosition.x / fMapSize;

		if (fProgress >= 0.99)
		{
			pPlayer->bControllLock = true;
			pPlayer->rigidbody->bActive = false;

			iPlayerScore[iNowStage] = ProcessScore();
			iEndingType = HAPPY;

			if (SCENE.GetSceneName() == "STAGE1")
				SCENE.ChangeScene("STAGE2");
			else if (SCENE.GetSceneName() == "STAGE2")
				SCENE.ChangeScene("ENDING");
		}
	}
}

void PlayerController::Render()
{
	RESOURCE.SetRenderType(SCREEN);

	// Áö³­ ½Ã°£ ·»´õ

	{
		RESOURCE.ApplyDraw(pTime, Vector3(50, 50, 0), 0xffffffff);
		tNumber.Draw((int)fFrameSkip, Vector3(100, 50, 0), 1.0f, -3.0f);
	}

	// ¸ñ¼û ·»´õ

	{
		RESOURCE.ApplyDraw(pLife, Vector3(210, 60, 0), 0xffffffff);
		tNumber.Draw((int)iPlayerLife, Vector3(300, 50, 0), 1.0f, -3.0f);
	}

	// ¾ÆÀÌÅÛ ·»´õ

	if (pPlayer)
	{
		int renderXIndex = 0;

		Vector3 defaultVec = Vector3(WINSIZEX - pItem->GetTexture(0)->tInfo.Width / 2.f - 10,
			pItem->GetTexture(0)->tInfo.Height / 2.f + 10, 0);

		for (int i = 0; i < ITEM_END; i++) {
			if (pPlayer->tItemInfo[i].bItemActive)
			{
				Vector3 p = defaultVec + Vector3(renderXIndex, 0, 0);

				RESOURCE.ApplyDraw(pItem->GetTexture(i), p, 0xffffffff);
				renderXIndex -= pItem->GetTexture(i)->tInfo.Width;

				if (pPlayer->tItemInfo[i].fDelay > 0)
				{
					tNumber.Draw(pPlayer->tItemInfo[i].fDelay - pPlayer->tItemInfo[i].fFrameSkip,
						p, 0.5, 0.0);
				}
			}
		}
	}

	// ÁøÇà ¹Ù ·»´õ

	{
		float w = pProgressBar->GetTexture(1)->tInfo.Width;
		float h = pProgressBar->GetTexture(1)->tInfo.Height;

		RECT rc;
		SetRect(&rc, 0, 0, w * fProgress, h);

		// ÇÏ´Ü ¹Ù
		RESOURCE.ApplyDraw(pProgressBar->GetTexture(0), Vector3(HALFSIZEX, WINSIZEY - 40, 0), 0xffffffff);

		// Àß¸®´Â »ó´Ü ¹Ù
		RESOURCE.ApplyWorldTransform(Vector3(HALFSIZEX, WINSIZEY - 40, 0), v3Normal, 0);
		RESOURCE.RectDraw(pProgressBar->GetTexture(1), Vector3(w / 2.f, h / 2.f, 0), rc, 0xffffffff);

		// ¹Ì´ÏÅÊÅ© UI
		RESOURCE.ApplyDraw(pMiniTank, 
			Vector3(HALFSIZEX - (w / 2.f) + w * fProgress, WINSIZEY - 40, 0), 0xffffffff);
	}
}

void PlayerController::Destroy()
{
}

void PlayerController::PlayerSpawn()
{
	if (iPlayerLife <= 1) {
		iEndingType = BAD;
		iPlayerScore[iNowStage] = ProcessScore();
		SCENE.ChangeScene("ENDING");
		return;
	}

	bRespawnOn = false;
	fFrameSkip = 99;

	pPlayer = InstanceEx(Player)(5);
	iPlayerLife--;
}

int PlayerController::ProcessScore()
{
	return fFrameSkip + iPlayerLife * 30 + EnemyController::iDeathEnemyCount * 5;
}

void PlayerController::ScoreReset()
{
	iPlayerScore[0] = 0;
	iPlayerScore[1] = 0;
}
