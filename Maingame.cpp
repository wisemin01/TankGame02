#include "DXUT.h"
#include "Maingame.h"

#include "IntroScene.h"
#include "TitleScene.h"
#include "Stage1Scene.h"
#include "Stage2Scene.h"
#include "EndingScene.h"

Maingame::Maingame()
{
}


Maingame::~Maingame()
{
}

void Maingame::Init()
{
	SCENE.AddScene("INTRO", new IntroScene);
	SCENE.AddScene("TITLE", new TitleScene);
	SCENE.AddScene("STAGE1", new Stage1Scene);
	SCENE.AddScene("STAGE2", new Stage2Scene);
	SCENE.AddScene("ENDING", new EndingScene);

	SCENE.ChangeScene("INTRO");
}

void Maingame::Update(float dt)
{
	INPUT.KeyInput();

	COLLISION.CheckOnFrame(dt);
	SCENE.Update(dt);

	CAMERA.Update(dt);

#if(CHEET_ON)
	Cheet();
#endif
}

void Maingame::Render()
{
	if (SUCCEEDED(RESOURCE.OnBeginDevice()))
	{
		SCENE.Render();
	}

	RESOURCE.OnEndDevice();
}

void Maingame::Destroy()
{
	ObjectManager::ReleaseInstance();
	CollisionManager::ReleaseInstance();
	SceneManager::ReleaseInstance();
	ResourceManager::ReleaseInstance();
	InputManager::ReleaseInstance();
	CameraManager::ReleaseInstance();
	SoundManager::ReleaseInstance();
}

void Maingame::OnLost()
{
	RESOURCE.OnLostDevice();
}

void Maingame::OnReset()
{
	RESOURCE.OnResetDevice();
}

void Maingame::Cheet()
{
	if (INPUT.GetInputKeyDown(VK_F4)) SCENE.ChangeScene("INTRO");
	if (INPUT.GetInputKeyDown(VK_F5)) SCENE.ChangeScene("STAGE1");
	if (INPUT.GetInputKeyDown(VK_F6)) SCENE.ChangeScene("STAGE2");
}
