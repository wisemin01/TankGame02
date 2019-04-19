#include "DXUT.h"
#include "Stage2Scene.h"

#include "PlayerController.h"
#include "ScrollBG.h"
#include "Ground.h"
#include "Volcano.h"
#include "Water.h"
#include "SavePoint.h"

#include "Fade.h"
#include "Mine.h"

#include "EnemyController.h"

Stage2Scene::Stage2Scene()
{
}


Stage2Scene::~Stage2Scene()
{
}

void Stage2Scene::Init()
{
	SOUND.Play("BG", 1);
	CAMERA.InitCamera();
	CAMERA.UseRange(0, 0, 99999, HALFSIZEY - 180);

	if (FAILED(COLLISION.GetPixelModule()->CreateRandomMultiHeightMap(GETTEXTURE("MINIMAP"), 10)))
	{
		assert(FALSE, "MAP CREATE FAILED");
		return;
	}

	InstanceEx(Fade)(100)->Setup(0, 1, 3, []() {}, []() {});

	HeightMap* pMap = COLLISION.GetPixelModule()->GetHeightMap();

	InstanceEx(PlayerController)(20, true, true)->PlayerSpawn();

	InstanceEx(ScrollBG)(-10)->Setup(GETTEXTURE("BACKGROUND", 0), Vector3(0, -HALFSIZEY, 0), 200);
	InstanceEx(ScrollBG)(-9)->Setup(GETTEXTURE("BACKGROUND", 1), Vector3(0, -HALFSIZEY, 0), 300);
	InstanceEx(Volcano)(-8)->Setup(HALFSIZEX, HALFSIZEY + 180);
	InstanceEx(ScrollBG)(-7)->Setup(GETTEXTURE("BACKGROUND", 2), Vector3(0, -HALFSIZEY, 0), 400);
	InstanceEx(ScrollBG)(-6)->Setup(GETTEXTURE("BACKGROUND", 3), Vector3(0, -HALFSIZEY, 0), 500);

	Instance(EnemyController)->Setup(3, 5);

	Ground::CreateBackGround(GETTEXTURE("GROUND"), pMap, -5, Vector3(0, 0, 0));
	SavePoint::CreateSavePoints(100, 10, 2);
	Mine::CreateMines(500, 40, 2);
}

void Stage2Scene::Update(float dt)
{
}

void Stage2Scene::Render()
{
}

void Stage2Scene::Destroy()
{
	COLLISION.GetPixelModule()->DestroyHeightMap();
	SOUND.Stop("BG");
}

void Stage2Scene::Load()
{
	// LOAD BACKGROUND
	ADDTEXTURE("MINIMAP", "./RS/MAP/STAGE2/MINIMAP/(%d).png", 3);
	ADDTEXTURE("BACKGROUND", "./RS/MAP/STAGE2/(%d).png", 4);
	ADDTEXTURE("GROUND", "./RS/MAP/STAGE2/GROUND/G(%d).png", 3);

	// OTHER TEXTURES
	ADDSTATETEX("PLAYER_LV1", "./RS/OBJECT/PLAYER/LV1/", IDLE | MOVE, 6);
	ADDSTATETEX("PLAYER_LV2", "./RS/OBJECT/PLAYER/LV2/", IDLE | MOVE, 6);
	ADDSTATETEX("PLAYER_LV3", "./RS/OBJECT/PLAYER/LV3/", IDLE | MOVE, 6);
	ADDTEXTURE("TOP_CANNON", "./RS/OBJECT/PLAYER/TOP_CANNON.png");

	ADDTEXTURE("MINE", "./RS/OBJECT/ENEMY/MINE/(%d).png", 4);
	ADDTEXTURE("ENEMY", "./RS/OBJECT/ENEMY/ENEMY/(%d).png", 4);
	ADDTEXTURE("DROP_MINE", "./RS/OBJECT/ENEMY/DROP_MINE/(%d).png", 4);

	ADDTEXTURE("VOLCANO", "./RS/OBJECT/VOLCANO/(%d).png", 4);
	ADDTEXTURE("METEOR", "./RS/OBJECT/METEOR/(1).png");
	ADDTEXTURE("BULLET", "./RS/EFFECT/BULLET/Forward.png");
	ADDTEXTURE("BULLET_T", "./RS/EFFECT/BULLET/Top.png");
	ADDTEXTURE("BULLET_E", "./RS/EFFECT/BULLET/Enemy.png");
	ADDTEXTURE("NUCLEAR", "./RS/EFFECT/BULLET/Nuclear.png");
	ADDTEXTURE("STONE", "./RS/OBJECT/STONE.png");
	ADDTEXTURE("WATER", "./RS/OBJECT/WATER.png");
	ADDTEXTURE("EXPLODE", "./RS/EFFECT/EXPLODE/R(%d).png", 6);
	ADDTEXTURE("EXPLODE_B", "./RS/EFFECT/EXPLODE/B(%d).png", 6);
	ADDTEXTURE("SAVEPOINT", "./RS/OBJECT/SAVEPOINT/(%d).png", 5);
	ADDTEXTURE("ITEM", "./RS/OBJECT/ITEM/(%d).png", 6);

	ADDTEXTURE("METEOR_WARNING", "./RS/UI/INGAME/METEOR_WARNING.png");

	ADDTEXTURE("PROGRESS_BAR", "./RS/UI/INGAME/PROGRESS/(%d).png", 2);
	ADDTEXTURE("MINITANK", "./RS/UI/INGAME/PROGRESS/TANK.png");
	ADDTEXTURE("ITEM_UI", "./RS/UI/INGAME/ITEM_INFO/(%d).png", 6);
	ADDTEXTURE("HEART", "./RS/UI/INGAME/HEART.png");
	ADDTEXTURE("CLOCK", "./RS/UI/INGAME/TIME.png");

	ADDTEXTURE("BLACK", "./RS/UI/BLACK.png");

	SOUND.Create("BG", L"./RS/SOUND/(4).wav");
	SOUND.Create("EXPLODE1", L"./RS/SOUND/E(1).wav");
	SOUND.Create("EXPLODE2", L"./RS/SOUND/E(2).wav");
}
