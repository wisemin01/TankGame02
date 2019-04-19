#pragma once
#include "GameObject.h"

class Button :
	public GameObject
{
	enum
	{
		NONE,
		ON_MOUSE
	};
public:
	RECT_F rcRange;

	int eType;

	function<void()> pOnFunc;

public:
	Button();
	virtual ~Button();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(Vector3 pos, float width, float height, function<void()> func, Texture* pTex);

private:
	bool GetCollision(RENDER_TYPE type);
};

