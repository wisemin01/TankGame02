#pragma once

class Scene
{
protected:

public:
	Scene();
	virtual ~Scene();

	virtual void Init() PURE;
	virtual void Update(float dt) PURE;
	virtual void Render() PURE;
	virtual void Destroy() PURE;

	virtual void Load() PURE;
};

