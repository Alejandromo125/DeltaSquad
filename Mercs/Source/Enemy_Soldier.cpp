#include "Enemy_Soldier.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"


Enemy_Soldier::Enemy_Soldier(int x, int y) : Enemy(x, y)
{	
	walkUp.speed = 0.2f;
	walkDown.speed = 0.2f;
	walkRight.speed = 0.2f;
	walkUpLeft.speed = 0.2f;
	walkUpRight.speed = 0.2f;
	walkDownLeft.speed = 0.2f;
	walkDownRight.speed = 0.2f;

	
	
	walkUp.PushBack({ 37,72,21,22 });
	walkUp.PushBack({ 69,72,21,22 });
	walkUp.PushBack({ 69,72,21,22 });

	walkDown.PushBack({ 5,72,21,22 });
	walkDown.PushBack({ 5,72,21,22 });
	walkDown.PushBack({ 5,72,21,22 });

	walkRight.PushBack({ 235,39,21,22 });
	walkRight.PushBack({ 201,39,21,22 });

	walkLeft.PushBack({ 235,39,21,22 });
	walkLeft.PushBack({ 201,39,21,22 });

	walkUpRight.PushBack({ 5,72,21,22 });
	walkUpRight.PushBack({ 5,72,21,22 });
	walkUpRight.PushBack({ 5,72,21,22 });

	walkUpLeft.PushBack({ 5,72,21,22 });
	walkUpLeft.PushBack({ 5,72,21,22 });
	walkUpLeft.PushBack({ 5,72,21,22 });

	walkDownRight.PushBack({ 5,72,21,22 });
	walkDownRight.PushBack({ 5,72,21,22 });
	walkDownRight.PushBack({ 5,72,21,22 });

	walkDownLeft.PushBack({ 5,72,21,22 });
	walkDownLeft.PushBack({ 5,72,21,22 });
	walkDownLeft.PushBack({ 5,72,21,22 });

	
	
	
	// TODO 3: Have the Soldiers describe a path in the screen taking into account the collisions
	
	path.PushBack({ -1.0, -0.5 }, 100, &walkUp);
	path.PushBack({ -1.0, 0 }, 15, &walkLeft);
	path.PushBack({ -1.0, 0.5 }, 100, &walkDown);

	
	
	
	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
	
}

void Enemy_Soldier::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();
	/*
	if(position.DistanceTo(ModulePlayer::position)<
	*/
	
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
