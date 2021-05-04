#include "Enemy_Soldier.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "p2Point.h"


Enemy_Soldier::Enemy_Soldier(int x, int y) : Enemy(x, y)
{	
	walkUp.speed = 0.1f;
	walkDown.speed = 0.1f;
	walkRight.speed = 0.1f;
	walkUpLeft.speed = 0.1f;
	walkUpRight.speed = 0.1f;
	walkDownLeft.speed = 0.1f;
	walkDownRight.speed = 0.1f;

	
	//WALKING ANIMATIONS
	walkUp.PushBack({ 113,547,30,43 });
	walkUp.PushBack({ 73,547,30,43 });
	walkUp.PushBack({ 35,547,30,43 });
	walkUp.loop = true;

	walkDown.PushBack({ 113,358,30,43 });
	walkDown.PushBack({ 76,358,30,43 });
	walkDown.PushBack({ 40,358,30,43 });
	walkDown.loop = true;

	walkRight.PushBack({ 113,448,30,43 });
	walkRight.PushBack({ 73,448,30,43 });
	walkRight.loop = true;

	walkLeft.PushBack({ 113,495,30,43 });
	walkLeft.PushBack({ 73,495,30,43 });
	walkLeft.loop = true;

	walkUpRight.PushBack({ 113,598,30,43 });
	walkUpRight.PushBack({ 73,598,30,43 });
	walkUpRight.PushBack({ 35,598,30,43 });
	walkUpRight.loop = true;

	walkUpLeft.PushBack({ 113,647,30,43 });
	walkUpLeft.PushBack({ 73,647,30,43 });
	walkUpLeft.PushBack({ 35,647,30,43 });
	walkUpLeft.loop = true;

	walkDownRight.PushBack({ 75,403,30,43 });
	walkDownRight.PushBack({ 40,403,30,43 });
	walkDownRight.PushBack({ 5,403,30,43 });
	walkDownRight.loop = true;

	walkDownLeft.PushBack({ 75,314,30,43 });
	walkDownLeft.PushBack({ 38,314,30,43 });
	walkDownLeft.PushBack({ 3,314,30,43 });
	walkDownLeft.loop = true;

	//SHOOTING ANIMATIONS
	shootDown.PushBack({113,358,30,43});
	shootUp.PushBack({ 113,547,30,43 });
	shootRight.PushBack({ 113,448,30,43 });
	shootLeft.PushBack({ 113,495,30,43 });
	shootUpRight.PushBack({ 113,598,30,43 });
	shootUpLeft.PushBack({ 113,647,30,43 });
	shootDownRight.PushBack({ 113,403,30,43 });
	shootDownLeft.PushBack({ 113,314,30,43 });
	
	//Have the Soldiers describe a path in the screen taking into account the collisions
	

	collider = App->collisions->AddCollider({position.x, position.y, 20, 30}, Collider::Type::ENEMY, (Module*)App->enemies);
	
	
	EnemyShot = App->audio->LoadFx("Assets/FX/06.wav");
}

void Enemy_Soldier::Update()
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
		
	
		
	
	
		if (counter % 30 == 0)
		{
			if (position.DistanceTo(App->player->position) < 250)
			{

				

				if ((position.x == App->player->position.x) && (position.y < App->player->position.y))
				{
					App->audio->PlayFx(EnemyShot);
					App->particles->AddParticle(App->particles->shotEffect, position.x + 5, position.y + 25, Collider::Type::NONE);
					App->particles->AddParticle(App->particles->EnemyshotDown, position.x + 5, position.y + 15, Collider::Type::ENEMY_SHOT);


				}
				if ((position.x == App->player->position.x) && (position.y > App->player->position.y))
				{
					App->audio->PlayFx(EnemyShot);
					App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
					App->particles->AddParticle(App->particles->EnemyshotUp, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);

				}
				if ((position.x < App->player->position.x) && (position.y == App->player->position.y))
				{

					App->audio->PlayFx(EnemyShot);
					App->particles->AddParticle(App->particles->shotEffect, position.x + 25, position.y + 8, Collider::Type::NONE);
					App->particles->AddParticle(App->particles->EnemyshotRight, position.x + 18, position.y + 8, Collider::Type::ENEMY_SHOT);



				}
				if ((position.x > App->player->position.x) && (position.y == App->player->position.y))
				{
					App->audio->PlayFx(EnemyShot);
					App->particles->AddParticle(App->particles->shotEffect, position.x - 8, position.y + 8, Collider::Type::NONE);
					App->particles->AddParticle(App->particles->EnemyshotLeft, position.x - 3, position.y + 8, Collider::Type::ENEMY_SHOT);


				}
				
			}
		}
		if (counter % 100 == 0)
		{
			//DIAGONAL SHOT IMPLEMENTATION
			if (position.DistanceTo(App->player->position) < 250)
			{
				if ((position.x > App->player->position.x) && (position.y > App->player->position.y))
				{
					App->audio->PlayFx(EnemyShot);
					App->particles->AddParticle(App->particles->shotEffect, position.x - 8, position.y + 8, Collider::Type::NONE);
					App->particles->AddParticle(App->particles->EnemyshotUpLeft, position.x - 3, position.y + 8, Collider::Type::ENEMY_SHOT);


				}
				if ((position.x > App->player->position.x) && (position.y < App->player->position.y))
				{
					App->audio->PlayFx(EnemyShot);
					App->particles->AddParticle(App->particles->shotEffect, position.x - 8, position.y + 20, Collider::Type::NONE);
					App->particles->AddParticle(App->particles->EnemyshotDownLeft, position.x - 3, position.y + 20, Collider::Type::ENEMY_SHOT);


				}
				if ((position.x < App->player->position.x) && (position.y > App->player->position.y))
				{
					App->audio->PlayFx(EnemyShot);
					App->particles->AddParticle(App->particles->shotEffect, position.x + 20, position.y + 8, Collider::Type::NONE);
					App->particles->AddParticle(App->particles->EnemyshotUpRight, position.x + 20, position.y + 8, Collider::Type::ENEMY_SHOT);


				}
				if ((position.x < App->player->position.x) && (position.y < App->player->position.y))
				{
					App->audio->PlayFx(EnemyShot);
					App->particles->AddParticle(App->particles->shotEffect, position.x + 8, position.y + 15, Collider::Type::NONE);
					App->particles->AddParticle(App->particles->EnemyshotDownRight, position.x + 8, position.y + 15, Collider::Type::ENEMY_SHOT);


				}
			}
			
		}
	
	
		
	
		
	
	
	
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
