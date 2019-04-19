#pragma once
#include "GameObject.h"
class Ground :
	public GameObject
{
public:
	Ground();
	virtual ~Ground();

	virtual void Init() override;

	void Setup(Texture* pTex, Vector3 pos);
	void SetupCenter(Texture* pTex, Vector3 pos);

public:
	static void CreateBackGround(Texture* pTex, HeightMap* pHeightMap, int layer = 0, Vector3 vPivot = v3Zero);
};

