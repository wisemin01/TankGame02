#include "DXUT.h"
#include "Water.h"


Water::Water()
{
}


Water::~Water()
{
}

void Water::Init()
{
	AC(Transform);
	AC(Collider);

	SetTag("WATER");
	pWaterTex = GETTEXTURE("WATER");

	fSinOffset = 0;
}

void Water::Update(float dt)
{
	fSinOffset += dt * 10;

	if (fSinOffset >= 100)
		fSinOffset -= 100;

	ProcessWater(3, 0.0095f, 0.0095f, 0.98f);
}

void Water::Render()
{
	RESOURCE.SetRenderType(SCROLL);

	constexpr int dep = 10;

	for (auto iter : vecPoints)
	{
		if (iter.x >= CAMERA_POS.x + WINSIZEX + dep ||
			iter.x <= CAMERA_POS.x - dep)
		{
			continue;
		}

		RESOURCE.ApplyWorldTransform(Vector3(iter.x, iter.y + sin(iter.x * 0.02f + fSinOffset) * 5, 0),
			v3Normal, 0);

		RESOURCE.Draw(pWaterTex, v3Zero, 0xffffffff);
	}
}

void Water::Destroy()
{
}

void Water::Setup(Vector3 leftPivot, int count)
{
	transform->vPosition = leftPivot;
	iWaterCount = count;

	vecPoints.reserve(count);

	fBlockWidth = pWaterTex->tInfo.Width - 4;
	fBlockHeight = pWaterTex->tInfo.Height;

	fMapWidth = fBlockWidth * count;
	fMapHeight = fBlockHeight;

	for (int i = 0; i < count; i++)
	{
		vecPoints.push_back(
			WaterPoint(leftPivot.x + fBlockWidth * i, leftPivot.y));
	}

	// COLLIDER SETTING
	collider->Create(0, 0, fMapWidth, fMapHeight, [&](Collider* other) { OnCollision(other); });
}

void Water::Impress(Vector3 position, float width)
{
	Vector3 p = position - transform->vPosition;

	float sX = position.x - width / 2.f;
	float eX = position.x + width / 2.f;

	int sIndex = (int)(sX / fBlockWidth);
	int eIndex = (int)(eX / fBlockWidth);

	if (sIndex < 0 || sIndex >= iWaterCount ||
		eIndex < 0 || eIndex >= iWaterCount)
		return;

	float power = 1.8f;

	for (int i = sIndex; i < eIndex; i++)
	{
		vecPoints[i].speed.y += power;
	}
}

void Water::OnCollision(Collider * other)
{
	if (other->bTrigger)
		return;

	if (other->gameObject->transform) {

		float tB = other->GetWorldRange().bottom;

		if (tB >= transform->vPosition.y - 3
			&& tB <= transform->vPosition.y + 3)
			return;

		Impress(other->gameObject->transform->vPosition,
			other->Width());
	}
}

void Water::ProcessWater(int iteration, float springConstant, float baseLine, float damping)
{
	// 현재 이 객체의 중심 좌표는 왼쪽 위로 설정
	// 모든 물 포인트들은 y_offset으로 돌아가려는 힘을 가진다.
	float y_offset = transform->vPosition.y;

	// iteration은 시뮬레이션 횟수
	for (int i = 0; i < iteration; i++)
	{
		// 모든 물 포인트들을 순회한다
		for (int n = 0; n < iWaterCount; n++)
		{
			WaterPoint& pt = vecPoints[n];

			float force;
			float force_from_right;
			float force_from_left;

			if (n == 0)
			{
				// 맨 왼쪽 요소라면 왼쪽에서부터 오는 힘은 0.
				force_from_left = 0;
			}
			else
			{
				// 왼쪽 요소와의 y 차이를 구한다.
				force_from_left = vecPoints[n - 1].y - pt.y;
				force_from_left *= springConstant;
			}

			if (n == iWaterCount - 1)
			{
				// 맨 오른쪽 요소라면 오른쪽에서부터 오는 힘은 0.
				force_from_right = 0;
			}
			else
			{
				// 오른쪽 요소와의 y 차이를 구한다.
				force_from_right = vecPoints[n + 1].y - pt.y;
				force_from_right *= springConstant;
			}

			// y_offset과의 높이 차이.
			float widthDepth = y_offset - pt.y;
			// y_offset로 돌아가려는 힘
			float forceToBaseLine = baseLine * widthDepth;

			// 힘 = 왼쪽 요소 + 오른쪽 요소 +  y_offset 으로 돌아가려는 힘
			force = force_from_left + force_from_right + forceToBaseLine;

			float acceleration = force / pt.mass;
			pt.speed.y = damping * pt.speed.y + acceleration;

			// 힘을 점에 적용한다.
			pt.y = pt.y + pt.speed.y;
		}
	}
}
