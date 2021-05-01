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

	//Water Colliders
	App->collisions->AddCollider({ 160, 1480, 590, 20 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 250, 1450, 500, 20 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 270, 1420, 480, 40 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 270, 1400, 20, 30 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 300, 1410, 450, 10 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 360, 1390, 390, 20 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 400, 1350, 350, 40 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 490, 1330, 260, 20 }, Collider::Type::WATER);
	App->collisions->AddCollider({ 520, 1310, 230, 20 }, Collider::Type::WATER);

	//Wall Colliders
	App->collisions->AddCollider({ 100, 1130, 20, 90 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 20, 70, 90, 20 }, Collider::Type::WALL); // Test
	App->collisions->AddCollider({ 120, 1130, 50, 80 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 170, 1130, 10, 70 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 180, 1130, 60, 60 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 240, 1130, 40, 50 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 280, 1130, 10, 40 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 290, 1130, 30, 30 }, Collider::Type::WALL);
	App->collisions->AddCollider({ 100, 1110, 230, 20 }, Collider::Type::WALL);

	// Enemies ---
	App->enemies->AddEnemy(Enemy_Type::SOLDIER, 100, 40);
	

	//App->render->camera.x = 0;
	//App->render->camera.y = 0;

	App->render->camera.x = App->player->position.x - ((SCREEN_WIDTH / 2));
	App->render->camera.y = App->player->position.y - ((SCREEN_HEIGHT / 2));

	App->player->Enable();
	App->enemies->Enable();

	return ret;
}

Update_Status SceneLevel1::Update()
{
	//App->render->camera.x = App->player->position.x - ((SCREEN_WIDTH / 2));
	//App->render->camera.y = App->player->position.y - ((SCREEN_HEIGHT / 2));

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