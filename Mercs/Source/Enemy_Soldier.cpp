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
	walkUp.PushBack({ 277,606,101,118 });
	walkUp.PushBack({ 174,606,101,118 });
	walkUp.PushBack({ 77,606,101,118 });

	walkDown.PushBack({ 274,122,101,118 });
	walkDown.PushBack({ 184,122,101,118 });
	walkDown.PushBack({ 91,122,101,118 });

	walkRight.PushBack({ 276,356,101,118 });
	walkRight.PushBack({ 170,356,101,118 });

	walkLeft.PushBack({ 280,471,101,118 });
	walkLeft.PushBack({ 174,471,101,118 });

	walkUpRight.PushBack({ 264,733,101,118 });
	walkUpRight.PushBack({ 174,733,101,118 });
	walkUpRight.PushBack({ 76,733,101,118 });

	walkUpLeft.PushBack({ 270,861,101,118 });
	walkUpLeft.PushBack({ 173,861,101,118 });
	walkUpLeft.PushBack({ 75,861,101,118 });

	walkDownRight.PushBack({ 179,241,101,118 });
	walkDownRight.PushBack({ 90,241,101,118 });
	walkDownRight.PushBack({ 0,241,101,118 });

	walkDownLeft.PushBack({ 0,0,101,118 });
	walkDownLeft.PushBack({ 83,0,101,118 });
	walkDownLeft.PushBack({ 180,0,101,118 });

	//SHOOTING ANIMATIONS
	shootDown.PushBack({});
	shootUp.PushBack({});
	shootRight.PushBack({});
	shootLeft.PushBack({});
	shootUpRight.PushBack({});
	shootUpLeft.PushBack({});
	shootDownRight.PushBack({});
	shootDownLeft.PushBack({});
	
	//Have the Soldiers describe a path in the screen taking into account the collisions
	
	path.PushBack({ -1.0, -0.5 }, 10, &walkUp);
	path.PushBack({ -1.0, 0 }, 15, &walkLeft);
	path.PushBack({ -1.0, 0.5 }, 10, &walkDown);
	

	collider = App->collisions->AddCollider({0, 0, 101, 118}, Collider::Type::ENEMY, (Module*)App->enemies);
	
	
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
			currentAnim == &shootDown;
			App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotDown, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
		}
		if ((position.x == App->player->position.x) && (position.y > App->player->position.y))
		{
			currentAnim == &shootUp;
			App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotUp, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
		}
		if ((position.x < App->player->position.x) && (position.y == App->player->position.y))
		{
			currentAnim == &shootRight;
			App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotRight, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
		}
		if ((position.x > App->player->position.x) && (position.y == App->player->position.y))
		{
			currentAnim == &shootLeft;
			App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotLeft, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
		}
		if ((position.x < App->player->position.x) && (position.y < App->player->position.y))
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
		}
		if ((position.x < App->player->position.x) && (position.y > App->player->position.y))
		{
			currentAnim == &shootUpRight;
			App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotUpRight, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
		}
		if ((position.x > App->player->position.x) && (position.y > App->player->position.y))
		{
			currentAnim == &shootUpLeft;
			App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotUpLeft, position.x + 10, position.y, Collider::Type::ENEMY_SHOT);
		}
	}
	
	
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
