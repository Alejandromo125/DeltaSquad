#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

#include "ModuleFadeToBlack.h"
#include "SceneIntro.h"

SceneLevel1::SceneLevel1(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel1::~SceneLevel1()
{

}

// Load assets
bool SceneLevel1::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	//TileMaps
	Level1FullMapTexture = App->textures->Load("Assets/Art/TileMaps/FullMap.png");
	bgTexture = App->textures->Load("Assets/Art/TileMaps/background.png");
	Houses1Texture = App->textures->Load("Assets/Art/TileMaps/background.png");
	Houses2Texture = App->textures->Load("Assets/Art/TileMaps/background.png");
	LevelIntroTexture = App->textures->Load("Assets/Art/TileMaps/background.png");
	MovingAndChangingTilesTexture = App->textures->Load("Assets/Art/TileMaps/background.png");

	App->audio->PlayMusic("Assets/Music/Mission1.ogg", 0.0f);

	//NULL COLLIDER --> (experimental test for camera functions and other mechanical stuff related with colliders)
	App->collisions->AddCollider({ 90 - 120, 80 - 1100, 790, 1420 }, Collider::Type::NULL_COLLIDER);

	//Camera Bound Colliders -=NOTE: Camera Bound Colliders stop working when colliding with another thing (water for example)=-
	App->collisions->AddCollider({ 100 - 120, 900 - 1100, 130, 610 }, Collider::Type::HORIZONTAL_CAMERA_BOUND);
	App->collisions->AddCollider({ 100 - 120, 520 - 1100, 170, 380 }, Collider::Type::HORIZONTAL_CAMERA_BOUND);
	App->collisions->AddCollider({ 100 - 120, 90 - 1100, 170, 430 }, Collider::Type::HORIZONTAL_CAMERA_BOUND);
	App->collisions->AddCollider({ 430 - 120, 1120 - 1100, 220, 380 }, Collider::Type::HORIZONTAL_CAMERA_BOUND);
	App->collisions->AddCollider({ 600 - 120, 360 - 1100, 220, 770 }, Collider::Type::HORIZONTAL_CAMERA_BOUND);
	App->collisions->AddCollider({ 760 - 120, 50 - 1100, 220, 310 }, Collider::Type::HORIZONTAL_CAMERA_BOUND);

	App->collisions->AddCollider({ 90 - 120, 1300 - 1100, 670, 270 }, Collider::Type::VERTICAL_CAMERA_BOUND);
	//App->collisions->AddCollider({ 90 - 120, 30 - 1100, 790, 240 }, Collider::Type::VERTICAL_CAMERA_BOUND); <-- Not needed

	//Water Colliders
	App->collisions->AddCollider({ 160 - 120, 1480 - 1100, 590, 20 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 250 - 120, 1460 - 1100, 500, 20 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 270 - 120, 1420 - 1100, 480, 40 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 270 - 120, 1400 - 1100, 20, 20 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 300 - 120, 1410 - 1100, 450, 10 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 360 - 120, 1390 - 1100, 390, 20 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 400 - 120, 1350 - 1100, 350, 40 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 490 - 120, 1330 - 1100, 260, 20 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 520 - 120, 1310 - 1100, 230, 20 }, Collider::Type::WATER);

	//Wall Colliders
	App->collisions->AddCollider({ 100 - 120, 1120 - 1100, 70, 80 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 170 - 120, 1120 - 1100, 10, 70 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 180 - 120, 1120 - 1100, 60, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 240 - 120, 1120 - 1100, 40, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 280 - 120, 1120 - 1100, 10, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 290 - 120, 1120 - 1100, 30, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 100 - 120, 1100 - 1100, 230, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 100 - 120, 910 - 1100, 240, 190 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 340 - 120, 940 - 1100, 80, 140 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 420 - 120, 960 - 1100, 10, 80 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 430 - 120, 960 - 1100, 30, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 460 - 120, 970 - 1100, 10, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 340 - 120, 930 - 1100, 20, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 390 - 120, 1180 - 1100, 130, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 400 - 120, 1200 - 1100, 120, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 460 - 120, 1210 - 1100, 60, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 470 - 120, 1220 - 1100, 50, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 500 - 120, 1230 - 1100, 20, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 510 - 120, 1250 - 1100, 10, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 520 - 120, 1180 - 1100, 10, 310 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 100 - 120, 1410 - 1100, 420, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 420 - 120, 1120 - 1100, 40, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 460 - 120, 1100 - 1100, 60, 80 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 520 - 120, 1090 - 1100, 10, 90 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 530 - 120, 1080 - 1100, 20, 100 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 550 - 120, 1070 - 1100, 40, 90 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 590 - 120, 1040 - 1100, 30, 90 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 620 - 120, 1030 - 1100, 100, 100 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 660 - 120, 1010 - 1100, 60, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 680 - 120, 990 - 1100, 40, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 100 - 120, 900 - 1100, 230, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 100 - 120, 880 - 1100, 190, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 100 - 120, 860 - 1100, 130, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 100 - 120, 840 - 1100, 110, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 100 - 120, 810 - 1100, 70, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 100 - 120, 750 - 1100, 30, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 100 - 120, 590 - 1100, 80, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 100 - 120, 540 - 1100, 80, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 180 - 120, 560 - 1100, 30, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 180 - 120, 540 - 1100, 20, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 100 - 120, 510 - 1100, 70, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 150 - 120, 90 - 1100, 10, 420 }, Collider::Type::WALL);

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::SOLDIER, 80, 80);

	//App->render->camera.x = 0;
	//App->render->camera.y = 0;

	App->render->camera.x = 100;
	App->render->camera.y = -215;

	App->player->Enable();
	App->enemies->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	//App->render->camera.x = App->player->position.x - ((SCREEN_WIDTH / 2));
	//App->render->camera.y = App->player->position.y - ((SCREEN_HEIGHT / 2));
	
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, -600, NULL, 0.53, true);
	App->render->Blit(bgTexture, 512, -600, NULL, 0.53, true);
	App->render->Blit(Level1FullMapTexture, -120, -1100, NULL, 1.0, true);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();

	return true;
}
