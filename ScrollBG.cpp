#include "DXUT.h"
#include "ScrollBG.h"


ScrollBG::ScrollBG()
{
}


ScrollBG::~ScrollBG()
{
}

void ScrollBG::Init()
{
	AC(Transform);

	iScroll = 0;
	fSpeed = 0;
	fWidth = 0;
	fHeight = 0;
}

void ScrollBG::Update(float dt)
{
	iScroll -= dt * fSpeed;

	index[0] = (int)iScroll % (int)fWidth + transform->vPosition.x;
	index[1] = (int)iScroll % (int)fWidth + transform->vPosition.x + (int)fWidth;

	iCameraHeight = CAMERA.GetPosition().y - HALFSIZEY;
}

void ScrollBG::Render()
{
	RESOURCE.SetRenderType(SCREEN);

	RESOURCE.ApplyWorldTransform(Vector3(index[0], transform->vPosition.y - iCameraHeight, 0), transform->vScale, transform->fRot);
	RESOURCE.Draw((*pTex)(0), Vector3(0, 0, 0), 0xffffffff);

	RESOURCE.ApplyWorldTransform(Vector3(index[1], transform->vPosition.y - iCameraHeight, 0), transform->vScale, transform->fRot);
	RESOURCE.Draw((*pTex)(0), Vector3(0, 0, 0), 0xffffffff);
}

void ScrollBG::Destroy()
{
}

void ScrollBG::Setup(Texture * pTex, Vector3 pos, float speed)
{
	ScrollBG::pTex = pTex;

	transform->vPosition = pos;
	fSpeed = speed;

	fWidth = (*pTex)(0)->tInfo.Width;
	fHeight = (*pTex)(0)->tInfo.Height;
}

void ScrollBG::Setup(RsKey key, Vector3 pos, float speed)
{
	Setup(GETTEXTURE(key), pos, speed);
}
