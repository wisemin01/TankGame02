#include "DXUT.h"
#include "TitleScene.h"

#include "Ground.h"
#include "Fluffy.h"
#include "Button.h"
#include "Explode.h"

#include "Fade.h"
#include "Plain.h"
#include "PlayerController.h"

#include "ScoreAdmin.h"

TitleScene::TitleScene()
{
}


TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{

	SOUND.Play("BG", 1);
	CAMERA.InitCamera(v3Zero);
	// 백그라운드
	InstanceEx(Ground)(-9)->SetupCenter(GETTEXTURE("BG"), v3Center);

	// 폭발
	InstanceEx(Explode)(-8)->Setup(v3Center, "EXPLODE", 0.25f, true);

	// 구름
	InstanceEx(Fluffy)(-7)->Setup(GETTEXTURE("CLOUD", 0),
		Vector3(0, HALFSIZEY, 0), v3Center, 15, 25);
	InstanceEx(Fluffy)(-6)->Setup(GETTEXTURE("CLOUD", 1),
		Vector3(WINSIZEX, HALFSIZEY, 0), v3Center, 15, 25);
	// 바닥
	InstanceEx(Ground)(-5)->SetupCenter(GETTEXTURE("GRESS"), v3Center);

	// 적
	InstanceEx(Fluffy)(-4)->Setup(GETTEXTURE("ENEMY", 0),
		Vector3(1000, -200, 0), Vector3(1000, 250, 0), 20, 5);
	InstanceEx(Fluffy)(-4)->Setup(GETTEXTURE("ENEMY", 1),
		Vector3(300, -200, 0), Vector3(300, 180, 0), 14, 16);

	// 탱크
	Fluffy* pTemp;
	pTemp = InstanceEx(Fluffy)(-2);
	pTemp->Setup(GETTEXTURE("TANK", 0),
		Vector3(-500, HALFSIZEY, 0), Vector3(950, 500, 0), 45, 0, false);
	pTemp->bLerp = true;
	pTemp = InstanceEx(Fluffy)(-2);
	pTemp->Setup(GETTEXTURE("TANK", 1),
		Vector3(WINSIZEX + 500, HALFSIZEY, 0), Vector3(300, 550, 0), 45, 0, false);
	pTemp->bLerp = true;
	// 2초 뒤 실행

	PlayerController::ScoreReset();

	DelayMsg::Send(2.0f, [&]() {

		Plain* plain = InstanceEx(Plain)(1);
		plain->Setup(v3Center, GETTEXTURE("PLAINS"));
		plain->SetMain();

		// 타이틀 제목
		InstanceEx(Ground)(-1)->SetupCenter(GETTEXTURE("TITLE"),
			Vector3(HALFSIZEX, HALFSIZEY - 200, 0));

		// 버튼들
		InstanceEx(Button)(0)->Setup(v3Center + Vector3(0, 50, 0), 200, 100,
			[]() { InstanceEx(Fade)(100)->Setup(255, 1, 3,
				[]() { SCENE.ChangeScene("STAGE1"); }, []() {});
			}, GETTEXTURE("START_BTN"));

		InstanceEx(Button)(0)->Setup(Vector3(HALFSIZEX, 580, 0), 200, 100,
			[&]() {
				Plain::pMainPlain->Show(0); 
				if (Plain::pMainPlain->iNowRender == 0)
					bScoreRender = true;
				else
					bScoreRender = false;
			}, GETTEXTURE("RANKING_BTN"));

		InstanceEx(Button)(0)->Setup(Vector3(1130, 350, 0), 200, 100,
			[&]() { Plain::pMainPlain->Show(2); bScoreRender = false; }, GETTEXTURE("INFO_BTN"));

		InstanceEx(Button)(0)->Setup(Vector3(1130, 500, 0), 200, 100,
			[&]() { Plain::pMainPlain->Show(1); bScoreRender = false; }, GETTEXTURE("HOWTO_BTN"));

		InstanceEx(Button)(0)->Setup(Vector3(1130, 650, 0), 200, 100,
			[&]() { Plain::pMainPlain->Show(-1); bScoreRender = false; }, GETTEXTURE("CREDIT_BTN"));

		InstanceEx(Button)(0)->Setup(Vector3(1200, 80, 0), 200, 100,
			[]() { PostQuitMessage(0); }, GETTEXTURE("EXIT_BTN"));
		});


	ScoreAdmin scoreAdmin;

	scoreAdmin.FileInput("./RS/DATA/score.txt");
	scoreAdmin.sort();

	int i = 0;
	for (auto iter : scoreAdmin.GetList())
	{
		iTop3Score[i] = iter;
		if (i++ > 2)
			break;
	}
	
	pNumber = new Number;

	bScoreRender = false;
}

void TitleScene::Update(float dt)
{
}

void TitleScene::Render()
{
	if (bScoreRender)
		ScoreRender();
}

void TitleScene::Destroy()
{
	SOUND.Stop("BG");
	SAFE_DELETE(pNumber);
}

void TitleScene::Load()
{
	ADDTEXTURE("START_BTN", "./RS/UI/BUTTON/S(%d).png", 2);
	ADDTEXTURE("INFO_BTN", "./RS/UI/BUTTON/I(%d).png", 2);
	ADDTEXTURE("RANKING_BTN", "./RS/UI/BUTTON/R(%d).png", 2);
	ADDTEXTURE("CREDIT_BTN", "./RS/UI/BUTTON/C(%d).png", 2);
	ADDTEXTURE("EXIT_BTN", "./RS/UI/BUTTON/E(%d).png", 2);
	ADDTEXTURE("HOWTO_BTN", "./RS/UI/BUTTON/H(%d).png", 2);

	ADDTEXTURE("TITLE", "./RS/UI/TITLE/TITLE.png");
	ADDTEXTURE("BG", "./RS/MAP/TITLE/BG.png");
	ADDTEXTURE("GRESS", "./RS/MAP/TITLE/GRESS.png");
	ADDTEXTURE("CLOUD", "./RS/MAP/TITLE/C(%d).png", 2);
	ADDTEXTURE("ENEMY", "./RS/MAP/TITLE/ENE(%d).png", 3);
	ADDTEXTURE("EXPLODE", "./RS/MAP/TITLE/EXP(%d).png", 6);
	ADDTEXTURE("TANK", "./RS/MAP/TITLE/T(%d).png", 2);

	ADDTEXTURE("BLACK", "./RS/UI/BLACK.png");

	ADDTEXTURE("PLAINS", "./RS/UI/TITLE/(%d).png", 3);

	SOUND.Create("BG", L"./RS/SOUND/(2).wav");
	SOUND.Create("EXPLODE1", L"./RS/SOUND/E(1).wav");
	SOUND.Create("EXPLODE2", L"./RS/SOUND/E(2).wav");
}

void TitleScene::ScoreRender()
{
	RESOURCE.SetRenderType(SCREEN);

	pNumber->Draw(iTop3Score[0], v3Center + Vector3(-50, 0, 0), 1.0, -3);
	pNumber->Draw(iTop3Score[1], v3Center + Vector3(-255, 85, 0), 1.0, -3);
	pNumber->Draw(iTop3Score[2], v3Center + Vector3(170, 140, 0), 1.0, -3);
}
