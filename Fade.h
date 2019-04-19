#pragma once
#include "GameObject.h"



class Fade :
	public GameObject
{
public:
	float fSpeed;

	function<void()> OnAlpha255;
	function<void()> OnAlpha0;

	bool bDown;
	bool bNoneDelete;

	int iCount;
public:
	Fade();
	virtual ~Fade();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(int to_type, int count, float speed, function<void()> on255, function<void()> on0);
};

