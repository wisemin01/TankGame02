#pragma once
#include "GameObject.h"

struct WaterPoint
	: public Vector2
{
	float mass = 1.0f;
	Vector2 speed = v2Zero;

	WaterPoint(float x, float y) : Vector2(x, y) {}
};

class Water :
	public GameObject
{
public:
	int iWaterCount;
	
	float fBlockWidth;
	float fBlockHeight;

	float fMapWidth;
	float fMapHeight;

	float fSinOffset;

	std::vector<WaterPoint> vecPoints;
	
	Texture* pWaterTex;
public:
	Water();
	virtual ~Water();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(Vector3 leftPivot, int count);

	void Impress(Vector3 position, float width);

	void OnCollision(Collider* other);

private:
	void ProcessWater(int iteration, float springConstant, float baseLine, float damping);
};

