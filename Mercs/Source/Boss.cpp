#include "Boss.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "p2Point.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"

Boss::Boss(int x, int y) : Enemy(x, y)
{
	Enemy::EnemyHP = 10;
	Idle.PushBack({ 0,0,128,102 });
	Idle.loop = true;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	

	//SHOOTING ANIMATIONS
	Shot.PushBack({ 0,0,128,102 });
	Shot.PushBack({ 140,0,128,102 });
	Shot.PushBack({ 280,0,128,102 });
	Shot.loop = true;

	


	collider = App->collisions->AddCollider({ position.x, position.y, 128, 102 }, Collider::Type::BOSS, (Module*)App->enemies);

}

void Boss::Update()
{
	currentAnim = &Idle;
	counter++;
	int half = position.x + 64;
	
	if (counter % 2 == 0)
	{
		if (position.DistanceTo(App->player->position) < 250)
		{
			if ((half > App->player->position.x) && (position.y < App->player->position.y))
			{
				currentAnim = &Shot;
				position.x--;


			}
			if ((half < App->player->position.x) && (position.y < App->player->position.y))
			{
				currentAnim = &Shot;
				position.x++;
			}
		}
	}
		
	
	

	if (counter % 60 == 0)
	{
		if (position.DistanceTo(App->player->position) < 250)
		{

			if ((position.x == App->player->position.x) && (position.y < App->player->position.y))
			{
				currentAnim = &Shot;
				App->particles->AddParticle(App->particles->shotEffect, position.x, position.y + 25, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotDown, position.x + 5, position.y + 15, Collider::Type::ENEMY_SHOT);
				


			}
		}
		//DIAGONAL SHOT IMPLEMENTATION
		if (position.DistanceTo(App->player->position) < 250)
		{

			
			if ((position.x > App->player->position.x) && (position.y < App->player->position.y))
			{
				currentAnim = &Shot;
				App->particles->AddParticle(App->particles->shotEffect, position.x, position.y + 20, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotDownLeft, position.x - 3, position.y + 20, Collider::Type::ENEMY_SHOT);
				


			}
			if ((position.x  < App->player->position.x) && (position.y < App->player->position.y))
			{
				currentAnim = &Shot;
				App->particles->AddParticle(App->particles->shotEffect, position.x, position.y + 15, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotDownRight, position.x + 8, position.y + 15, Collider::Type::ENEMY_SHOT);
				

			}
		}

	}
	if (EnemyHP == 0) App->player->activateWinCondition = true;
	
		if (App->player->activateWinCondition == true)
		{
			App->player->activateWinCondition = false;
			App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 90);
			App->fade->FadeToBlack((Module*)App->player, (Module*)App->sceneIntro, 90);
		}
	
	

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}