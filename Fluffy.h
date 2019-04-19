#pragma once
#include "GameObject.h"
class Fluffy :
	public GameObject
{
public:
	Vector3 vEnd;

	float fSpeed;
	float fHeight;

	bool bUp;
	bool bEnd;
	bool bFluffy;
	bool bLerp;
public:
	Fluffy();
	virtual ~Fluffy();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(RsKey key, Vector3 startPos, Vector3 targetPos, float speed, float height, bool bFluffy = true);
	void Setup(Texture* pTex, Vector3 startPos, Vector3 targetPos, float speed, float height, bool bFluffy = true);
};

