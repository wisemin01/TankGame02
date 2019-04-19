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
	// ���� �� ��ü�� �߽� ��ǥ�� ���� ���� ����
	// ��� �� ����Ʈ���� y_offset���� ���ư����� ���� ������.
	float y_offset = transform->vPosition.y;

	// iteration�� �ùķ��̼� Ƚ��
	for (int i = 0; i < iteration; i++)
	{
		// ��� �� ����Ʈ���� ��ȸ�Ѵ�
		for (int n = 0; n < iWaterCount; n++)
		{
			WaterPoint& pt = vecPoints[n];

			float force;
			float force_from_right;
			float force_from_left;

			if (n == 0)
			{
				// �� ���� ��Ҷ�� ���ʿ������� ���� ���� 0.
				force_from_left = 0;
			}
			else
			{
				// ���� ��ҿ��� y ���̸� ���Ѵ�.
				force_from_left = vecPoints[n - 1].y - pt.y;
				force_from_left *= springConstant;
			}

			if (n == iWaterCount - 1)
			{
				// �� ������ ��Ҷ�� �����ʿ������� ���� ���� 0.
				force_from_right = 0;
			}
			else
			{
				// ������ ��ҿ��� y ���̸� ���Ѵ�.
				force_from_right = vecPoints[n + 1].y - pt.y;
				force_from_right *= springConstant;
			}

			// y_offset���� ���� ����.
			float widthDepth = y_offset - pt.y;
			// y_offset�� ���ư����� ��
			float forceToBaseLine = baseLine * widthDepth;

			// �� = ���� ��� + ������ ��� +  y_offset ���� ���ư����� ��
			force = force_from_left + force_from_right + forceToBaseLine;

			float acceleration = force / pt.mass;
			pt.speed.y = damping * pt.speed.y + acceleration;

			// ���� ���� �����Ѵ�.
			pt.y = pt.y + pt.speed.y;
		}
	}
}
