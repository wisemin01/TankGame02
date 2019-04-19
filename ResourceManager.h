#pragma once
#include "Singleton.h"

class Texture;
class ResourceManager :
	public Singleton<ResourceManager>
{
private:
	map<string, Texture*> mapTexture;
	LPD3DXSPRITE pSprite;

	RENDER_TYPE eRenderType;

public:
	ResourceManager();
	virtual ~ResourceManager();

	Texture* AddTexture(RsKey key, RsKey path, int count = 0);
	Texture* GetTexture(RsKey key, int count = -1);

	Texture* AddStateTexture(RsKey key, RsKey path, int state, int frameCnt);

	void Draw(Texture* pTex, Vector3 vCenter, DWORD dwColor);
	void RectDraw(Texture* pTex, Vector3 vCenter, const RECT& rc, DWORD dwColor);
	void ApplyDraw(Texture* pTex, Vector3 pos, DWORD dwColor);

	void ApplyWorldTransform(const Vector3& pos, const Vector3& scale, float rot);

	inline HRESULT OnBeginDevice() { return pSprite->Begin(D3DXSPRITE_ALPHABLEND); }
	inline void OnEndDevice()	{ pSprite->End(); }

	inline void OnLostDevice()	{ pSprite->OnLostDevice(); }
	inline void OnResetDevice() { pSprite->OnResetDevice(); }

	void TexClear();

	inline void SetRenderType(RENDER_TYPE eRType) { eRenderType = eRType; }
};

#define RESOURCE ResourceManager::GetInstance()