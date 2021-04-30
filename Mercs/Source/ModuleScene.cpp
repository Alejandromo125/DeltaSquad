#include "ModuleScene.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

ModuleScene::ModuleScene(bool startEnabled) : Module(startEnabled)
{

}

ModuleScene::~ModuleScene()
{

}

// Load assets
bool ModuleScene::Start()
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
	App->enemies->AddEnemy(ENEMY_TYPE::SOLDIER, 100, 40);
	//App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 625, 80);
	//App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 640, 80);
	//App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 665, 80);

	// Add a new wave of red birds
	//App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 860, 125);
	//App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 885, 125);
	//App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 910, 125);
	//App->enemies->AddEnemy(ENEMY_TYPE::REDBIRD, 935, 125);
	
	// Add a new wave of brown cookies
	//App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 700, 100);
	//App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 715, 100);
	//App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 730, 100);
	//App->enemies->AddEnemy(ENEMY_TYPE::BROWNSHIP, 745, 100);

	// Create a new enemy type: The Mech
	//App->enemies->AddEnemy(ENEMY_TYPE::MECH, 970, 220 - 32);

	App->player->Enable();
	App->enemies->Enable();

	return ret;
}

update_status ModuleScene::Update()
{
	//App->render->camera.x = App->player->position.x - 200;
	//App->render->camera.y = App->player->position.y - 100;

	return update_status::UPDATE_CONTINUE;
}

// Update: draw background
update_status ModuleScene::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, -600, NULL, true);
	App->render->Blit(bgTexture, 512, -600, NULL, true);
	App->render->Blit(Level1FullMapTexture, -120, -1100, NULL, 2.0, true);

	return update_status::UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
	App->player->Disable();
	App->enemies->Disable();

	return true;
}