#include "Enemy_BrownShip.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_BrownShip::Enemy_BrownShip(int x, int y) : Enemy(x, y)
{
	flyUp.speed = 0.2f;
	flyMiddle.speed = 0.2f;
	flyDown.speed = 0.2f;

	flyUp.loop = false;
	flyMiddle.loop = false;
	flyDown.loop = false;
	
	flyUp.PushBack({ 37,72,21,22 });
	flyUp.PushBack({ 69,72,21,22 });

	flyMiddle.PushBack({ 5,72,21,22 });

	flyDown.PushBack({ 235,39,21,22 });
	flyDown.PushBack({ 201,39,21,22 });
	
	
	currentAnim = &flyMiddle;
	
	// TODO 3: Have the Brown Cookies describe a path in the screen
	path.PushBack({ -1.0, -0.5 }, 100, &flyUp);
	path.PushBack({ -1.0, 0 }, 15, &flyMiddle);
	path.PushBack({ -1.0, 0.5 }, 100, &flyDown);

	
	
	collider = App->collisions->AddCollider({0, 0, 24, 24}, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_BrownShip::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();

	
	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
