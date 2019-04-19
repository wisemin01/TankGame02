#pragma once
#include "Singleton.h"

class GameObject;
struct RECT_F;

struct CameraShake
{	
	float fShakeDelay;
	float fShakeFrameSkip;
	float fShakePower;

	bool operator <(const CameraShake& other)
	{
		return (fShakeDelay * fShakePower) < (other.fShakeDelay * other.fShakePower);
	}
};

class CameraManager :
	public Singleton<CameraManager>
{
	friend class ResourceManager;
private:
	CameraShake tShakeInfo;
	bool bShakeOn;

	Vector3 vCameraPostion;
	Vector3 vOffset;

	GameObject* pTarget;

	RECT_F* pRange;

public:
	CameraManager();
	virtual ~CameraManager();

	void InitCamera(Vector3 camPos = v3Center);

	void Update(float dt);

	void ApplyToWorldTransform(Vector3& refPosition);
	void ApplyToScreenTransform(Vector3& refPosition);

	inline Vector3 GetPosition() { return vCameraPostion; }
	inline void SetPosition(Vector3 pos) { vCameraPostion = pos; }

	void SetTarget(GameObject* pTarget);
	void SetOffset(float x, float y);

	void UseRange(float l, float t, float r, float b);
	void UnuseRange();

	void Shake(float delay, float power);
};

#define CAMERA CameraManager::GetInstance()

#define APPLY_TO_WORLD(v)	CAMERA.ApplyToWorldTransform(v)
#define APPLY_TO_SCREEN(v)	CAMERA.ApplyToScreenTransform(v)

#define CAMERA_POS CAMERA.GetPosition()