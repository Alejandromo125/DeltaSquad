#include "SceneLevel1.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

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

	//Bottomside collider
	//App->collisions->AddCollider({ 0, 224, 3930, 16 }, Collider::Type::WALL);

	//First two columns colliders
	//App->collisions->AddCollider({ 1375, 0, 111, 96 }, Collider::Type::WALL);
	//App->collisions->AddCollider({ 1375, 145, 111, 96 }, Collider::Type::WALL);

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::SOLDIER, 100, 40);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->Enable();
	App->enemies->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	//App->render->camera.x += 3;

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneLevel1::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, -600, NULL, true);
	App->render->Blit(bgTexture, 512, -600, NULL, true);
	App->render->Blit(Level1FullMapTexture, -120, -1100, NULL, 2.0, true);

	return Update_Status::UPDATE_CONTINUE;
}

bool SceneLevel1::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();

	return true;
}