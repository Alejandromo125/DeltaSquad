#include "Boss.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "p2Point.h"


Boss::Boss(int x, int y) : Enemy(x, y)
{
	Enemy::EnemyHP = 10;
	Idle.PushBack({ 0,0,128,102 });
	Idle.loop = true;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	path.PushBack({ 1.0f, 0.5f }, 20,(&(Animation)Idle));
	path.PushBack({ 0.0f, 0.0f }, 20, (&(Animation)Idle));
	path.PushBack({ 1.0f, -0.5f }, 20,(&(Animation)Idle));
	path.PushBack({ 0.0f, 0.0f }, 20, (&(Animation)Idle));
	path.PushBack({ -1.0f, 0.5f }, 20,(&(Animation)Idle));
	path.PushBack({ 0.0f, 0.0f }, 20, (&(Animation)Idle));
	path.PushBack({ -1.0f, -0.5f }, 20, (&(Animation)Idle));
	path.PushBack({ 0.0f, 0.0f }, 20, (&(Animation)Idle));

	//SHOOTING ANIMATIONS
	Shot.PushBack({ 0,0,128,102 });
	Shot.PushBack({ 140,0,128,102 });
	Shot.PushBack({ 280,0,128,102 });
	Shot.loop = true;

	


	collider = App->collisions->AddCollider({ position.x, position.y, 128, 102 }, Collider::Type::BOSS, (Module*)App->enemies);

}

void Boss::Update()
{

	counter++;

	if (counter % 60 == 0)
	{
		if (position.DistanceTo(App->player->position) < 250)
		{

			if ((position.x == App->player->position.x) && (position.y < App->player->position.y))
			{
				currentAnim = &Shot;
				App->particles->AddParticle(App->particles->shotEffect, position.x + 5, position.y + 25, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotDown, position.x + 5, position.y + 15, Collider::Type::ENEMY_SHOT);


			}
		}
		//DIAGONAL SHOT IMPLEMENTATION
		if (position.DistanceTo(App->player->position) < 250)
		{

			
			if ((position.x > App->player->position.x) && (position.y < App->player->position.y))
			{
				currentAnim = &Shot;
				App->particles->AddParticle(App->particles->shotEffect, position.x - 8, position.y + 20, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotDownLeft, position.x - 3, position.y + 20, Collider::Type::ENEMY_SHOT);


			}
			if ((position.x < App->player->position.x) && (position.y < App->player->position.y))
			{
				currentAnim = &Shot;
				App->particles->AddParticle(App->particles->shotEffect, position.x + 8, position.y + 15, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotDownRight, position.x + 8, position.y + 15, Collider::Type::ENEMY_SHOT);


			}
		}

	}



	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}