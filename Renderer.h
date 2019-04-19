#pragma once
#include "Component.h"
#include "Frame.h"

class Renderer :
	public Component
{
public:
	Texture * pTex = nullptr;

	D3DXCOLOR tColor = 0xffffffff;

	Vector3 vCenter = v3Zero;
	
	RENDER_TYPE eRenderType = SCROLL;

	Frame tFrame;
public:
	Renderer();
	virtual ~Renderer();

	virtual void Init() override;
	virtual void Update(float dt) override;
	virtual void Render() override;
	virtual void Destroy() override;

	inline void SetTexture(Texture* tex, int count = -1) { pTex = (*tex)(count); SetCenter(0); }
	inline void SetTexture(RsKey key, int count = -1) { pTex = RESOURCE.GetTexture(key, count); SetCenter(0); }

	inline float Width(int cnt = 0) { return (*pTex)(0)->tInfo.Width; }
	inline float Height(int cnt = 0) { return (*pTex)(0)->tInfo.Height; }

	inline void SetCenter(int cnt = 0) { vCenter = Vector3(Width(cnt) / 2.f, Height(cnt) / 2.f, 0); }
};

