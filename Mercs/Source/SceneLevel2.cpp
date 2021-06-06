#include "SceneLevel2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "Boss.h"

#include "ModuleFadeToBlack.h"
#include "SceneIntro.h"
#include "ModuleParticles.h"
#include "ModuleBreakable.h"
#include "ModuleEndPlane.h"

#include "SDL_image/include/SDL_image.h"
#include "ModuleInput.h"
#include <SDL_mixer/include/SDL_mixer.h>
#pragma comment( lib, "SDL_image/libx86/SDL2_image.lib" )


SceneLevel2::SceneLevel2(bool startEnabled) : Module(startEnabled)
{

}

SceneLevel2::~SceneLevel2()
{

}

// Load assets
bool SceneLevel2::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	//App->player->Enable();

	//App->enemies->Enable();

	App->particles->Enable();
	App->breakableParticles->Enable();
	App->endPlane->Enable();

	App->collisions->Enable();

	//TileMaps
	Level2FullMapTexture = App->textures->Load("Assets/Art/TileMaps/FullMap_L2.png");
	//bgTexture = App->textures->Load("Assets/Art/TileMaps/background.png");
	//LevelIntroTexture = App->textures->Load("Assets/Art/TileMaps/LevelIntro.png");

	Mix_ResumeMusic();

	App->audio->PlayMusic("Assets/Music/Mission2.ogg", 0.0f);

	//NULL COLLIDER --> (experimental test for camera functions and other mechanical stuff related with colliders)
	App->collisions->AddCollider({ 0, 0, 768, 3072 }, Collider::Type::NULL_COLLIDER);
	
	// Scene Colliders
	App->collisions->AddCollider({ 270, 2890, 60, 180 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 250, 2870, 50, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 210, 2820, 70, 50 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 200, 2810, 10, 40 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 170, 2770, 60, 40 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 160, 2760, 30, 10 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 0, 2740, 180, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 500, 2720, 40, 350 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 470, 2940, 30, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 470, 2810, 30, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 470, 2690, 50, 70 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 440, 2680, 30, 70 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 390, 2650, 50, 50 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 370, 2620, 20, 30 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 350, 2580, 20, 50 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 370, 2580, 310, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 400, 2470, 20, 110 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 0, 2200, 110, 340 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 110, 2200, 10, 150 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 120, 2110, 20, 100 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 140, 2110, 10, 80 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 150, 2110, 10, 70 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 160, 2140, 30, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 160, 2080, 20, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 180, 2080, 10, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 170, 1990, 40, 90 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 210, 1990, 30, 70 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 240, 1990, 20, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 260, 1990, 20, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 280, 1990, 20, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 300, 1940, 20, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 320, 1940, 20, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 340, 1940, 20, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 360, 1900, 30, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 390, 1820, 10, 100 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 400, 1820, 10, 90 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 410, 1820, 10, 80 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 420, 1820, 10, 70 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 430, 1820, 10, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 440, 1820, 10, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 450, 1820, 10, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 460, 1820, 10, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 470, 1680, 10, 160 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 440, 1640, 30, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 390, 1630, 50, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 340, 2420, 360, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 310, 2220, 30, 210 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 300, 2240, 10, 160 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 320, 2200, 130, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 340, 2190, 40, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 410, 2170, 130, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 500, 2060, 40, 110 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 510, 2010, 30, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 520, 1960, 90, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 530, 1950, 20, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 570, 1930, 40, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 580, 1760, 190, 170 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 1420, 530, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 1410, 480, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 680, 1430, 90, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 700, 1410, 70, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 640, 1260, 130, 80 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 380, 1200, 390, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 350, 1210, 30, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 1230, 40, 80 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 40, 1230, 110, 40 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 170, 1250, 20, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 60, 970, 10, 260 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 70, 970, 360, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 430, 980, 30, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 460, 990, 20, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 550, 1100, 120, 80 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 720, 1040, 50, 160 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 610, 1040, 110, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 590, 1050, 20, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 580, 1070, 10, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 180, 850, 120, 80 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 0, 1310, 40, 100 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 70, 1150, 20, 30 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 150, 1240, 20, 20 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 100, 830, 40, 140 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 0, 780, 270, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 570, 780, 200, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 410, 780, 110, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 390, 790, 20, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 370, 810, 20, 10 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 580, 820, 110, 70 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 530, 850, 40, 40 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 700, 850, 50, 40 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 730, 890, 20, 30 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 370, 610, 90, 140 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 450, 750, 10, 30 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 0, 610, 80, 10 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 350, 680, 10, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 340, 670, 10, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 330, 660, 10, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 320, 650, 10, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 310, 640, 10, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 300, 630, 10, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 290, 620, 10, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 280, 610, 10, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 270, 600, 10, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 210, 590, 60, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 80, 360, 10, 270 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 200, 360, 10, 250 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 0, 400, 80, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 210, 400, 560, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 0, 0, 770, 10 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 140, 30, 580, 150 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 100, 1040, 100, 90 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 200, 1040, 30, 70 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 230, 1040, 20, 60 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 250, 1040, 30, 30 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 100, 1290, 90, 120 }, Collider::Type::TRENCH_WALL);


	App->collisions->AddCollider({ 450, 1450, 10, 190 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 470, 1590, 40, 20 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 503, 1450, 80, 130 }, Collider::Type::TRENCH_WALL);

	App->collisions->AddCollider({ 760, 0, 10, 1760 }, Collider::Type::TRENCH_WALL);
	App->collisions->AddCollider({ 660, 210, 110, 1580 }, Collider::Type::HORIZONTAL_CAMERA_BOUND);
	App->collisions->AddCollider({ 0, 0, 660, 210 }, Collider::Type::VERTICAL_CAMERA_BOUND);
	App->collisions->AddCollider({ 660, 0, 110, 210 }, Collider::Type::BIDIMENSIONAL_CAMERA_BOUND);
	App->collisions->AddCollider({ 110, 800, 130, 180 }, Collider::Type::HORIZONTAL_CAMERA_BOUND);

	App->collisions->AddCollider({ 560, 140, 80, 80 }, Collider::Type::MULTI_USE);


	// Enemies
	App->enemies->AddEnemy(Enemy_Type::TOWER_ENEMY, 501, 1440);
	App->enemies->AddEnemy(Enemy_Type::TOWER_ENEMY, 371, 610);
	App->enemies->AddEnemy(Enemy_Type::TOWER_ENEMY, 101, 1250);


	App->enemies->AddEnemy(Enemy_Type::ENEMY_CAR, 170, 2470);
	App->enemies->AddEnemy(Enemy_Type::ENEMY_CAR, 420, 2020);
	App->enemies->AddEnemy(Enemy_Type::ENEMY_CAR, 100, 380);

	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 280, 2720);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 50, 2630);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 320, 2520);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 140, 2380);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 210, 2380);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 170, 2310);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 240, 2080);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 220, 2310);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 460, 2130);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 500, 1890);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 500, 1810);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 540, 1810);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 700, 1650);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 520, 1650);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 610, 1420);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 250, 1200);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 200, 1330);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 500, 1320);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 400, 1350);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 320, 1290);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 260, 2180);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 110, 1170);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 250, 1360);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 210, 1230);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 300, 1220);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 700, 1360);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 330, 1100);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 390, 1150);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 420, 1090);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 500, 1150);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 500, 1020);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 540, 1040);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 690, 970);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 630, 940);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 250, 930);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 480, 840);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 320, 790);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 280, 790);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 230, 710);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 60, 700);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 100, 640);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 140, 650);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER2, 190, 630);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 110, 340);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 160, 340);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 130, 290);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 690, 1500);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 500, 930);
	App->enemies->AddEnemy(Enemy_Type::SOLDIER_LEVEL2, 390, 900);

	//Item Collisions
	App->particles->AddParticle(App->particles->greenShotWeapon, 120, 2580, Collider::Type::GREEN_SHOT_WEAPON_ID02);
	App->particles->AddParticle(App->particles->healingFood, 270, 2450, Collider::Type::HEALING_FOOD_ID03);
	App->particles->AddParticle(App->particles->healingFood, 160, 1170, Collider::Type::HEALING_FOOD_ID03);

	// Last scene
	App->endPlane->AddParticle(App->endPlane->plane, 10, 0, Collider::Type::NONE);


	App->render->camera.x = 300 * SCREEN_SIZE;
	App->render->camera.y = 2690 * SCREEN_SIZE;

	App->player->position.x = 400;
	App->player->position.y = 2880;

	App->player->score = App->player->score;

	App->player->Enable();
	App->enemies->Enable();

	App->player->cameraXlimitation = false;
	App->player->cameraYlimitation = false;

	SceneCounter = 0;

	return ret;
}

Update_Status SceneLevel2::Update()
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

	if (App->player->playerDelay >= 420 && App->player->destroyed == true)
	{
		App->fade->FadeToBlack((Module*)App->sceneLevel_2, (Module*)App->sceneIntro, 30);
	}

	if (App->input->keys[SDL_SCANCODE_F4] == Key_State::KEY_DOWN)
	{
		App->player->playerDelay = 0;
		App->player->activateWinCondition_FINAL = true;

	}

	if (App->player->activateWinCondition_FINAL == true || App->player->destroyed == true)
	{
		SceneCounter = 0;
	}
	else
	{
		SceneCounter++;
	}

	if ((App->player->bossZoneEvent == true)&&(App->enemies->AlreadySpawned!=true))
	{
		App->enemies->AddEnemy(Enemy_Type::BOSS, 756 - 120, 50 - 1100);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel2::PostUpdate()
{
	// Draw everything --------------------------------------
	//App->render->Blit(bgTexture, 0, -600, NULL, 0.53, true);
	//App->render->Blit(bgTexture, 512, -600, NULL, 0.53, true);
	App->render->Blit(Level2FullMapTexture, 0, 0, NULL, 1.0, true);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel2::CleanUp()
{
	
	//NULL COLLIDER --> (experimental test for camera functions and other mechanical stuff related with colliders)
	App->collisions->RemoveCollider(App->collisions->AddCollider({ 0, 0, 768, 3072 }, Collider::Type::NULL_COLLIDER));

	SDL_DestroyTexture(Level2FullMapTexture);
	SDL_free(Level2FullMapTexture);

	App->player->Disable();
	App->player->CleanUp();

	App->enemies->Disable();
	App->enemies->CleanUp();

	App->particles->Disable();
	App->particles->CleanUp();

	App->breakableParticles->Disable();
	App->breakableParticles->CleanUp();

	App->endPlane->Disable();
	App->endPlane->CleanUp();

	App->collisions->CleanUp();
	App->collisions->Disable();

	App->collisions->RemoveCollider(App->player->collider);

	return true;
}
