#include "DXUT.h"
#include "SceneManager.h"

#include "Scene.h"

SceneManager::SceneManager()
	:	pNowScene(nullptr),
		pNextScene(nullptr)
{
}


SceneManager::~SceneManager()
{
	SceneClear();

	pNowScene = nullptr;
	pNextScene = nullptr;
}

Scene * SceneManager::AddScene(RsKey key, Scene * pScene)
{
	auto find = mapScene.find(key);

	if (find == mapScene.end())
	{
		mapScene.insert(make_pair(key, pScene));

		return pScene;
	}
	else
	{
		pScene->Destroy();
		SAFE_DELETE(pScene);
	}

	return nullptr;
}

Scene * SceneManager::ChangeScene(RsKey key)
{
	auto find = mapScene.find(key);

	if (find != mapScene.end())
	{
		pNextScene = find->second;
		sNowScene = find->first;
		return pNextScene;
	}

	return nullptr;
}

void SceneManager::Update(float dt)
{
	if (pNextScene)
	{
		if (pNowScene)
		{
			pNowScene->Destroy();
			pNowScene = nullptr;

			OBJECT.ClearObject();
			RESOURCE.TexClear();
			SOUND.Clear();

			DelayMsg::ReleaseMeseages();
		}

		pNextScene->Load();
		pNextScene->Init();
		pNowScene = pNextScene;
		pNextScene = nullptr;
	}

	if (pNowScene) {
		DelayMsg::MessageLoop(dt);

		pNowScene->Update(dt);
		OBJECT.Update(dt);
	}
}

void SceneManager::Render()
{
	if (pNowScene) {
		OBJECT.Render();
		pNowScene->Render();
	}
}

void SceneManager::SceneClear()
{
	DelayMsg::ReleaseMeseages();

	if (pNowScene)
		pNowScene->Destroy();

	for (auto iter : mapScene)
	{
		SAFE_DELETE(iter.second);
	}

	mapScene.clear();
}
