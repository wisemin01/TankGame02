#pragma once
#include "Singleton.h"

class InputManager :
	public Singleton<InputManager>
{
private:
	bool bOld[KEY_MAX];
	bool bCur[KEY_MAX];
public:
	InputManager();
	virtual ~InputManager();

	void KeyInput();

	bool GetInputKeyDown(int iKey);
	bool GetInputKeyUp(int iKey);
	bool GetInputKeyPress(int iKey);

	Vector3 GetMouse();
};

#define INPUT InputManager::GetInstance()

#define KEY_DOWN(k)		INPUT.GetInputKeyDown(k)
#define KEY_UP(k)		INPUT.GetInputKeyUp(k)
#define KEY_PRESS(k)	INPUT.GetInputKeyPress(k)