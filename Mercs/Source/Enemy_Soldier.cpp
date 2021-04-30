#include "Enemy_Soldier.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

Enemy_Soldier::Enemy_Soldier(int x, int y) : Enemy(x, y)
{	
	walkUp.speed = 0.2f;
	walkDown.speed = 0.2f;
	walkRight.speed = 0.2f;
	walkUpLeft.speed = 0.2f;
	walkUpRight.speed = 0.2f;
	walkDownLeft.speed = 0.2f;
	walkDownRight.speed = 0.2f;

	
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
	
	path.PushBack({ 0.0f,0.5f }, 50,&walkDown);
	path.PushBack({ 0.0f,-0.5f }, 50, &walkUp);

	collider = App->collisions->AddCollider({position.x, position.y, 30, 43}, Collider::Type::ENEMY, (Module*)App->enemies);
	
	
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
			path.Update();
		}
		if ((position.x == App->player->position.x) && (position.y > App->player->position.y))
		{
			
			App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotUp, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
			path.Update();
		}
		if ((position.x < App->player->position.x) && (position.y == App->player->position.y))
		{
			
			App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotRight, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
			path.Update();
		}
		if ((position.x > App->player->position.x) && (position.y == App->player->position.y))
		{
			
			App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotLeft, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
			path.Update();
		}
		/**
		if ((position.x < App->player->position.x) && (position.y < App->player->position.y))
		{
			currentAnim == &shootDownRight;
			App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotDownRight, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
			path.Update();
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
