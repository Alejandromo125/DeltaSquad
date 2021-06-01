#include "Enemy_Soldier_Level2.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "p2Point.h"


Enemy_Soldier_Level2::Enemy_Soldier_Level2(int x, int y) : Enemy(x, y)
{
	walkUp_Soldier_Level2.speed = 0.1f;
	walkDown_Soldier_Level2.speed = 0.1f;
	walkRight_Soldier_Level2.speed = 0.1f;
	walkUpLeft_Soldier_Level2.speed = 0.1f;
	walkUpRight_Soldier_Level2.speed = 0.1f;
	walkDownLeft_Soldier_Level2.speed = 0.1f;
	walkDownRight_Soldier_Level2.speed = 0.1f;


	//WALKING ANIMATIONS
	walkUp_Soldier_Level2.PushBack({ 418,547,30,43 });
	walkUp_Soldier_Level2.PushBack({ 378,547,30,43 });
	walkUp_Soldier_Level2.PushBack({ 340,547,30,43 });
	walkUp_Soldier_Level2.loop = true;

	walkDown_Soldier_Level2.PushBack({ 57,180,30,43 });
	walkDown_Soldier_Level2.PushBack({ 76,358,30,43 });
	walkDown_Soldier_Level2.PushBack({ 345,358,30,43 });
	walkDown_Soldier_Level2.loop = true;

	walkRight_Soldier_Level2.PushBack({ 418,448,30,43 });
	walkRight_Soldier_Level2.PushBack({ 378,448,30,43 });
	walkRight_Soldier_Level2.PushBack({ 418,448,30,43 });
	walkRight_Soldier_Level2.PushBack({ 378,448,30,43 });
	walkRight_Soldier_Level2.loop = true;

	walkLeft_Soldier_Level2.PushBack({ 418,495,30,43 });
	walkLeft_Soldier_Level2.PushBack({ 378,495,30,43 });
	walkLeft_Soldier_Level2.PushBack({ 418,495,30,43 });
	walkLeft_Soldier_Level2.PushBack({ 378,495,30,43 });
	walkLeft_Soldier_Level2.loop = true;

	walkUpRight_Soldier_Level2.PushBack({ 418,598,30,43 });
	walkUpRight_Soldier_Level2.PushBack({ 378,598,30,43 });
	walkUpRight_Soldier_Level2.PushBack({ 340,598,30,43 });
	walkUpRight_Soldier_Level2.PushBack({ 418,598,30,43 });
	walkUpRight_Soldier_Level2.loop = true;

	walkUpLeft_Soldier_Level2.PushBack({ 418,647,30,43 });
	walkUpLeft_Soldier_Level2.PushBack({ 378,647,30,43 });
	walkUpLeft_Soldier_Level2.PushBack({ 340,647,30,43 });
	walkUpLeft_Soldier_Level2.PushBack({ 418,647,30,43 });
	walkUpLeft_Soldier_Level2.loop = true;

	walkDownRight_Soldier_Level2.PushBack({ 380,403,30,43 });
	walkDownRight_Soldier_Level2.PushBack({ 345,403,30,43 });
	walkDownRight_Soldier_Level2.PushBack({ 310,403,30,43 });
	walkDownRight_Soldier_Level2.PushBack({ 380,403,30,43 });
	walkDownRight_Soldier_Level2.loop = true;

	walkDownLeft_Soldier_Level2.PushBack({ 380,314,30,43 });
	walkDownLeft_Soldier_Level2.PushBack({ 343,314,30,43 });
	walkDownLeft_Soldier_Level2.PushBack({ 308,314,30,43 });
	walkDownLeft_Soldier_Level2.PushBack({ 380,314,30,43 });
	walkDownLeft_Soldier_Level2.loop = true;

	//SHOOTING ANIMATIONS
	shootDown_Soldier_Level2.PushBack({ 418,358,30,43 });
	shootDown_Soldier_Level2.PushBack({ 418,547,30,43 });
	shootDown_Soldier_Level2.PushBack({ 418,448,30,43 });
	shootDown_Soldier_Level2.PushBack({ 418,495,30,43 });
	shootDown_Soldier_Level2.PushBack({ 418,598,30,43 });
	shootDown_Soldier_Level2.PushBack({ 418,647,30,43 });
	shootDown_Soldier_Level2.PushBack({ 418,403,30,43 });
	shootDown_Soldier_Level2.PushBack({ 418,314,30,43 });

	//Have the Soldiers describe a path in the screen taking into account the collisions


	collider = App->collisions->AddCollider({ position.x, position.y, 20, 30 }, Collider::Type::ENEMY, (Module*)App->enemies);



}

void Enemy_Soldier_Level2::Update()
{



	counter++;
	if (position.DistanceTo(App->player->position) < 250)
	{
		if (counter % 10 == 0)
		{
			if (App->player->position.y < position.y)
			{
				currentAnim = &walkUp_Soldier_Level2;
				position.y = position.y - 1;
				App->player->EnemyLookingPosition = 1;
			}

			if (App->player->position.y > position.y)
			{

				currentAnim = &walkDown_Soldier_Level2;
				position.y = position.y + 1;
				App->player->EnemyLookingPosition = 2;
			}

			if (App->player->position.x < position.x)
			{

				currentAnim = &walkLeft_Soldier_Level2;
				position.x = position.x - 1;
				App->player->EnemyLookingPosition = 3;

			}
			if (App->player->position.x > position.x)
			{
				currentAnim = &walkRight_Soldier_Level2;
				position.x = position.x + 1;
				App->player->EnemyLookingPosition = 4;
			}

			if ((App->player->position.y < position.y) && (App->player->position.x < position.x))
			{
				currentAnim = &walkUpLeft_Soldier_Level2;
				position.y = position.y - 1;
				position.x = position.x - 1;
				App->player->EnemyLookingPosition = 5;

			}

			if ((App->player->position.x > position.x) && (App->player->position.y < position.y))
			{
				currentAnim = &walkUpRight_Soldier_Level2;
				position.x = position.x + 1;
				position.y = position.y - 1;
				App->player->EnemyLookingPosition = 6;
			}

			if ((App->player->position.y > position.y) && (App->player->position.x > position.x))
			{
				currentAnim = &walkDownRight_Soldier_Level2;
				position.y = position.y + 1;
				position.x = position.x + 1;
				App->player->EnemyLookingPosition = 7;
			}

			if ((App->player->position.x < position.x) && (App->player->position.y > position.y))
			{

				currentAnim = &walkDownLeft_Soldier_Level2;
				position.x = position.x - 1;
				position.y = position.y + 1;
				App->player->EnemyLookingPosition = 8;
			}
		}
	}





	if (counter % 60 == 0)
	{
		if (position.DistanceTo(App->player->position) < 250)
		{



			if ((position.x == App->player->position.x) && (position.y < App->player->position.y))
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x + 5, position.y + 25, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotDown, position.x + 5, position.y + 15, Collider::Type::ENEMY_SHOT);


			}
			if ((position.x == App->player->position.x) && (position.y > App->player->position.y))
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotUp, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);

			}
			if ((position.x < App->player->position.x) && (position.y == App->player->position.y))
			{

				App->particles->AddParticle(App->particles->shotEffect, position.x + 25, position.y + 8, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotRight, position.x + 18, position.y + 8, Collider::Type::ENEMY_SHOT);



			}
			if ((position.x > App->player->position.x) && (position.y == App->player->position.y))
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x - 8, position.y + 8, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotLeft, position.x - 3, position.y + 8, Collider::Type::ENEMY_SHOT);


			}

		}
	}
	if (counter % 200 == 0)
	{
		//DIAGONAL SHOT IMPLEMENTATION
		if (position.DistanceTo(App->player->position) < 250)
		{
			if ((position.x > App->player->position.x) && (position.y > App->player->position.y))
			{

				App->particles->AddParticle(App->particles->shotEffect, position.x - 8, position.y + 8, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotUpLeft, position.x - 3, position.y + 8, Collider::Type::ENEMY_SHOT);


			}
			if ((position.x > App->player->position.x) && (position.y < App->player->position.y))
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x - 8, position.y + 20, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotDownLeft, position.x - 3, position.y + 20, Collider::Type::ENEMY_SHOT);


			}
			if ((position.x < App->player->position.x) && (position.y > App->player->position.y))
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x + 20, position.y + 8, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotUpRight, position.x + 20, position.y + 8, Collider::Type::ENEMY_SHOT);


			}
			if ((position.x < App->player->position.x) && (position.y < App->player->position.y))
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x + 8, position.y + 15, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotDownRight, position.x + 8, position.y + 15, Collider::Type::ENEMY_SHOT);


			}
		}

	}








	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
