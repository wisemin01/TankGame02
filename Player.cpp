#include "DXUT.h"
#include "Player.h"

#include "Renderer.h"
#include "Rigidbody.h"
#include "Bullet.h"
#include "TrackingBullet.h"
#include "PlayerTopCannon.h"
#include "Nuclear.h"

#define WIDTH 150
#define WHEEL_WIDTH 100

Vector3 Player::vRespawnPos = Vector3(300, 250, 0);
bool Player::bPlayerLive = false;

Player::Player()
{
	bPlayerLive = true;
	bInvinc = false;
	bDoubleJump = false;
	pTopCannon = nullptr;
	bControllLock = false;
}


Player::~Player()
{
	bPlayerLive = false;
}

void Player::Init()
{
	AC(Transform);
	AC(Renderer);
	AC(Rigidbody);
	AC(Collider);
	AC(Life)->Setup(1, [&]() { OnDeath(); });

	SetTag("PLAYER");
	eState = IDLE;
	iTankLevel = 0;
	cannonPos = Vector3(100, -100, 0);

	pPlayerTexture[0] = GETTEXTURE("PLAYER_LV1");
	pPlayerTexture[1] = GETTEXTURE("PLAYER_LV2");
	pPlayerTexture[2] = GETTEXTURE("PLAYER_LV3");

	pTopCannon = InstanceEx(PlayerTopCannon)(6);
	pTopCannon->Setup(this, Vector3(0, -70, 0));

	renderer->SetTexture(pPlayerTexture[iTankLevel]->GetTexture(eState));
	renderer->eRenderType = SCROLL;
	renderer->tFrame(0, 5, 0.2);
	
	transform->vPosition = vRespawnPos;
	transform->vScale = Vector3(0.5, 0.5, 0);
	transform->vOffset = Vector3(0, -55, 0);

	rigidbody->bUseGravity = true;
	rigidbody->fMass = 2.0f;

	collider->CreateAsTexture(renderer->pTex, [&](Collider*) {});
	collider->vOffset = Vector3(0, -55, 0);

	bRightLock = false;
	bLeftLock = false;
	fSpeed = 50.0f;
	iNuclearCount = 2;

	CAMERA.SetTarget(this);
	CAMERA.SetOffset(300, 0);
	CAMERA.SetPosition(transform->vPosition);

	for (int i = 0; i < ITEM_END; i++)
		tItemInfo[i].Reset();
}

void Player::Update(float dt)
{
	Vector3 vForce(0, 0, 0);

	float fp = fSpeed;

	if (tItemInfo[SPEED_UP].bItemActive)
	{
		fp *= 1.5f;
	}

	if (!bControllLock) {

		if (INPUT.GetInputKeyPress('A') && !bLeftLock)
			vForce += Vector3(-fp, 0, 0);
		if (INPUT.GetInputKeyPress('D') && !bRightLock)
			vForce += Vector3(fp, 0, 0);

		if (INPUT.GetInputKeyDown(VK_SPACE)) {
			if (bOnFloor) {
				vForce += Vector3(0, -700, 0);

				if (tItemInfo[DOUBLE_JUMP].bItemActive)
					bDoubleJump = true;
			}
			else if (bDoubleJump)
			{
				vForce += Vector3(0, -700, 0);
				bDoubleJump = false;
			}
		}

		if (INPUT.GetInputKeyDown(VK_TAB))
		{
			if (iNuclearCount > 0) {
				iNuclearCount--;
				InstanceEx(Nuclear)(10);
			}
		}
	}

#if (CHEET_ON)
	if (INPUT.GetInputKeyDown('1'))
		UseItem(DOUBLE_JUMP, 10);
	if (INPUT.GetInputKeyDown('2'))
		UseItem(SPEED_UP, -1);
	if (INPUT.GetInputKeyDown('3'))
		UseItem(THREE_DIR, 10);
	if (INPUT.GetInputKeyDown('4'))
		UseItem(RANGE_UP, 10);
	if (INPUT.GetInputKeyDown('5'))
		UseItem(TRACKING, 10);

	if (INPUT.GetInputKeyDown(VK_F1))
		bInvinc = !bInvinc;
	if (INPUT.GetInputKeyDown(VK_F2))
		DegradeTank();
	if (INPUT.GetInputKeyDown(VK_F3))
		UpgradeTank();
#endif

	ProcessItem(dt);
	ProcessAttack();
	ProcessCalculatePlayer(vForce);
	ProcessAsPixelMap(dt);
}

void Player::Render()
{
}

void Player::Destroy()
{
	CAMERA.SetTarget(nullptr);
}

void Player::ProcessAsPixelMap(float dt)
{
	PixelColliderModule* pix = COLLISION.GetPixelModule();

	if (pix->GetCollisionCheck(&transform->vPosition))
	{
		Vector3 vPush;

		pix->GetCalculatePushVector(&vPush, transform->vPosition, WHEEL_WIDTH);

		float y = pix->GetHeightAsHeightMap(transform->vPosition.x);

		rigidbody->AddForce(vPush, 75);

		if (rigidbody->vForce.y > y)
			rigidbody->vForce.y = 0;

		if (transform->vPosition.y >= y)
			transform->vPosition.y = y;
	}

	if (COLLISION.GetPixelModule()->GetCollisionCheck(&(transform->vPosition + Vector3(0, 10, 0))))
	{
		bOnFloor = true;
	}
	else
	{
		bOnFloor = false;
	}

	if (pix->GetRightInspec(transform->vPosition, WIDTH / 2.f, 80))
	{
		if (rigidbody->vVelocity.x > 0)
			rigidbody->vVelocity.x = 0;
		rigidbody->AddForce(-20, 0);
		bRightLock = true;
	}
	else bRightLock = false;

	if (pix->GetLeftInspec(transform->vPosition, WIDTH / 2.f, 80))
	{
		if (rigidbody->vVelocity.x < 0)
			rigidbody->vVelocity.x = 0;
		rigidbody->AddForce(20, 0);
		bLeftLock = true;
	}
	else bLeftLock = false;

	COLLISION.GetPixelModule()->GetCalculateLineRotation(transform->vPosition, WIDTH, &transform->fRot, dt);
}

void Player::ProcessCalculatePlayer(Vector3 moveData)
{
	rigidbody->AddForce(moveData);

	int prev = eState;

	if (moveData == v3Zero)
		eState = IDLE;
	else
		eState = MOVE;

	if(prev != eState)
		renderer->SetTexture(pPlayerTexture[iTankLevel]->GetTexture(eState));

	if (transform->vPosition.y > 990)
		Kill();
}

void Player::ProcessAttack()
{
	if (INPUT.GetInputKeyDown(VK_LBUTTON))
	{
		float lifeTime = 0.7;
		float rot = transform->fRot;
		int count = 1;
		bool tracking = false;

		if (tItemInfo[THREE_DIR].bItemActive) {
			count = 3;
			rot -= 0.1f;
		}
		if (tItemInfo[RANGE_UP].bItemActive)
			lifeTime *= 3;
		if (tItemInfo[TRACKING].bItemActive)
			tracking = true;

		for (int i = 0; i < count; i++) {

			D3DXMATRIX mat;
			D3DXMatrixRotationZ(&mat, rot + 0.1 * i);
			Vector3 dir;
			D3DXVec3TransformNormal(&dir, &Vector3(1, 0, 0), &mat);

			if (tracking)
				InstanceEx(TrackingBullet)(0)->Setup(GetCannonPos(), dir, "BULLET", 120, 1, lifeTime * 2);
			else
				InstanceEx(Bullet)(0)->Setup(GetCannonPos(), dir, "BULLET", 120, 1, lifeTime);
		}
	}
}

void Player::ProcessItem(float dt)
{
	for (int i = 0; i < ITEM_END; i++)
	{
		tItemInfo[i].Update(dt);

		if (tItemInfo[i].fDelay < 0)
			continue;

		if (tItemInfo[i].fFrameSkip >= tItemInfo[i].fDelay)
		{
			tItemInfo[i].Reset();
		}
	}
}


void Player::OnDeath()
{
	if (bInvinc)
		return;

	CAMERA.Shake(1.0f, 20);
	SOUND.DuplicatePlay("EXPLODE1", 0);

	Kill();
}

void Player::UseItem(ITEM_TYPE item, float lifeTime)
{
	if (item == NUCLEAR)
	{
		if (iNuclearCount < 2)
			iNuclearCount++;
		return;
	}

	tItemInfo[item].bItemActive = true;
	tItemInfo[item].fDelay = lifeTime;
	tItemInfo[item].fFrameSkip = 0;
}

void Player::UpgradeTank()
{
	if (iTankLevel < 2) {
		iTankLevel++;
		TankSetting();
	}
}

void Player::DegradeTank()
{
	if (iTankLevel > 0) {
		iTankLevel--;
		TankSetting();
	}
}

void Player::TankSetting()
{
	renderer->SetTexture(pPlayerTexture[iTankLevel]->GetTexture(eState));
	collider->ReCreateAsTexture(renderer->pTex);

	switch (iTankLevel)
	{
	case 0:

		pTopCannon->Setup(this, Vector3(0, -70, 0));
		transform->vOffset = Vector3(0, -55, 0);
		collider->vOffset = Vector3(0, -55, 0);
		cannonPos = Vector3(100, -100, 0);

		break;
	case 1:

		pTopCannon->Setup(this, Vector3(0, -100, 0));
		transform->vOffset = Vector3(0, -95, 0);
		collider->vOffset = Vector3(0, -95, 0);
		cannonPos = Vector3(100, -130, 0);

		break;
	case 2:

		pTopCannon->Setup(this, Vector3(0, -70, 0));
		transform->vOffset = Vector3(0, -120, 0);
		collider->vOffset = Vector3(0, -120, 0);
		cannonPos = Vector3(100, -100, 0);

		break;
	default:
		break;
	}
}

Vector3 Player::GetCannonPos()
{
	Vector3 out;

	D3DXMATRIX mat;

	D3DXMatrixRotationZ(&mat, transform->fRot);

	D3DXVec3TransformCoord(&out, &cannonPos, &mat);

	return out + transform->vPosition;
}

void Player::OnRespawn()
{
	transform->vPosition = vRespawnPos;
}
