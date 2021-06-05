#include "Tower_Enemy_Level2.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleInput.h"
#include "ModuleBreakable.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "p2Point.h"


TowerEnemy::TowerEnemy(int x, int y) : Enemy(x, y)
{

	Enemy::EnemyHP = 15;
	//SHOOTING ANIMATIONS
	ShootDown.PushBack({ 0,861,89,161 });
	ShootRight.PushBack({ 94,861,89,161 });
	ShootLeft.PushBack({ 188,861,89,161 });
	ShootDownRight.PushBack({ 288,861,89,161 });
	ShootDownLeft.PushBack({ 375,861,89,161 });

	//Have the Soldiers describe a path in the screen taking into account the collisions


	collider = App->collisions->AddCollider({ position.x, position.y, 86, 92 }, Collider::Type::TOWER_ENEMY, (Module*)App->enemies);



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
				currentAnim = &ShootDown;
				App->particles->AddParticle(App->particles->shotEffect, position.x + 5, position.y + 25, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotDown, position.x + 5, position.y + 15, Collider::Type::ENEMY_SHOT);
				currentAnim = &ShootDown;
				App->particles->AddParticle(App->particles->shotEffect, position.x + 5, position.y + 25, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotDown, position.x + 5, position.y + 15, Collider::Type::ENEMY_SHOT);


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


			if ((position.x > App->player->position.x) && (position.y < App->player->position.y))
			{
				currentAnim = &ShootDownLeft;
				App->particles->AddParticle(App->particles->shotEffect, position.x - 8, position.y + 20, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotDownLeft, position.x - 3, position.y + 20, Collider::Type::ENEMY_SHOT);
				currentAnim = &ShootDownLeft;
				App->particles->AddParticle(App->particles->shotEffect, position.x + 8, position.y + 20, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotDownLeft, position.x + 3, position.y + 20, Collider::Type::ENEMY_SHOT);


			}
			if ((position.x < App->player->position.x) && (position.y < App->player->position.y))
			{
				currentAnim = &ShootDownRight;
				App->particles->AddParticle(App->particles->shotEffect, position.x + 8, position.y + 15, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotDownRight, position.x + 8, position.y + 15, Collider::Type::ENEMY_SHOT);
				currentAnim = &ShootDownRight;
				App->particles->AddParticle(App->particles->shotEffect, position.x - 8, position.y + 15, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->EnemyshotDownRight, position.x - 8, position.y + 15, Collider::Type::ENEMY_SHOT);


			}
		}

	}

	if (EnemyHP <= 0)
	{
		App->audio->PlayFx(App->breakableParticles->broken04);
		App->input->ShakeController(0, 500, 0.3f);

		App->particles->AddParticle(App->particles->explosion, position.x + 10, position.y + 10);
		App->particles->AddParticle(App->particles->explosion, position.x + 50, position.y + 80);
		App->particles->AddParticle(App->particles->explosion, position.x + 70, position.y + 40);

		App->particles->AddParticle(App->particles->explosion, position.x + 20, position.y + 40, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->explosion, position.x + 40, position.y + 60, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->explosion, position.x + 30, position.y + 90, Collider::Type::NONE);
		App->particles->AddParticle(App->particles->explosion, position.x + 80, position.y + 70, Collider::Type::NONE, 5);
		App->particles->AddParticle(App->particles->explosion, position.x + 10, position.y + 100, Collider::Type::NONE, 5);
		App->particles->AddParticle(App->particles->explosion, position.x + 100, position.y + 20, Collider::Type::NONE, 5);
		App->particles->AddParticle(App->particles->explosion, position.x + 60, position.y + 10, Collider::Type::NONE, 10);
		App->particles->AddParticle(App->particles->explosion, position.x + 50, position.y + 20, Collider::Type::NONE, 10);
		App->particles->AddParticle(App->particles->explosion, position.x + 70, position.y + 80, Collider::Type::NONE, 10);

	}





	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}