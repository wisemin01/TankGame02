#pragma once
#include "GameObject.h"


class Item :
	public GameObject
{
public:
	ITEM_TYPE eType;
public:
	Item();
	virtual ~Item();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;
	
	void RandomSetup(Vector3 pos);
};

