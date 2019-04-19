#pragma once
#include "GameObject.h"
class StoneObstacle :
	public GameObject
{
public:
	StoneObstacle();
	virtual ~StoneObstacle();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(Vector3 position, Vector3 size = v3Normal, float fRot = 0);
	
	void OnCollision(Collider* other);
	void OnDeath();
};

