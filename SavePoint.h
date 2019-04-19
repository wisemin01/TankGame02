#pragma once
#include "GameObject.h"
class SavePoint :
	public GameObject
{
	bool bPassed;
public:
	SavePoint();
	virtual ~SavePoint();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Place(Vector3 pos);

public:
	static void CreateSavePoints(int xIndex, int count, int layer);
};

