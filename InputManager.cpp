#include "DXUT.h"
#include "InputManager.h"


InputManager::InputManager()
{
	memset(bCur, 0, sizeof(bCur));
}


InputManager::~InputManager()
{
}

void InputManager::KeyInput()
{
	for (int i = 0; i < KEY_MAX; i++)
	{
		bOld[i] = bCur[i];
		bCur[i] = (bool)(GetAsyncKeyState(i));
	}
}

bool InputManager::GetInputKeyDown(int iKey)
{
	return !bOld[iKey] && bCur[iKey];
}

bool InputManager::GetInputKeyUp(int iKey)
{
	return bOld[iKey] && !bCur[iKey];
}

bool InputManager::GetInputKeyPress(int iKey)
{
	return bOld[iKey] && bCur[iKey];
}

Vector3 InputManager::GetMouse()
{
	POINT pt;
	GetCursorPos(&pt);

	ScreenToClient(DXUTGetHWND(), &pt);

	return Vector3((float)pt.x, (float)pt.y, 0.0f);
}
