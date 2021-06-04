#include "Boss.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "p2Point.h"
#include "ModuleFadeToBlack.h"
#include "ModuleRender.h"


Boss::Boss(int x, int y) : Enemy(x, y)
{
	Enemy::EnemyHP = 20;
	Idle.PushBack({ 0,0,128,102 });
	Idle.loop = true;

	// TODO 3: Have the Brown Cookies describe a path in the screen
	

	//SHOOTING ANIMATIONS
	Shot.PushBack({ 0,0,128,102 });
	Shot.PushBack({ 140,0,128,102 });
	Shot.PushBack({ 280,0,128,102 });
	Shot.PushBack({ 0,0,128,102 });
	Shot.PushBack({ 140,0,128,102 });
	Shot.PushBack({ 280,0,128,102 });
	Shot.loop = true;

	
	

	collider = App->collisions->AddCollider({ position.x, position.y, 128, 102 }, Collider::Type::BOSS, (Module*)App->enemies);
	App->enemies->AlreadySpawned = true;
}

void Boss::Update()
{
	currentAnim = &Shot;
	counter++;
	BossMovementCounter++;
	int half = position.x + 54;

	
	
	if (counter % 2 == 0)
	{
		if (position.DistanceTo(App->player->position) < 1000)
		{
			if (BossMovementCounter<180)
			{
				currentAnim = &Shot;
				position.x--;
				position.x--;
				
				

			}
			if ((BossMovementCounter>180)&&(BossMovementCounter<360))
			{
				currentAnim = &Shot;
				position.x++;
				position.x++;
				
				
			}
			if (BossMovementCounter == 360) BossMovementCounter = 0;
			
			
		}
		
	}
	
	
	

	if (counter % 40 == 0)
	{
		if (position.DistanceTo(App->player->position) < 250)
		{
				currentAnim = &Shot;
				App->particles->AddParticle(App->particles->shotEffect, half-40, position.y +50, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->BossShot, half-40, position.y + 50, Collider::Type::BOSS_ATTACK);
				currentAnim = &Shot;
				App->particles->AddParticle(App->particles->shotEffect, half+50, position.y + 50, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->BossShot,half+50, position.y + 50, Collider::Type::BOSS_ATTACK);
		}
		

	}
	if (EnemyHP == 0) App->player->activateWinCondition = true;
	

	
	

	// Call to the base class. It must be called at the end
	// It will update the collider depending on the position
	Enemy::Update();
}