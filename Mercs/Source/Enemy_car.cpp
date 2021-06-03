#include "Enemy_car.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "p2Point.h"


Enemy_car::Enemy_car(int x, int y) : Enemy(x, y)
{
	Enemy::EnemyHP = 5;
	walkUp.speed = 0.1f;
	walkDown.speed = 0.1f;
	walkRight.speed = 0.1f;
	walkUpLeft.speed = 0.1f;
	walkUpRight.speed = 0.1f;
	walkDownLeft.speed = 0.1f;
	walkDownRight.speed = 0.1f;


	//WALKING ANIMATIONS
	walkUp.PushBack({ 804,618,39,67 });
	walkUp.loop = true;

	walkDown.PushBack({ 798,933,38,89 });
	walkDown.loop = true;

	walkRight.PushBack({ 790,802,67,63 });
	walkRight.loop = true;

	walkLeft.PushBack({ 792,726,67,63 });
	walkLeft.loop = true;

	walkUpRight.PushBack({ 957,667,67,63 });
	walkUpRight.loop = true;

	walkUpLeft.PushBack({ 887,667,67,63 });
	walkUpLeft.loop = true;

	walkDownRight.PushBack({ 957,855,67,83 });
	walkDownRight.loop = true;

	walkDownLeft.PushBack({ 886,853,67,83 });
	walkDownLeft.loop = true;

	
	collider = App->collisions->AddCollider({ position.x, position.y, 20, 30 }, Collider::Type::ENEMY, (Module*)App->enemies);



}

void Enemy_car::Update()
{

	counter++;
	if (position.DistanceTo(App->player->position) < 250)
	{
		if (counter % 10 == 0)
		{
			if (App->player->position.y < position.y)
			{
				currentAnim = &walkUp;
				position.y = position.y - 1;
				App->player->EnemyLookingPosition = 1;
			}

			if (App->player->position.y > position.y)
			{

				currentAnim = &walkDown;
				position.y = position.y + 1;
				App->player->EnemyLookingPosition = 2;
			}

			if (App->player->position.x < position.x)
			{

				currentAnim = &walkLeft;
				position.x = position.x - 1;
				App->player->EnemyLookingPosition = 3;

			}
			if (App->player->position.x > position.x)
			{
				currentAnim = &walkRight;
				position.x = position.x + 1;
				App->player->EnemyLookingPosition = 4;
			}

			if ((App->player->position.y < position.y) && (App->player->position.x < position.x))
			{
				currentAnim = &walkUpLeft;
				position.y = position.y - 1;
				position.x = position.x - 1;
				App->player->EnemyLookingPosition = 5;

			}

			if ((App->player->position.x > position.x) && (App->player->position.y < position.y))
			{
				currentAnim = &walkUpRight;
				position.x = position.x + 1;
				position.y = position.y - 1;
				App->player->EnemyLookingPosition = 6;
			}

			if ((App->player->position.y > position.y) && (App->player->position.x > position.x))
			{
				currentAnim = &walkDownRight;
				position.y = position.y + 1;
				position.x = position.x + 1;
				App->player->EnemyLookingPosition = 7;
			}

			if ((App->player->position.x < position.x) && (App->player->position.y > position.y))
			{

				currentAnim = &walkDownLeft;
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