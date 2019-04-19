#pragma once
#include "GameObject.h"


class ScrollBG :
	public GameObject
{
public:
	int iScroll;
	float fSpeed;

	float fWidth;
	float fHeight;

	Texture* pTex;

	int index[2];
	int iCameraHeight;

public:
	ScrollBG();
	virtual ~ScrollBG();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(RsKey key, Vector3 pos, float speed);
	void Setup(Texture* pTex, Vector3 pos, float speed);
};

