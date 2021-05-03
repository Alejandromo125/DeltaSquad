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

	
	path.PushBack({ 0.5f,0.0f }, 25, &walkRight);
	path.PushBack({ -0.5f,0.0f }, 25, &walkLeft);

	
	
		
		
	
	
	
	if ((this->collider->Intersects({ 100 - 120, 1120 - 1100, 70, 80 }))|| (this->collider->Intersects({ 170 - 120, 1120 - 1100, 10, 70 })))
	{
		if (currentAnim = &walkUp)
		{
			srand(NULL);
			int random = rand() % 5 + 1;
			if (random == 1)
			{
				path.steps->framesDuration = 50;
				path.PushBack({ 0.0f,0.5f }, 1000, &walkDown);
			}
			if (random == 2)
			{
				//walk Down Right
				path.PushBack({ 0.5f,0.5f }, 1000, &walkDownRight);
			}
			if (random == 3)
			{
				//walk Down Left
				path.PushBack({ -0.5f,0.5f }, 1000, &walkDownLeft);
			}
			if (random == 4)
			{
				//walk Left
				path.PushBack({ -0.5f,0.0f }, 1000, &walkLeft);
			}
			if (random == 5)
			{
				//walk Right
				path.PushBack({ 0.5f,0.0f }, 1000, &walkRight);
			}
		}
		if (currentAnim = &walkDown)
		{
			srand(NULL);
			int random = rand() % 5 + 1;
			if (random == 1)
			{
				path.PushBack({ 0.0f,-0.5f }, 50, &walkUp);
			}
			if (random == 2)
			{
				//walk Up Right
				path.PushBack({ 0.5f,-0.5f }, 1000, &walkUpRight);
			}
			if (random == 3)
			{
				//walk Up Left
				path.PushBack({ -0.5f,-0.5f }, 1000, &walkUpLeft);
			}
			if (random == 4)
			{
				//walk Left
				path.PushBack({ -0.5f,0.0f }, 1000, &walkLeft);
			}
			if (random == 5)
			{
				//walk Right
				path.PushBack({ 0.5f,0.0f }, 1000, &walkRight);
			}
		}
		if (currentAnim = &walkUpRight)
		{
			srand(NULL);
			int random = rand() % 5 + 1;
			if (random == 1)
			{
				path.PushBack({ 0.0f,0.5f }, 50, &walkDown);
			}
			if (random == 2)
			{
				//walk Down Right
				path.PushBack({ 0.5f,0.5f }, 1000, &walkDownRight);
			}
			if (random == 3)
			{
				//walk Down Left
				path.PushBack({ -0.5f,0.5f }, 1000, &walkDownLeft);
			}
			if (random == 4)
			{
				//walk Left
				path.PushBack({ -0.5f,0.0f }, 1000, &walkLeft);
			}
			if (random == 5)
			{
				//walk Right
				path.PushBack({ 0.5f,0.0f }, 1000, &walkRight);
			}
		}
		if (currentAnim = &walkUpLeft)
		{
			srand(NULL);
			int random = rand() % 5 + 1;
			if (random == 1)
			{
				path.PushBack({ 0.0f,0.5f }, 1000, &walkDown);
			}
			if (random == 2)
			{
				//walk Down Right
				path.PushBack({ 0.5f,0.5f }, 1000, &walkDownRight);
			}
			if (random == 3)
			{
				//walk Down Left
				path.PushBack({ -0.5f,0.5f }, 1000, & walkDownLeft);
			}
			if (random == 4)
			{
				//walk Left
				path.PushBack({ -0.5f,0.0f }, 1000, & walkLeft);
			}
			if (random == 5)
			{
				//walk Right
				path.PushBack({ 0.5f,0.0f }, 1000, & walkRight);
			}
		}
		if (currentAnim = &walkDownRight)
		{
			srand(NULL);
			int random = rand() % 5 + 1;
			if (random == 1)
			{
				path.PushBack({ 0.0f,-0.5f }, 1000, &walkUp);
			}
			if (random == 2)
			{
				//walk Up Right
				path.PushBack({ 0.5f,-0.05f }, 1000, & walkUpRight);
			}
			if (random == 3)
			{
				//walk Up Left
				path.PushBack({ -0.5f,-0.5f }, 1000, & walkUpLeft);
			}
			if (random == 4)
			{
				//walk Left
				path.PushBack({ -0.5f,0.0f }, 1000, & walkLeft);
			}
			if (random == 5)
			{
				//walk Right
				path.PushBack({ 0.5f,0.0f }, 1000, & walkRight);
			}
		}
		if (currentAnim = &walkDownLeft)
		{
			srand(NULL);
			int random = rand() % 5 + 1;
			if (random == 1)
			{
				path.PushBack({ 0.0f,-0.5f }, 1000, &walkUp);
			}
			if (random == 2)
			{
				//walk Up Right
				path.PushBack({ 0.5f,-0.05f }, 1000, & walkUpRight);
			}
			if (random == 3)
			{
				//walk Up Left
				path.PushBack({ -0.5f,-0.5f }, 1000, & walkUpLeft);
			}
			if (random == 4)
			{
				//walk Left
				path.PushBack({ -0.5f,0.0f }, 1000, & walkLeft);
			}
			if (random == 5)
			{
				//walk Right
				path.PushBack({ 0.5f,0.0f }, 1000, & walkRight);
			}
		}
		if (currentAnim = &walkLeft)
		{
			srand(NULL);
			int random = rand() % 5 + 1;
			if (random == 1)
			{
				path.PushBack({ 0.0f,-0.5f }, 1000, &walkUp);
			}
			if (random == 2)
			{
				//walk Up Right
				path.PushBack({ 0.5f,-0.5f }, 1000, & walkUpRight);
			}
			if (random == 3)
			{
				//walk Down Right
				path.PushBack({ 0.5f,0.5f }, 1000, & walkDownRight);
			}
			if (random == 4)
			{
				//walk Down
				path.PushBack({ 0.0f,0.5f }, 1000, & walkDown);
			}
			if (random == 5)
			{
				//walk Right
				path.PushBack({ 0.5f,0.0f }, 1000, & walkRight);
			}
		}
		if (currentAnim = &walkRight)
		{
			srand(NULL);
			int random = rand() % 5 + 1;
			if (random == 1)
			{
				path.PushBack({ 0.0f,0.5f }, 50, &walkUp);
			}
			if (random == 2)
			{
				//walk Up Left
				path.PushBack({ -0.5f,-0.5f }, 1000, & walkUpRight);
			}
			if (random == 3)
			{
				//walk Down Left
				path.PushBack({ -0.5f,0.5f }, 1000, & walkDownLeft);
			}
			if (random == 4)
			{
				//walk Down
				path.PushBack({ 0.0f,0.5f }, 1000, & walkDown);
			}
			if (random == 5)
			{
				//walk Left
				path.PushBack({ -0.5f,0.0f }, 1000, & walkLeft);
			}
		}
	}
	
}

void Enemy_Soldier::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();
	
	if (position.DistanceTo(App->player->position) < 150)
	{
		
		if ((position.x == App->player->position.x) && (position.y < App->player->position.y))
		{
			
			App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotDown, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
			
			
		}
		if ((position.x == App->player->position.x) && (position.y > App->player->position.y))
		{
			
			App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotUp, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
			
		}
		if ((position.x < App->player->position.x) && (position.y == App->player->position.y))
		{
			
			
			App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotRight, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
			
			
		
		}
		if ((position.x > App->player->position.x) && (position.y == App->player->position.y))
		{
			
			App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotLeft, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
			
			
		}
		/*
		if (((position.x < App->player->position.x) && (position.y < App->player->position.y)))
		{
			currentAnim == &shootDownRight;
			App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotDownRight, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
			
		}
		
		if ((position.x > App->player->position.x) && (position.y < App->player->position.y))
		{
			currentAnim == &shootDownLeft;
			App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotDownLeft, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
			path.Update();
		}
		if ((position.x < App->player->position.x) && (position.y > App->player->position.y))
		{
			currentAnim == &shootUpRight;
			App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotUpRight, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
			path.Update();
		}
		if ((position.x > App->player->position.x) && (position.y > App->player->position.y))
		{
			currentAnim == &shootUpLeft;
			App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotUpLeft, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
			path.Update();
		}
		*/
	}
	
	
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
