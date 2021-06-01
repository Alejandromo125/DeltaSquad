#include "Enemy_Soldier_Standing.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "p2Point.h"


Enemy_Soldier_Standing::Enemy_Soldier_Standing(int x, int y) : Enemy(x, y)
{
	
	Enemy::EnemyHP = 2;
	//SHOOTING ANIMATIONS
	Enemy2shootDown.PushBack({ 113,358,30,43 });
	Enemy2shootUp.PushBack({ 113,547,30,43 });
	Enemy2shootRight.PushBack({ 113,448,30,43 });
	Enemy2shootLeft.PushBack({ 113,495,30,43 });
	Enemy2shootUpRight.PushBack({ 113,598,30,43 });
	Enemy2shootUpLeft.PushBack({ 113,647,30,43 });
	Enemy2shootDownRight.PushBack({ 113,403,30,43 });
	Enemy2shootDownLeft.PushBack({ 113,314,30,43 });

	//Have the Soldiers describe a path in the screen taking into account the collisions


	collider = App->collisions->AddCollider({ position.x, position.y, 20, 30 }, Collider::Type::ENEMY, (Module*)App->enemies);

	

}

void Enemy_Soldier_Standing::Update()
{

	

	counterEnemy2++;

	if (App->player->position.y < position.y)
	{
		currentAnim = &Enemy2shootUp;
	}

	if (App->player->position.y > position.y)
	{

		currentAnim = &Enemy2shootDown;
	}

	if (App->player->position.x < position.x)
	{
		currentAnim = &Enemy2shootLeft;

	}
	if (App->player->position.x > position.x)
	{
		currentAnim = &Enemy2shootRight;
	}

	if ((App->player->position.y < position.y) && (App->player->position.x < position.x))
	{
		currentAnim = &Enemy2shootUpLeft;
	}

	if ((App->player->position.x > position.x) && (App->player->position.y < position.y))
	{
		currentAnim = &Enemy2shootUpRight;
	}

	if ((App->player->position.y > position.y) && (App->player->position.x > position.x))
	{
		currentAnim = &Enemy2shootDownRight;
	}

	if ((App->player->position.x < position.x) && (App->player->position.y > position.y))
	{
		currentAnim = &Enemy2shootDownLeft;
	}


	if (counterEnemy2 % 60 == 0)
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
	if (counterEnemy2 % 200 == 0)
	{
		//DIAGONAL SHOT IMPLEMENTATION
	
		if (position.DistanceTo(App->player->position) < 250)
		{

		}if ((position.x > App->player->position.x) && (position.y > App->player->position.y))
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







	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}