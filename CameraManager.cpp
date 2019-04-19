#include "DXUT.h"
#include "CameraManager.h"

#include "GameObject.h"
#include "Transform.h"

#define SHAKE_ATN (0.99f)

CameraManager::CameraManager()
	:	pTarget(nullptr),
		pRange(nullptr),
		vOffset(0,0,0),
		bShakeOn(false)
{
	tShakeInfo = { 0,0,0 };
}


CameraManager::~CameraManager()
{
	UnuseRange();
}

void CameraManager::InitCamera(Vector3 camPos)
{
	UnuseRange();

	vCameraPostion = camPos;
	pTarget = nullptr;
	pRange  = nullptr;
	vOffset = v3Zero;
	bShakeOn = false;
}

void CameraManager::Update(float dt)
{
	if (bShakeOn)
	{
		if (tShakeInfo.fShakeFrameSkip <= tShakeInfo.fShakeDelay)
		{
			vCameraPostion += Vector3(GetRandom<int>(-tShakeInfo.fShakePower, tShakeInfo.fShakePower),
				GetRandom<int>(-tShakeInfo.fShakePower, tShakeInfo.fShakePower), 0);

			tShakeInfo.fShakeFrameSkip += dt;
			tShakeInfo.fShakePower *= SHAKE_ATN;
		}
		else
		{
			bShakeOn = false;
		}
	}
	else
	{
		tShakeInfo.fShakeFrameSkip = 0;
		tShakeInfo.fShakeDelay = 0;
		tShakeInfo.fShakePower = 0;
	}

	if (pTarget)
	{
		Vector3 vEnd = pTarget->transform->vPosition + vOffset - v3Center;

		// NONE LERP : vCameraPostion = vEnd;
		Lerp(&vCameraPostion, vCameraPostion, vEnd, dt * 20);
	}

	if (pRange)
	{
		if (vCameraPostion.x <= pRange->left)
			vCameraPostion.x = pRange->left;

		if (vCameraPostion.x >= pRange->right)
			vCameraPostion.x = pRange->right;

		if (vCameraPostion.y <= pRange->top)
			vCameraPostion.y = pRange->top;

		if (vCameraPostion.y >= pRange->bottom)
			vCameraPostion.y = pRange->bottom;
	}
}

void CameraManager::ApplyToWorldTransform(Vector3 & refPosition)
{
	refPosition += vCameraPostion;
}

void CameraManager::ApplyToScreenTransform(Vector3 & refPosition)
{
	refPosition -= vCameraPostion;
}

void CameraManager::SetTarget(GameObject * pTarget)
{
	CameraManager::pTarget = pTarget;
}

void CameraManager::SetOffset(float x, float y)
{
	vOffset = Vector3(x, y, 0);
}

void CameraManager::UseRange(float l, float t, float r, float b)
{
	if (!pRange)
		pRange = new RECT_F;

	SetRect_F(pRange, l, t, r, b);
}

void CameraManager::UnuseRange()
{
	SAFE_DELETE(pRange);
}

void CameraManager::Shake(float delay, float power)
{
	CameraShake s = { delay, 0, power };

	if (tShakeInfo < s)
	{
		tShakeInfo = s;
		bShakeOn = true;
	}
}
