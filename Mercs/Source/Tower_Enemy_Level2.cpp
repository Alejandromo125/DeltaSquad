#include "Tower_Enemy_Level2.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "p2Point.h"


TowerEnemy::TowerEnemy(int x, int y) : Enemy(x, y)
{

	Enemy::EnemyHP = 5;
	//SHOOTING ANIMATIONS
	ShootDown.PushBack({ 113,358,30,43 });
	ShootRight.PushBack({ 113,448,30,43 });
	ShootLeft.PushBack({ 113,495,30,43 });
	ShootDownRight.PushBack({ 113,403,30,43 });
	ShootDownLeft.PushBack({ 113,314,30,43 });

	//Have the Soldiers describe a path in the screen taking into account the collisions


	collider = App->collisions->AddCollider({ position.x, position.y, 20, 30 }, Collider::Type::ENEMY, (Module*)App->enemies);



}

void TowerEnemy::Update()
{



	counter++;

	if (App->player->position.y > position.y)
	{

		currentAnim = &ShootDown;
	}

	if (App->player->position.x < position.x)
	{
		currentAnim = &ShootLeft;

	}
	if (App->player->position.x > position.x)
	{
		currentAnim = &ShootRight;
	}

	if ((App->player->position.y > position.y) && (App->player->position.x > position.x))
	{
		currentAnim = &ShootDownRight;
	}

	if ((App->player->position.x < position.x) && (App->player->position.y > position.y))
	{
		currentAnim = &ShootDownLeft;
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