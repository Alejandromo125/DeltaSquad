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
	/*
	if ((App->player->position.x > position.x) && (App->player->position.y == position.y))
	{
		&Animation::HasFinished;
		path.PushBack({ 0.0f,0.5f },10,&walkRight);
		
	}
	if ((App->player->position.x < position.x) && (App->player->position.y == position.y))
	{
		&Animation::HasFinished;
		path.PushBack({ 0.0f,-0.5f },10, &walkLeft);
		
	}
	if ((App->player->position.y > position.y) && (App->player->position.x == position.x))
	{
		&Animation::HasFinished;
		path.PushBack({ 0.5f,0.0f },10, &walkDown);
		
	}
	if ((App->player->position.y < position.y) && (App->player->position.x == position.x))
	{
		&Animation::HasFinished;
		path.PushBack({ -0.5f,0.0f },10, &walkUp);
		
	}
	/*
	while ((App->player->position.y < position.y) && (App->player->position.x < position.x))
	{
		path.PushBack({ -0.5f,-0.5f }, 5, &walkUpLeft);
	}
	while ((App->player->position.y < position.y) && (App->player->position.x > position.x))
	{
		path.PushBack({ -0.5f,0.5f }, 5, &walkUpRight);
	}
	while ((App->player->position.y > position.y) && (App->player->position.x > position.x))
	{
		path.PushBack({ 0.5f,0.5f }, 5, &walkDownRight);
	}
	while ((App->player->position.y > position.y) && (App->player->position.x < position.x))
	{
		path.PushBack({ 0.5f,-0.5f }, 5, &walkDownLeft);
	}
	*/
	
	/*
	if(this->collider->Intersects()
	{
		if (currentAnim = &walkUp)
		{
			srand(1);
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
			srand(1);
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
			srand(1);
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
			srand(1);
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
			srand(1);
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
			srand(1);
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
			srand(1);
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
			srand(1);
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
	*/
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
