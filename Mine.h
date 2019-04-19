#pragma once
#include "GameObject.h"
class Mine :
	public GameObject
{
public:
	bool bDropMine;
public:
	Mine();
	virtual ~Mine();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Place(Vector3 pos);
	void Drop(Vector3 pos);

	void OnDeath();

	void OnCollision(Collider* other);

public:
	static void CreateMines(int xIndex, int count, int layer);
};

