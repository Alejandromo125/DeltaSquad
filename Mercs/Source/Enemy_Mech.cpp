#include "Enemy_Mech.h"

#include "Application.h"
#include "ModuleCollisions.h"

Enemy_Mech::Enemy_Mech(int x, int y) : Enemy(x, y)
{
	walkLeft.speed = 0.1f;
	walkRight.speed = 0.1f;

	walkLeft.loop = true;
	walkRight.loop = true;

	walkLeft.PushBack({ 35,104,32,32 });
	walkLeft.PushBack({ 6,104,32,32 });

	walkRight.PushBack({ 172,104,32,32 });
	walkRight.PushBack({ 139,104,32,32 });


	currentAnim = &walkLeft;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	path.PushBack({ -1.0, 0 }, 100, &walkLeft);
	path.PushBack({ 1.5, 0 }, 100, &walkRight);



	collider = App->collisions->AddCollider({ 0, 0, 24, 24 }, Collider::Type::ENEMY, (Module*)App->enemies);
}

void Enemy_Mech::Update()
{
	path.Update();
	position = spawnPos + path.GetRelativePosition();
	currentAnim = path.GetCurrentAnimation();


	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}
