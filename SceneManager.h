#pragma once
#include "Singleton.h"


class Scene;
class SceneManager :
	public Singleton<SceneManager>
{
private:
	map<string, Scene*> mapScene;

	Scene* pNowScene  = nullptr;
	Scene* pNextScene = nullptr;

	string sNowScene;
public:
	SceneManager();
	virtual ~SceneManager();

	Scene* AddScene(RsKey key, Scene* pScene);
	Scene* ChangeScene(RsKey key);

	void Update(float dt);
	void Render();

	void SceneClear();

	string GetSceneName() { return sNowScene; }
};

#define SCENE SceneManager::GetInstance()