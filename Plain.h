#pragma once
#include "GameObject.h"


class Plain :
	public GameObject
{
public:
	enum { NONE_SELECT = -1 };
	int iNowRender;
public:
	Plain();
	virtual ~Plain();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Show(int renderIndex);

	void Setup(Vector3 pos, Texture* multiTex);
	void SetMain();

public:
	static Plain * pMainPlain;
};

