#pragma once
#include "Component.h"

struct RECT_F
{
	float left, top, right, bottom;
};

enum COLLIDER_GET_TYPE
{
	WORLD,
	AREA
};

// INTERFACE FUNC

VOID	SetRect_F		(RECT_F* pRect, float left, float top, float right, float bottom);
BOOL	IntersectRect_F	(const RECT_F* pRc1, const RECT_F* pRc2);
BOOL	IntersectRectToVector_F(const RECT_F* pRc, const Vector3* pPt);
RECT_F	ApplyRect_F		(const RECT_F* pRect, const Vector3* pPiv, const Vector3* pSca);

class GameObject;
class Collider :
	public Component
{
public:
	RECT_F rcRange;

	std::function<void(Collider*)> pOnFunc;
	Vector3 vOffset = v3Zero;

	bool bTrigger = false;
public:
	Collider() {}
	virtual ~Collider() {}

	virtual void Init() override;
	virtual void Destroy() override;

	float Width();
	float Height(); 

	inline RECT_F operator()(COLLIDER_GET_TYPE type)
	{
		return type == WORLD ? GetWorldRange() : GetRange();
	}

	RECT_F GetRange() { return rcRange; }
	RECT_F GetWorldRange();

	void OnCollision(Collider* other) { pOnFunc(other); }

	void Create(float width, float height, function<void(Collider*)> func);
	void Create(float l, float t, float r, float b, function<void(Collider*)> func);
	void CreateAsTexture(Texture* text, function<void(Collider*)> func);

	void ReCreateAsTexture(Texture* text);

	void Register	()	{ COLLISION.Register(this);		}
	void UnRegister	()	{ COLLISION.UnRegister(this);	}
};
