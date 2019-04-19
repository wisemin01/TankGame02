#pragma once
#include "GameObject.h"
class Meteor :
	public GameObject
{
	Texture* pWarning;

	bool bRenderWarning;
	Vector3 vWarningPos;

	float fDirX;

	float fTimeScale;
public:
	Meteor();
	virtual ~Meteor();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	void Setup(Vector3 pos, Vector3 size);

	void OnCollision(Collider* other);

	void Drop();
};

