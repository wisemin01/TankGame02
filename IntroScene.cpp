#include "DXUT.h"
#include "IntroScene.h"

#include "GameObject.h"

#include "Fade.h"

IntroScene::IntroScene()
{
}


IntroScene::~IntroScene()
{
}

void IntroScene::Init()
{
	pTitle = InstanceEx(GameObject)(0, true, true);

	pTitle->AC(Transform)->vPosition = v3Center;
	pTitle->AC(Renderer)->SetTexture("INTRO");
	pTitle->renderer->tFrame(0, 19, 0.5f);
	pTitle->renderer->eRenderType = SCREEN;

	SOUND.Play("BG", 1);
}

void IntroScene::Update(float dt)
{
	if (pTitle->renderer->tFrame.cur == 19 ||
		INPUT.GetInputKeyDown(VK_LBUTTON))
	{
		InstanceEx(Fade)(100)->Setup(255, 1, 3, []() {SCENE.ChangeScene("TITLE"); }, []() {});
	}
}

void IntroScene::Render()
{
}

void IntroScene::Destroy()
{
	SOUND.Stop("BG");
}

void IntroScene::Load()
{
	ADDTEXTURE("INTRO", "./RS/MAP/INTRO/(%d).png", 20);
	ADDTEXTURE("BLACK", "./RS/UI/BLACK.png");

	SOUND.Create("BG", L"./RS/SOUND/(1).wav");
}
