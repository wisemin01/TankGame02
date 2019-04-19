#include "DXUT.h"
#include "EndingScene.h"

#include "Fade.h"
#include "PlayerController.h"
#include "Ground.h"
#include "Button.h"
#include "ScoreAdmin.h"

EndingScene::EndingScene()
{
}


EndingScene::~EndingScene()
{
}

void EndingScene::Init()
{
	CAMERA.InitCamera(v3Zero);

	pEnding = InstanceEx(GameObject)(0, true, true);

	pEnding->AC(Transform)->vPosition = v3Center;
	pEnding->AC(Renderer);
	pEnding->renderer->eRenderType = SCREEN;

	if (PlayerController::iEndingType == HAPPY)
	{
		pEnding->renderer->tFrame(0, 25, 0.5f);
		pEnding->renderer->SetTexture("H_ENDING");
		iMaxFrame = 25;
	}
	else if (PlayerController::iEndingType == BAD)
	{
		pEnding->renderer->tFrame(0, 20, 0.5f);
		pEnding->renderer->SetTexture("B_ENDING");
		iMaxFrame = 20;
	}

	ScoreAdmin scoreAdmin;
	scoreAdmin.FileInput("./RS/DATA/score.txt");
	scoreAdmin.Insert(PlayerController::iPlayerScore[0] + PlayerController::iPlayerScore[1]);
	scoreAdmin.sort();
	scoreAdmin.FileOutput("./RS/DATA/score.txt");

	SOUND.Play("BG", 1);

	pNumber = new Number;
	bScreenUI = false;
	bScreenScore = false;
}

void EndingScene::Update(float dt)
{
	if (pEnding->renderer->tFrame.cur == iMaxFrame)
	{
		pEnding->renderer->tFrame(iMaxFrame, iMaxFrame, 0);

		if (!bScreenUI)
		{
			bScreenUI = true;
			Fade* fade = InstanceEx(Fade)(10);
			fade->Setup(255, 1, 3, [&]() {
				// UI CREATES
				bScreenScore = true;

				if (PlayerController::iEndingType == HAPPY)
					InstanceEx(Ground)(11)->SetupCenter(GETTEXTURE("H_PLAIN"), v3Center);
				else if (PlayerController::iEndingType == BAD)
					InstanceEx(Ground)(11)->SetupCenter(GETTEXTURE("B_PLAIN"), v3Center);

				InstanceEx(Button)(12)->Setup(v3Center + Vector3(-150, 140, 0), 200, 100,
					[&]() { InstanceEx(Fade)(100)->Setup(255, 1, 3,
						[&]() { SCENE.ChangeScene("STAGE1"); }, []() {});
				bScreenScore = false; }, GETTEXTURE("RE_BTN"));

				InstanceEx(Button)(12)->Setup(v3Center + Vector3(150, 140, 0), 200, 100,
					[&]() { InstanceEx(Fade)(100)->Setup(255, 1, 3,
						[&]() { SCENE.ChangeScene("TITLE"); }, []() {});
				bScreenScore = false; }, GETTEXTURE("GO_BTN"));

				}, []() {});
			fade->bNoneDelete = true;
		}
	}
}

void EndingScene::Render()
{
	RESOURCE.SetRenderType(SCREEN);

	if (bScreenScore) {
		pNumber->Draw(PlayerController::iPlayerScore[0] + PlayerController::iPlayerScore[1],
			v3Center + Vector3(-80, 15, 0), 1.0f, -3.0f);
	}
}

void EndingScene::Destroy()
{
	SAFE_DELETE(pNumber);
	SOUND.Stop("BG");
}

void EndingScene::Load()
{
	ADDTEXTURE("H_ENDING", "./RS/MAP/ENDING/HAPPY/(%d).png", 26);
	ADDTEXTURE("B_ENDING", "./RS/MAP/ENDING/BAD/(%d).png", 21);
	ADDTEXTURE("BLACK", "./RS/UI/BLACK.png");

	ADDTEXTURE("H_PLAIN", "./RS/UI/ENDING/WIN.png");
	ADDTEXTURE("B_PLAIN", "./RS/UI/ENDING/LOSE.png");
	
	ADDTEXTURE("RE_BTN", "./RS/UI/ENDING/R(%d).png", 2);
	ADDTEXTURE("GO_BTN", "./RS/UI/ENDING/N(%d).png", 2);

	SOUND.Create("BG", L"./RS/SOUND/(3).wav");
}
