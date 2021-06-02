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
#include "ModuleParticles.h"
#include "ModuleBreakable.h"

#include "SDL_image/include/SDL_image.h"
#include "ModuleInput.h"
#include <SDL_mixer/include/SDL_mixer.h>
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )

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

	//App->player->Enable();

	//App->enemies->Enable();

	App->particles->Enable();
	App->breakableParticles->Enable();

	App->collisions->Enable();

	//TileMaps
	Level1FullMapTexture = App->textures->Load("Assets/Art/TileMaps/FullMap.png");
	bgTexture = App->textures->Load("Assets/Art/TileMaps/background.png");
	Houses1Texture = App->textures->Load("Assets/Art/TileMaps/houses1.png");
	Houses2Texture = App->textures->Load("Assets/Art/TileMaps/houses2.png");
	LevelIntroTexture = App->textures->Load("Assets/Art/TileMaps/LevelIntro.png");
	MovingAndChangingTilesTexture = App->textures->Load("Assets/Art/TileMaps/MovingAndChagingTiles.png");

	Mix_ResumeMusic();

	App->audio->PlayMusic("Assets/Music/Mission1.ogg", 0.0f);

	//NULL COLLIDER --> (experimental test for camera functions and other mechanical stuff related with colliders)
	App->collisions->AddCollider({ 90 - 120, 80 - 1100, 790, 1420 }, Collider::Type::NULL_COLLIDER);

	//Camera Bound Colliders -=NOTE: Camera Bound Colliders stop working when colliding with another thing (water for example)=-
	App->collisions->AddCollider({ 100 - 120, 900 - 1100, 130, 400 }, Collider::Type::HORIZONTAL_CAMERA_BOUND);
	App->collisions->AddCollider({ 100 - 120, 520 - 1100, 170, 380 }, Collider::Type::HORIZONTAL_CAMERA_BOUND);
	App->collisions->AddCollider({ 100 - 120, 90 - 1100, 170, 430 }, Collider::Type::HORIZONTAL_CAMERA_BOUND);
	App->collisions->AddCollider({ 430 - 120, 1120 - 1100, 220, 180 }, Collider::Type::HORIZONTAL_CAMERA_BOUND);
	App->collisions->AddCollider({ 600 - 120, 360 - 1100, 220, 770 }, Collider::Type::HORIZONTAL_CAMERA_BOUND);

	App->collisions->AddCollider({ 760 - 120, 50 - 1100, 220, 310 }, Collider::Type::BIDIMENSIONAL_CAMERA_BOUND);
	App->collisions->AddCollider({ 90 - 120, 1300 - 1100, 150, 260 }, Collider::Type::BIDIMENSIONAL_CAMERA_BOUND);
	App->collisions->AddCollider({ 430 - 120, 1300 - 1100, 330, 260 }, Collider::Type::BIDIMENSIONAL_CAMERA_BOUND);

	App->collisions->AddCollider({ 240 - 120, 1300 - 1100, 190, 270 }, Collider::Type::VERTICAL_CAMERA_BOUND);
	App->collisions->AddCollider({ 530 - 120, 120 - 1100, 220, 300 }, Collider::Type::VERTICAL_CAMERA_BOUND);

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
	App->collisions->AddCollider({ 670 - 120, 890 - 1100, 40, 100 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 650 - 120, 840 - 1100, 20, 80 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 640 - 120, 840 - 1100, 10, 80 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 600 - 120, 840 - 1100, 40, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 590 - 120, 840 - 1100, 10, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 570 - 120, 840 - 1100, 20, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 560 - 120, 750 - 1100, 10, 120 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 540 - 120, 750 - 1100, 20, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 540 - 120, 750 - 1100, 10, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 530 - 120, 750 - 1100, 10, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 490 - 120, 750 - 1100, 40, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 480 - 120, 750 - 1100, 10, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 470 - 120, 750 - 1100, 10, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 460 - 120, 750 - 1100, 20, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 450 - 120, 620 - 1100, 10, 140 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 440 - 120, 670 - 1100, 10, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 430 - 120, 680 - 1100, 20, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 460 - 120, 570 - 1100, 10, 160 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 470 - 120, 460 - 1100, 10, 140 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 440 - 120, 250 - 1100, 30, 230 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 430 - 120, 260 - 1100, 10, 210 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 420 - 120, 270 - 1100, 10, 190 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 410 - 120, 280 - 1100, 10, 180 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 400 - 120, 440 - 1100, 10, 10 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 390 - 120, 280 - 1100, 20, 130 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 380 - 120, 280 - 1100, 10, 110 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 360 - 120, 300 - 1100, 20, 60 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 340 - 120, 320 - 1100, 10, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 470 - 120, 250 - 1100, 10, 100 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 480 - 120, 240 - 1100, 10, 30 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 500 - 120, 220 - 1100, 150, 50 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 650 - 120, 240 - 1100, 10, 50 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 660 - 120, 250 - 1100, 40, 40 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 700 - 120, 270 - 1100, 10, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 710 - 120, 280 - 1100, 110, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 820 - 120, 300 - 1100, 20, 60 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 840 - 120, 310 - 1100, 20, 50 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 860 - 120, 60 - 1100, 10, 300 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 170 - 120, 260 - 1100, 20, 90 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 180 - 120, 340 - 1100, 10, 10 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 200 - 120, 140 - 1100, 20, 130 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 220 - 120, 140 - 1100, 20, 120 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 240 - 120, 140 - 1100, 20, 110 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 260 - 120, 140 - 1100, 20, 100 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 280 - 120, 140 - 1100, 20, 90 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 300 - 120, 140 - 1100, 20, 80 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 320 - 120, 140 - 1100, 20, 70 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 340 - 120, 140 - 1100, 20, 60 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 360 - 120, 140 - 1100, 30, 50 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 390 - 120, 150 - 1100, 110, 10 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 500 - 120, 150 - 1100, 140, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 640 - 120, 130 - 1100, 240, 10 }, Collider::Type::TRENCH_WALL);

	App->collisions->AddCollider({ 240 - 120, 400 - 1100, 100, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 195 - 120, 480 - 1100, 100, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 320 - 120, 530 - 1100, 100, 20 }, Collider::Type::TRENCH_WALL);

	App->collisions->AddCollider({ 100 - 120, 630 - 1100, 90, 130 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 100 - 120, 760 - 1100, 50, 60 }, Collider::Type::WALL);

	App->collisions->AddCollider({ 480 - 120, 500 - 1100, 10, 10 }, Collider::Type::MULTI_USE);

	//Item Collisions
	App->particles->AddParticle(App->particles->doubleShotWeapon, 570 - 120, 970 - 1100, Collider::Type::DOUBLE_SHOT_WEAPON_ID01);

	// Breakable and special Collisions
	App->breakableParticles->AddParticle(App->breakableParticles->palm, 440 - 120, 870 - 1100, Collider::Type::BREAKABLE_OBJECT);
	App->breakableParticles->AddParticle(App->breakableParticles->palm, 505 - 120, 890 - 1100, Collider::Type::BREAKABLE_OBJECT);
	App->breakableParticles->AddParticle(App->breakableParticles->palm, 475 - 120, 920 - 1100, Collider::Type::BREAKABLE_OBJECT);
	App->breakableParticles->AddParticle(App->breakableParticles->palm, 410 - 120, 930 - 1100, Collider::Type::BREAKABLE_OBJECT);
	App->breakableParticles->AddParticle(App->breakableParticles->palm, 440 - 120, 930 - 1100, Collider::Type::BREAKABLE_OBJECT);

	App->breakableParticles->AddParticle(App->breakableParticles->house, 70 - 120, 630 - 1100, Collider::Type::BREAKABLE_OBJECT);
	App->breakableParticles->AddParticle(App->breakableParticles->house, 200 - 120, 650 - 1100, Collider::Type::BREAKABLE_OBJECT);
	App->breakableParticles->AddParticle(App->breakableParticles->house, 170 - 120, 700 - 1100, Collider::Type::BREAKABLE_OBJECT);

	// Event triggered particle and event triggerer collider
	fallingWallEventDelays = 0;
	App->breakableParticles->AddParticle(App->breakableParticles->fallingWall, 400 - 120, 440 - 1100, Collider::Type::WALL);
	App->collisions->AddCollider({ 280 - 120, 790 - 1100, 560, 50 }, Collider::Type::EVENT_TRIGGER);
	App->collisions->AddCollider({ 350 - 120, 650 - 1100, 120, 130 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 340 - 120, 660 - 1100, 10, 100 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 370 - 120, 630 - 1100, 60, 30 }, Collider::Type::WALL);

	//App->collisions->AddCollider({ 570 - 120, 970 - 1100, 30, 30 }, Collider::Type::DOUBLE_SHOT_WEAPON_ID01);
	// Enemies ---
	//SOLDIER

	App->enemies->AddEnemy(Enemy_Type::SOLDIER, 178-120, 1340-1100);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER, 401 - 120, 1280 - 1100);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER, 596 - 120, 965 - 1100);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER, 400 - 120, 871 - 1100);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER, 380 - 120, 711 - 1100);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER, 260 - 120, 565 - 1100);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER, 307 - 120, 287 - 1100);

	//SOLDIER2
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 370 - 120, 489 - 1100);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 386 - 120, 650 - 1100);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 278 - 120, 346 - 1100);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 501 - 120, 215 - 1100);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 645 - 120, 214 - 1100);

	//App->render->camera.x = 0;
	//App->render->camera.y = 0;
	App->enemies->AddEnemy(Enemy_Type::BOSS, 401 - 120, 1280 - 1100);

	App->render->camera.x = 100;
	App->render->camera.y = -215;

	App->player->score = 0;

	//App->player->activateWinCondition = false;

	App->player->Enable();
	App->enemies->Enable();

	App->player->cameraXlimitation = false;
	App->player->cameraYlimitation = false;

	return ret;
}

Update_Status SceneLevel1::Update()
{
	/*
	if (App->player->wallCollision == false && App->player->trenchWallCollision == false && App->player->destroyed == false)
	{
		if (App->player->cameraYlimitation == false && App->player->bidimensionalCameraLimitation == false)
		{
			if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
				App->render->camera.y -= App->render->cameraSpeedY;

			if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT)
				App->render->camera.y += App->render->cameraSpeedY;
		}

		if (App->player->cameraXlimitation == false && App->player->bidimensionalCameraLimitation == false)
		{
			if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT)
				App->render->camera.x -= App->render->cameraSpeedX;
			if (App->render->camera.x < 0) App->render->camera.x = 0;

			if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
				App->render->camera.x += App->render->cameraSpeedX;
		}

	}
	*/
	
	if (App->player->activateWinCondition == true)
	{
		App->player->activateWinCondition = false;
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
		App->fade->FadeToBlack((Module*)App->player, (Module*)App->sceneIntro, 90);
	}

	if (App->player->fallingWallEvent == true)
	{
		fallingWallEventDelays++;
	}
	if (fallingWallEventDelays > 0 && fallingWallEventDelays <= 1)
	{
		App->breakableParticles->fallingWall.SetToDelete();
		App->breakableParticles->AddParticle(App->breakableParticles->fallingWallMoving, 400 - 120, 440 - 1100);

		App->particles->AddParticle(App->particles->dirt, 460 - 120, 470 - 1100, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->dirt, 500 - 120, 500 - 1100, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->dirt, 520 - 120, 560 - 1100, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->dirt, 510 - 120, 610 - 1100, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->dirt, 460 - 650, 610 - 1100, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->dirt, 440 - 650, 600 - 1100, Collider::Type::NONE);

		App->particles->AddParticle(App->particles->dirt, 470 - 120, 620 - 1100, Collider::Type::NONE, 10);
		App->particles->AddParticle(App->particles->dirt, 500 - 120, 660 - 1100, Collider::Type::NONE, 15);
		App->particles->AddParticle(App->particles->dirt, 450 - 120, 670 - 1100, Collider::Type::NONE, 20);
		App->particles->AddParticle(App->particles->dirt, 430 - 120, 710 - 1100, Collider::Type::NONE, 20);
		App->particles->AddParticle(App->particles->dirt, 400 - 120, 650 - 1100, Collider::Type::NONE, 25);
		App->particles->AddParticle(App->particles->dirt, 450 - 120, 730 - 1100, Collider::Type::NONE, 25);
		App->particles->AddParticle(App->particles->dirt, 420 - 120, 710 - 1100, Collider::Type::NONE, 25);
		App->particles->AddParticle(App->particles->dirt, 420 - 120, 750 - 1100, Collider::Type::NONE, 30);
		App->particles->AddParticle(App->particles->dirt, 470 - 120, 630 - 1100, Collider::Type::NONE, 30);
		App->particles->AddParticle(App->particles->dirt, 450 - 120, 670 - 1100, Collider::Type::NONE, 35);
		App->particles->AddParticle(App->particles->dirt, 480 - 120, 690 - 1100, Collider::Type::NONE, 35);
		App->particles->AddParticle(App->particles->dirt, 440 - 120, 690 - 1100, Collider::Type::NONE, 35);
		App->particles->AddParticle(App->particles->dirt, 420 - 120, 720 - 1100, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->dirt, 470 - 120, 700 - 1100, Collider::Type::NONE, 40);
		App->particles->AddParticle(App->particles->dirt, 390 - 120, 680 - 1100, Collider::Type::NONE, 45);
		App->particles->AddParticle(App->particles->dirt, 410 - 120, 680 - 1100, Collider::Type::NONE, 45);
		App->particles->AddParticle(App->particles->dirt, 480 - 120, 630 - 1100, Collider::Type::NONE, 50);
		App->particles->AddParticle(App->particles->dirt, 450 - 120, 680 - 1100, Collider::Type::NONE, 55);

	}
	else if (fallingWallEventDelays > 75 && fallingWallEventDelays <= 76)
	{
		App->particles->AddParticle(App->particles->dirt, 350 - 120, 780 - 1100, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->dirt, 380 - 120, 790 - 1100, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->dirt, 410 - 120, 790 - 1100, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->dirt, 440 - 120, 760 - 1100, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->dirt, 450 - 650, 730 - 1100, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->dirt, 440 - 650, 690 - 1100, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->dirt, 340 - 650, 740 - 1100, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->dirt, 350 - 650, 680 - 1100, Collider::Type::NONE);

		App->particles->AddParticle(App->particles->dirt, 390 - 650, 720 - 1100, Collider::Type::NONE, 5);
		App->particles->AddParticle(App->particles->dirt, 410 - 650, 700 - 1100, Collider::Type::NONE, 5);

		App->breakableParticles->AddParticle(App->breakableParticles->fallingWallEnd, 330 - 120, 630 - 1100);
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
	
	//NULL COLLIDER --> (experimental test for camera functions and other mechanical stuff related with colliders)
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 90 - 120, 80 - 1100, 790, 1420 }, Collider::Type::NULL_COLLIDER));

	//Camera Bound Colliders -=NOTE: Camera Bound Colliders stop working when colliding with another thing (water for example)=-
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 100 - 120, 900 - 1100, 130, 400 }, Collider::Type::HORIZONTAL_CAMERA_BOUND));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 100 - 120, 520 - 1100, 170, 380 }, Collider::Type::HORIZONTAL_CAMERA_BOUND));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 100 - 120, 90 - 1100, 170, 430 }, Collider::Type::HORIZONTAL_CAMERA_BOUND));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 430 - 120, 1120 - 1100, 220, 180 }, Collider::Type::HORIZONTAL_CAMERA_BOUND));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 600 - 120, 360 - 1100, 220, 770 }, Collider::Type::HORIZONTAL_CAMERA_BOUND));

	App->collisions->RemoveCollider(App->collisions->AddCollider({ 760 - 120, 50 - 1100, 220, 310 }, Collider::Type::BIDIMENSIONAL_CAMERA_BOUND));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 90 - 120, 1300 - 1100, 150, 260 }, Collider::Type::BIDIMENSIONAL_CAMERA_BOUND));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 430 - 120, 1300 - 1100, 330, 260 }, Collider::Type::BIDIMENSIONAL_CAMERA_BOUND));

	App->collisions->RemoveCollider(App->collisions->AddCollider({ 240 - 120, 1300 - 1100, 190, 270 }, Collider::Type::VERTICAL_CAMERA_BOUND));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 530 - 120, 120 - 1100, 220, 300 }, Collider::Type::VERTICAL_CAMERA_BOUND));

	//Water Colliders
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 160 - 120, 1480 - 1100, 590, 20 }, Collider::Type::WATER));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 250 - 120, 1460 - 1100, 500, 20 }, Collider::Type::WATER));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 270 - 120, 1420 - 1100, 480, 40 }, Collider::Type::WATER));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 270 - 120, 1400 - 1100, 20, 20 }, Collider::Type::WATER));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 300 - 120, 1410 - 1100, 450, 10 }, Collider::Type::WATER));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 360 - 120, 1390 - 1100, 390, 20 }, Collider::Type::WATER));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 400 - 120, 1350 - 1100, 350, 40 }, Collider::Type::WATER));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 490 - 120, 1330 - 1100, 260, 20 }, Collider::Type::WATER));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 520 - 120, 1310 - 1100, 230, 20 }, Collider::Type::WATER));

	//Wall Colliders
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 100 - 120, 1120 - 1100, 70, 80 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 170 - 120, 1120 - 1100, 10, 70 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 180 - 120, 1120 - 1100, 60, 60 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 240 - 120, 1120 - 1100, 40, 50 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 280 - 120, 1120 - 1100, 10, 40 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 290 - 120, 1120 - 1100, 30, 30 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 100 - 120, 1100 - 1100, 230, 20 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 100 - 120, 910 - 1100, 240, 190 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 340 - 120, 940 - 1100, 80, 140 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 420 - 120, 960 - 1100, 10, 80 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 430 - 120, 960 - 1100, 30, 50 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 460 - 120, 970 - 1100, 10, 30 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 340 - 120, 930 - 1100, 20, 10 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 390 - 120, 1180 - 1100, 130, 20 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 400 - 120, 1200 - 1100, 120, 10 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 460 - 120, 1210 - 1100, 60, 10 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 470 - 120, 1220 - 1100, 50, 10 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 500 - 120, 1230 - 1100, 20, 20 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 510 - 120, 1250 - 1100, 10, 10 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 520 - 120, 1180 - 1100, 10, 310 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 100 - 120, 1410 - 1100, 420, 10 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 420 - 120, 1120 - 1100, 40, 60 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 460 - 120, 1100 - 1100, 60, 80 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 520 - 120, 1090 - 1100, 10, 90 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 530 - 120, 1080 - 1100, 20, 100 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 550 - 120, 1070 - 1100, 40, 90 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 590 - 120, 1040 - 1100, 30, 90 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 620 - 120, 1030 - 1100, 100, 100 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 660 - 120, 1010 - 1100, 60, 20 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 680 - 120, 990 - 1100, 40, 20 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 100 - 120, 900 - 1100, 230, 20 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 100 - 120, 880 - 1100, 190, 20 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 100 - 120, 860 - 1100, 130, 20 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 100 - 120, 840 - 1100, 110, 20 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 100 - 120, 810 - 1100, 70, 30 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 100 - 120, 750 - 1100, 30, 60 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 100 - 120, 590 - 1100, 80, 60 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 100 - 120, 540 - 1100, 80, 50 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 180 - 120, 560 - 1100, 30, 20 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 180 - 120, 540 - 1100, 20, 20 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 100 - 120, 510 - 1100, 70, 30 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 150 - 120, 90 - 1100, 10, 420 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 670 - 120, 890 - 1100, 40, 100 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 650 - 120, 840 - 1100, 20, 80 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 640 - 120, 840 - 1100, 10, 80 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 600 - 120, 840 - 1100, 40, 60 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 590 - 120, 840 - 1100, 10, 50 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 570 - 120, 840 - 1100, 20, 40 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 560 - 120, 750 - 1100, 10, 120 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 540 - 120, 750 - 1100, 20, 60 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 540 - 120, 750 - 1100, 10, 50 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 530 - 120, 750 - 1100, 10, 50 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 490 - 120, 750 - 1100, 40, 40 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 480 - 120, 750 - 1100, 10, 30 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 470 - 120, 750 - 1100, 10, 20 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 460 - 120, 750 - 1100, 20, 20 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 450 - 120, 620 - 1100, 10, 140 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 440 - 120, 670 - 1100, 10, 40 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 430 - 120, 680 - 1100, 20, 10 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 460 - 120, 570 - 1100, 10, 160 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 470 - 120, 460 - 1100, 10, 140 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 440 - 120, 250 - 1100, 30, 230 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 430 - 120, 260 - 1100, 10, 210 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 420 - 120, 270 - 1100, 10, 190 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 410 - 120, 280 - 1100, 10, 180 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 400 - 120, 440 - 1100, 10, 10 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 390 - 120, 280 - 1100, 20, 130 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 380 - 120, 280 - 1100, 10, 110 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 360 - 120, 300 - 1100, 20, 60 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 340 - 120, 320 - 1100, 10, 20 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 470 - 120, 250 - 1100, 10, 100 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 470 - 120, 250 - 1100, 10, 100 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 480 - 120, 240 - 1100, 10, 30 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 500 - 120, 220 - 1100, 150, 50 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 650 - 120, 240 - 1100, 10, 50 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 660 - 120, 250 - 1100, 40, 40 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 700 - 120, 270 - 1100, 10, 20 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 710 - 120, 280 - 1100, 110, 20 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 820 - 120, 300 - 1100, 20, 60 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 840 - 120, 310 - 1100, 20, 50 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 860 - 120, 60 - 1100, 10, 300 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 170 - 120, 260 - 1100, 20, 90 }, Collider::Type::WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 180 - 120, 340 - 1100, 10, 10 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 200 - 120, 140 - 1100, 20, 130 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 220 - 120, 140 - 1100, 20, 120 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 240 - 120, 140 - 1100, 20, 110 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 260 - 120, 140 - 1100, 20, 100 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 280 - 120, 140 - 1100, 20, 90 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 300 - 120, 140 - 1100, 20, 80 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 320 - 120, 140 - 1100, 20, 70 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 340 - 120, 140 - 1100, 20, 60 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 360 - 120, 140 - 1100, 30, 50 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 390 - 120, 150 - 1100, 110, 10 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 500 - 120, 150 - 1100, 140, 20 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 640 - 120, 130 - 1100, 240, 10 }, Collider::Type::TRENCH_WALL));

	App->collisions->RemoveCollider(App->collisions->AddCollider({ 240 - 120, 400 - 1100, 100, 20 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 195 - 120, 480 - 1100, 100, 20 }, Collider::Type::TRENCH_WALL));
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 320 - 120, 530 - 1100, 100, 20 }, Collider::Type::TRENCH_WALL));

	SDL_DestroyTexture(Level1FullMapTexture);
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(Houses1Texture);
	SDL_DestroyTexture(Houses2Texture);
	SDL_DestroyTexture(LevelIntroTexture);
	SDL_DestroyTexture(MovingAndChangingTilesTexture);

	//SDL_free(Level1FullMapTexture);
	//SDL_free(bgTexture);
	//SDL_free(Houses1Texture);
	//SDL_free(Houses2Texture);
	//SDL_free(LevelIntroTexture);
	//SDL_free(MovingAndChangingTilesTexture);

	App->player->Disable();
	App->player->CleanUp();

	App->enemies->Disable();
	App->enemies->CleanUp();

	App->particles->Disable();
	App->particles->CleanUp();

	App->breakableParticles->Disable();
	App->breakableParticles->CleanUp();

	App->collisions->CleanUp();
	App->collisions->Disable();

	App->collisions->RemoveCollider(App->player->collider);

	return true;
}
