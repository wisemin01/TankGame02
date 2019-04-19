#include "DXUT.h"
#include "ResourceManager.h"

#include "SingleTexture.h"
#include "MultiTexture.h"
#include "StateTexture.h"

ResourceManager::ResourceManager()
	: pSprite(nullptr)
{
	D3DXCreateSprite(DEVICE, &pSprite);
}


ResourceManager::~ResourceManager()
{
	TexClear();

	SAFE_RELEASE(pSprite);
}

Texture * ResourceManager::AddTexture(RsKey key, RsKey path, int count)
{
	auto find = mapTexture.find(key);

	if (find == mapTexture.end())
	{
		Texture* tex;

		if (count == 0)
			tex = new SingleTexture;
		else
			tex = new MultiTexture;

		tex->AddTexture(path, count);

		mapTexture.insert(make_pair(key, tex));

		return tex;
	}

	return find->second;
}

Texture * ResourceManager::GetTexture(RsKey key, int count)
{
	auto find = mapTexture.find(key);

	if (find == mapTexture.end())
	{
		return nullptr;
	}

	return find->second->GetTexture(count);
}

Texture * ResourceManager::AddStateTexture(RsKey key, RsKey path, int state, int frameCnt)
{
	auto find = mapTexture.find(key);

	if (find == mapTexture.end())
	{
		Texture* tex = new StateTexture;

		StateTexture::iStateFrameCount = frameCnt;
		tex->AddTexture(path, state);

		mapTexture.insert(make_pair(key, tex));

		return tex;
	}

	return find->second;
}

void ResourceManager::Draw(Texture * pTex, Vector3 vCenter, DWORD dwColor)
{
	pSprite->Draw(pTex->pTex, NULL, &vCenter, NULL, dwColor);
}

void ResourceManager::RectDraw(Texture * pTex, Vector3 vCenter, const RECT & rc, DWORD dwColor)
{
	pSprite->Draw(pTex->pTex, &rc, &vCenter, NULL, dwColor);
}

void ResourceManager::ApplyDraw(Texture * pTex, Vector3 pos, DWORD dwColor)
{
	ApplyWorldTransform(pos, v3Normal, 0);
	Draw(pTex, Vector3(pTex->tInfo.Width / 2.f, pTex->tInfo.Height / 2.f, 0), dwColor);
}

void ResourceManager::ApplyWorldTransform(const Vector3 & pos, const Vector3 & scale, float rot)
{
	D3DXMATRIX matWorld;
	D3DXMATRIX s, r, t;

	Vector3 renderPos;

	if (eRenderType == SCREEN)
		renderPos = pos;
	else if (eRenderType == SCROLL)
		renderPos = pos - CAMERA.vCameraPostion;

	D3DXMatrixScaling(&s, scale.x, scale.y, scale.z);
	D3DXMatrixRotationZ(&r, rot);
	D3DXMatrixTranslation(&t, renderPos.x, renderPos.y, renderPos.z);

	matWorld = s * r * t;

	pSprite->SetTransform(&matWorld);
}

void ResourceManager::TexClear()
{
	for (auto iter : mapTexture)
	{
		SAFE_DELETE(iter.second);
	}
	mapTexture.clear();
}
