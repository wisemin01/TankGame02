#include "DXUT.h"
#include "CollisionManager.h"

#include "Collider.h"

#define MAP_HEIGHT 1000
#define UP_HEIGHT 20

CollisionManager::CollisionManager()
{
	pPixelModule = new PixelColliderModule;
}


CollisionManager::~CollisionManager()
{
	listCollider.clear();
	SAFE_DELETE(pPixelModule);
}

void CollisionManager::CheckOnFrame(float dt)
{ 
	if (listCollider.size() < 2)
		return;

	auto end = std::prev(listCollider.end(), 1);

	for (auto col1 = listCollider.begin(); col1 != end; col1++)
	{
		for (auto col2 = std::next(col1, 1); col2 != listCollider.end(); col2++)
		{
			if ((*col1)->gameObject == (*col2)->gameObject)
				continue;

			RECT_F *rc1 = &(*col1)->GetWorldRange();
			RECT_F *rc2 = &(*col2)->GetWorldRange();

			if (IntersectRect_F(rc1, rc2))
			{
				(*col1)->OnCollision(*col2);
				(*col2)->OnCollision(*col1);
			}
		}
	}
}

PixelColliderModule::PixelColliderModule()
{
	pHeightMap = nullptr;
}

PixelColliderModule::~PixelColliderModule()
{
	if (pHeightMap)
		DestroyHeightMap();
}

HRESULT PixelColliderModule::CreateSingleHeightMap(Texture * pTex)
{
	IDirect3DTexture9*	lpTexture	= pTex->pTex;
	D3DXIMAGE_INFO		tInfo		= pTex->tInfo;
	D3DLOCKED_RECT		lockRect;
	DWORD*							pDwordList;

	FLOAT				width  = tInfo.Width;
	FLOAT				height = tInfo.Height;

	if (FAILED(lpTexture->LockRect(0, &lockRect, NULL, D3DLOCK_DISCARD)))
	{
		lpTexture->UnlockRect(0);
		return E_FAIL;
	}

	pDwordList = reinterpret_cast<DWORD*>(lockRect.pBits);

	pHeightMap = new HeightMap;
	pHeightMap->pMap = new int[width];
	pHeightMap->iHeightMapSize = width;
	pHeightMap->iHeightMapCount = 1;
	
	AssignHeightModule(pDwordList, pHeightMap->pMap, 0, width, height);

	return S_OK;
}

HRESULT PixelColliderModule::CreateRandomMultiHeightMap(Texture * pMultiTex, int iMapCount)
{
	INT iMapKind = pMultiTex->Size();

	D3DXIMAGE_INFO		tInfo = (*pMultiTex)(0)->tInfo;

	FLOAT				width = tInfo.Width;
	FLOAT				height = tInfo.Height;

	pHeightMap = new HeightMap;

	pHeightMap->iHeightMapSize = width * iMapCount;
	pHeightMap->pMap = new int[width * iMapCount];
	pHeightMap->iHeightMapCount = iMapCount;

	for (int i = 0; i < iMapCount; i++)
	{
		pHeightMap->iRandomMapKind[i] = GetRandom<int>(0, iMapKind - 1);
	}

	for (int i = 0; i < iMapCount; i++)
	{
		IDirect3DTexture9*	lpThisTex = pMultiTex->GetTexture(pHeightMap->iRandomMapKind[i])->pTex;

		D3DLOCKED_RECT		lockRect;
		DWORD*				pDwordList;

		if (FAILED(lpThisTex->LockRect(0, &lockRect, NULL, D3DLOCK_DISCARD)))
		{
			lpThisTex->UnlockRect(0);
			return E_FAIL;
		}

		pDwordList = reinterpret_cast<DWORD*>(lockRect.pBits);

		AssignHeightModule(pDwordList, pHeightMap->pMap, i*width, (i + 1)*width, height);
		lpThisTex->UnlockRect(0);
	}

	return S_OK;
}

HRESULT PixelColliderModule::DestroyHeightMap()
{
	if (pHeightMap)
	{
		SAFE_DELETE_ARRAY(pHeightMap->pMap);
		delete pHeightMap;
		pHeightMap = nullptr;
	}

	return S_OK;
}

void PixelColliderModule::AssignHeightModule(DWORD *& pDwList, int *& pMap, int startPoint, int endPoint, int mapHeight)
{
	FLOAT width = abs(endPoint - startPoint);

	for (int i = startPoint; i < endPoint; i++)
	{
		pMap[i] = MAP_HEIGHT;
	}

	for (int x = startPoint; x < endPoint; x++)
	{
		for (int y = 0; y < mapHeight; y++)
		{
			DWORD color = pDwList[(int)(y * width + x)];

			if (color == dwFloor)
			{
				pMap[x] = min(pMap[x], y);
			}
		}
	}
}

HRESULT PixelColliderModule::RegisterHeightMap(HeightMap * pHeightMap)
{
	if (PixelColliderModule::pHeightMap == nullptr) {
		PixelColliderModule::pHeightMap = pHeightMap;
		return S_OK;
	}
	return E_FAIL;
}

HRESULT PixelColliderModule::UnRegisterHeightMap()
{
	if (PixelColliderModule::pHeightMap) {
		PixelColliderModule::pHeightMap = nullptr;
		return S_OK;
	}
	return E_FAIL;
}

BOOL PixelColliderModule::GetCollisionCheck(const Vector3 * vPos)
{
	if (InspecRange(vPos->x) == FALSE)
		return FALSE;

	if (pHeightMap->pMap[(INT)vPos->x] <= vPos->y)
	{
		return TRUE;
	}
	else
		return FALSE;
}

INT PixelColliderModule::GetHeightAsHeightMap(int sector)
{
	if (InspecRange(sector) == FALSE)
		return FALSE;

	return pHeightMap->pMap[(INT)sector];
}

BOOL PixelColliderModule::InspecRange(int sector)
{
	if (sector > pHeightMap->iHeightMapSize
		|| sector < 0)
		return FALSE;

	return TRUE;
}

BOOL PixelColliderModule::GetRightInspec(Vector3 sector, float half_width, float up_height)
{
	if (InspecRange(sector.x + half_width) == FALSE
		|| InspecRange(sector.x) == FALSE)
		return FALSE;

	if (sector.y - pHeightMap->pMap[(int)(sector.x + half_width)] >= up_height)
	{
		return true;
	}

	return false;
}

BOOL PixelColliderModule::GetLeftInspec(Vector3 sector, float half_width, float up_height)
{
	if (InspecRange(sector.x - half_width) == FALSE
		|| InspecRange(sector.x) == FALSE)
		return FALSE;

	if (sector.y - pHeightMap->pMap[(int)(sector.x - half_width)] >= up_height)
	{
		return true;
	}

	return false;
}

Vector3 PixelColliderModule::GetLineVectorAsHeightMap(Vector3 sector, float width)
{
	float leftPivot = -width / 2.f;
	float rightPivot = width / 2.f;

	if (!InspecRange(sector.x + leftPivot) ||
		!InspecRange(sector.x + rightPivot))
	{
		return v3Zero;
	}

	Vector3 leftPt, rightPt;

	leftPt	= Vector3(sector.x + leftPivot, pHeightMap->pMap[(int)(sector.x + leftPivot)], 0);
	rightPt = Vector3(sector.x + rightPivot, pHeightMap->pMap[(int)(sector.x + rightPivot)], 0);

	Vector3 vLine = rightPt - leftPt;

	D3DXVec3Normalize(&vLine, &vLine);

	return vLine;
}

void PixelColliderModule::GetCalculatePushVector(Vector3 * pOutPush, Vector3 pos, float width)
{
	Vector3 vLine = GetLineVectorAsHeightMap(pos, width);

	if (vLine == v3Zero || pHeightMap->pMap[(int)pos.x] > pos.y)
	{
		*pOutPush = v3Zero;
		return;
	}

	Vector3 vPush(vLine.y, -vLine.x, 0);

	if (vPush.y > 0)
		vPush *= -1;

	*pOutPush = vPush;
}

void PixelColliderModule::GetCalculateLineRotation(Vector3 sector, float width, float * pOutRot, float dt)
{
	Vector3 vLine;

	if (GetCollisionCheck(&sector))
		vLine = GetLineVectorAsHeightMap(sector, width);
	else
		vLine = v3Zero;

	float fRot = atan2f(vLine.y, vLine.x);

	Lerp(pOutRot, *pOutRot, fRot, dt * 5);
}