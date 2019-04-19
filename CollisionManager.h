#pragma once
#include "Singleton.h"

class PixelColliderModule;
class Collider;

class CollisionManager :
	public Singleton<CollisionManager>
{
private:
	list<Collider*> listCollider;

	PixelColliderModule* pPixelModule;
public:
	CollisionManager();
	virtual ~CollisionManager();

	void CheckOnFrame(float dt);

	inline void Register(Collider* col) { listCollider.push_back(col); }
	inline void UnRegister(Collider* col) { listCollider.remove(col); }

	inline void Clear() { listCollider.clear(); }

	PixelColliderModule* GetPixelModule() { return pPixelModule; }
};

struct HeightMap
{
	int* pMap = nullptr;
	int iHeightMapSize = 0;
	int iHeightMapCount = 0;
	int iRandomMapKind[64];
};

class PixelColliderModule
{
private:
	HeightMap * pHeightMap = nullptr;
public:
	PixelColliderModule();
	virtual ~PixelColliderModule();

	HRESULT CreateSingleHeightMap(Texture* pTex);
	HRESULT CreateRandomMultiHeightMap(Texture* pMultiTex, int iMapCount);

	HRESULT DestroyHeightMap();

	VOID	AssignHeightModule(DWORD*& pDwList, int*& pMap, int startPoint, int endPoint, int mapHeight);

	HRESULT RegisterHeightMap(HeightMap* pHeightMap);
	HRESULT UnRegisterHeightMap();

	HeightMap* GetHeightMap() { return pHeightMap; }

	BOOL GetCollisionCheck(const Vector3* vPos);
	INT	 GetHeightAsHeightMap(int sector);
	BOOL InspecRange(int sector);

	BOOL GetRightInspec(Vector3 sector, float half_width, float up_height);
	BOOL GetLeftInspec(Vector3 sector, float half_width, float up_height);

public:
	// CALC FUNC
	Vector3 GetLineVectorAsHeightMap(Vector3 sector, float width);
	void	GetCalculatePushVector(Vector3* pOutPush, Vector3 pos, float width);
	void	GetCalculateLineRotation(Vector3 sector, float width, float* pOutRot, float dt);

public:
	const DWORD dwFloor = D3DCOLOR_ARGB(255, 0, 0, 0);
};

#define COLLISION CollisionManager::GetInstance()