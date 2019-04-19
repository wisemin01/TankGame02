#include "DXUT.h"
#include "Collider.h"
#include "GameObject.h"

VOID SetRect_F(RECT_F * pRect, float left, float top, float right, float bottom)
{
	pRect->left = left;
	pRect->top = top;
	pRect->right = right;
	pRect->bottom = bottom;
}

BOOL IntersectRect_F(const RECT_F * pRc1, const RECT_F * pRc2)
{
	if (pRc1->left < pRc2->right &&
		pRc1->top < pRc2->bottom &&
		pRc1->right > pRc2->left &&
		pRc1->bottom > pRc2->top)
		return true;
	else
		return false;
}

BOOL IntersectRectToVector_F(const RECT_F * pRc, const Vector3 * pPt)
{
	if (pRc->left < pPt->x &&
		pRc->right > pPt->x &&
		pRc->top < pPt->y &&
		pRc->bottom > pPt->y)
		return true;
	else return false;
}

RECT_F ApplyRect_F(const RECT_F * pRect, const Vector3 * pPiv, const Vector3* pSca)
{
	return { pRect->left * pSca->x + pPiv->x,
			 pRect->top * pSca->y + pPiv->y,
			 pRect->right * pSca->x + pPiv->x,
			 pRect->bottom * pSca->y + pPiv->y };
}



void Collider::Init()
{
	gameObject->collider = this;
}

void Collider::Destroy()
{
	COLLISION.UnRegister(this);

	if (gameObject->collider == this)
		gameObject->collider = nullptr;
}

float Collider::Width()
{
	return abs(rcRange.right - rcRange.left) * gameObject->transform->vScale.x;
}

float Collider::Height()
{
	return abs(rcRange.bottom - rcRange.top) * gameObject->transform->vScale.y;
}

RECT_F Collider::GetWorldRange()
{
	return ApplyRect_F(&rcRange, &(gameObject->transform->vPosition + vOffset), &gameObject->transform->vScale);
}

void Collider::Create(float width, float height, function<void(Collider*)> func)
{
	rcRange.left = -width / 2.f;
	rcRange.right = width / 2.f;
	rcRange.top = -height / 2.f;
	rcRange.bottom = height / 2.f;

	pOnFunc = func;

	COLLISION.Register(this);
}

void Collider::Create(float l, float t, float r, float b, function<void(Collider*)> func)
{
	rcRange.left = l;
	rcRange.right = r;
	rcRange.top = t;
	rcRange.bottom = b;

	pOnFunc = func;

	COLLISION.Register(this);
}

void Collider::CreateAsTexture(Texture * text, function<void(Collider*)> func)
{
	float w = (*text)(0)->tInfo.Width;
	float h = (*text)(0)->tInfo.Height;

	rcRange.left = -w / 2.f;
	rcRange.right = w / 2.f;
	rcRange.top = -h / 2.f;
	rcRange.bottom = h / 2.f;

	pOnFunc = func;

	COLLISION.Register(this);
}

void Collider::ReCreateAsTexture(Texture * text)
{
	float w = (*text)(0)->tInfo.Width;
	float h = (*text)(0)->tInfo.Height;

	rcRange.left = -w / 2.f;
	rcRange.right = w / 2.f;
	rcRange.top = -h / 2.f;
	rcRange.bottom = h / 2.f;
}
