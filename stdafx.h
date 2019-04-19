#pragma once

#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <functional>
#include <string>
#include <random>

using namespace std;

enum
{
	WINSIZEX = 1280,
	WINSIZEY = 720,
	WINMODE = FALSE,
	HALFSIZEX = WINSIZEX / 2,
	HALFSIZEY = WINSIZEY / 2
};


#if DEBUG
#define CONSOLE_LOG(log) { std::cout << log << std::endl; }
#define BREAK_ALLOC 0
#else
#define CONSOLE_LOG(log)
#define BREAK_ALLOC 0
#endif
#define CHEET_ON TRUE


#define NOWTIME timeGetTime()
#define DELTIME DXUTGetElapsedTime()
#define DEVICE  DXUTGetD3D9Device()

#define KEY_MAX (256)

#define AC(c) AddComponent<c>()
#define GC(c) GetComponent<c>()

#define ADDTEXTURE	RESOURCE.AddTexture
#define ADDSTATETEX RESOURCE.AddStateTexture
#define GETTEXTURE	RESOURCE.GetTexture

using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;

using RsKey = const string&;

using ObjectId = int;

const Vector3 v3Center(HALFSIZEX, HALFSIZEY, 0);
const Vector2 v2Center(HALFSIZEX, HALFSIZEY);

const Vector3 v3Zero(0, 0, 0);
const Vector2 v2Zero(0, 0);

const Vector3 v3Normal(1.0f, 1.0f, 1.0f);
const Vector2 v2Normal(1.0f, 1.0f);

template <typename T>
T GetRandom(T min, T max)
{
	random_device rn;
	mt19937_64 rnd(rn());

	uniform_int_distribution<T> range(min, max);

	return range(rnd);
}

template <>
float GetRandom<float>(float min, float max);


template <typename T>
void Lerp(T* target, const T& start, const T& end, float speed)
{
	*target = start + (end - start) * speed;
}

VOID ResizeArray(int **array, int size);

#include "Enum.h"
#include "Texture.h"
#include "Manager.h"
#include "DelayMsg.h"

#include "Transform.h"
#include "Renderer.h"
#include "Rigidbody.h"
#include "Collider.h"
#include "Life.h"

#include "Number.h"

template<>
inline float GetRandom(float min, float max)
{
	random_device rn;
	mt19937_64 rnd(rn());

	uniform_real_distribution<float> range(min, max);

	return range(rnd);
}
