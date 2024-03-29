#include "ModuleEnemies.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

#include "Enemy.h"
#include "Enemy_Soldier.h"
#include "Enemy_Soldier_Standing.h"
#include "Enemy_Soldier_Level2.h"
#include "Boss.h"
#include "Tower_Enemy_Level2.h"
#include "Enemy_car.h"

#define SPAWN_MARGIN 50


ModuleEnemies::ModuleEnemies(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{

}

bool ModuleEnemies::Start()
{
	texture = App->textures->Load("Assets/Art/Sprites/soldier.png");
	
	enemyDestroyedFx = App->audio->LoadFx("Assets/FX/22.wav");

	return true;
}


Update_Status ModuleEnemies::PreUpdate()
{
	// Remove all enemies scheduled for deletion
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->pendingToDelete)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::Update()
{
	HandleEnemiesSpawn();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
			enemies[i]->Update();
	}

	HandleEnemiesDespawn();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleEnemies::PostUpdate()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
			enemies[i]->Draw();
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(Enemy_Type type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(spawnQueue[i].type == Enemy_Type::NO_TYPE)
		{
			spawnQueue[i].type = type;
			spawnQueue[i].x = x;
			spawnQueue[i].y = y;
			ret = true;
			break;
		}
	}
	if (type == Enemy_Type::BOSS)
	{
		for (uint i = 0; i < 1; ++i)
		{
			if (spawnQueue[i].type == Enemy_Type::NO_TYPE)
			{
				spawnQueue[i].type = type;
				spawnQueue[i].x = x;
				spawnQueue[i].y = y;
				ret = true;
				break;
			}
		}
	}

	return ret;
}

void ModuleEnemies::HandleEnemiesSpawn()
{
	// Iterate all the enemies queue
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (spawnQueue[i].type != Enemy_Type::NO_TYPE)
		{
			// Spawn a new enemy if the screen has reached a spawn position
			if ((spawnQueue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN) || (spawnQueue[i].x * SCREEN_SIZE > App->render->camera.x - (App->render->camera.w * SCREEN_SIZE) - SPAWN_MARGIN) || (spawnQueue[i].y * SCREEN_SIZE < App->render->camera.y - (App->render->camera.h * SCREEN_SIZE) - SPAWN_MARGIN))
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
			/*
			if (spawnQueue[i].x * SCREEN_SIZE > App->render->camera.x - (App->render->camera.w * SCREEN_SIZE) - SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].x * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
			if (spawnQueue[i].y * SCREEN_SIZE > App->render->camera.y - (App->render->camera.h * SCREEN_SIZE) - SPAWN_MARGIN)
			{
				LOG("Spawning enemy at %d", spawnQueue[i].y * SCREEN_SIZE);

				SpawnEnemy(spawnQueue[i]);
				spawnQueue[i].type = Enemy_Type::NO_TYPE; // Removing the newly spawned enemy from the queue
			}
			*/
		}
	}
}

void ModuleEnemies::HandleEnemiesDespawn()
{
	// Iterate existing enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			// Delete the enemy when it has reached the end of the screen
			if (enemies[i]->position.y * SCREEN_SIZE > (App->render->camera.y + SCREEN_HEIGHT * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);

				enemies[i]->SetToDelete();
			}
			
		}
	}
}

void ModuleEnemies::SpawnEnemy(const EnemySpawnpoint& info)
{
	// Find an empty slot in the enemies array
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		
		if (enemies[i] == nullptr)
		{
			switch (info.type)
			{
				case Enemy_Type::SOLDIER:
					enemies[i] = new Enemy_Soldier(info.x, info.y);
					break;
				case Enemy_Type::SOLDIER2:
					enemies[i] = new Enemy_Soldier_Standing(info.x, info.y);
					break;
				case Enemy_Type::SOLDIER_LEVEL2:
					enemies[i] = new Enemy_Soldier_Level2(info.x, info.y);
					break;
				case Enemy_Type::BOSS:
					enemies[i] = new Boss(info.x, info.y);
					break;
				case Enemy_Type::TOWER_ENEMY:
					enemies[i] = new TowerEnemy(info.x, info.y);
					break; 
				case Enemy_Type::ENEMY_CAR:
						enemies[i] = new Enemy_car(info.x, info.y);
						break;

			}
			enemies[i]->texture = texture;
			enemies[i]->destroyedFx = enemyDestroyedFx;
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2); //Notify the enemy of a collision
			break;
		}
	}
	
}