#include "Tower_Enemy_Level2.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"
#include "ModuleInput.h"
#include "ModuleBreakable.h"
#include "ModuleParticles.h"
#include "Particle.h"
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

	explosionDelay = 120;

}

void TowerEnemy::Update()
{


	explosionDelay++;
	counter++;

	if (App->player->position.y > position.y)
	{

		currentAnim = &ShootDown;
		App->particles->enemyBomb.speed.y = (App->player->position.y - (position.y + 20)) / 120;
	}

	if (App->player->position.x < position.x)
	{
		currentAnim = &ShootLeft;
		App->particles->enemyBomb.speed.x = -(App->player->position.x - (position.x + 10)) / 120;

	}
	if (App->player->position.x > position.x)
	{
		currentAnim = &ShootRight;
		App->particles->enemyBomb.speed.x = (App->player->position.x - (position.x + 10)) / 120;
	}

	if ((App->player->position.y > position.y) && (App->player->position.x > position.x))
	{
		currentAnim = &ShootDownRight;
		App->particles->enemyBomb.speed.x = (App->player->position.x - (position.x + 10)) / 120;
		App->particles->enemyBomb.speed.y = (App->player->position.y - (position.y + 20)) / 120;
	}

	if ((App->player->position.x < position.x) && (App->player->position.y > position.y))
	{
		currentAnim = &ShootDownLeft;
		App->particles->enemyBomb.speed.x = -(App->player->position.x - (position.x + 10)) / 120;
		App->particles->enemyBomb.speed.y = (App->player->position.y - (position.y + 20)) / 120;
	}

	if (counter % 120 == 0)
	{
		if (position.DistanceTo(App->player->position) < 350)
		{
			explosionDelay = 0;

			App->particles->AddParticle(App->particles->enemyBomb, position.x + 5, position.y + 15, Collider::Type::ENEMY_BOMB);
			App->particles->AddParticle(App->particles->bombExplosion, position.x + 5, position.y + 15, Collider::Type::NONE);
			if (explosionDelay == 118)
			{
				App->particles->bombExplosion.speed.x = 0;
				App->particles->bombExplosion.speed.y = 0;
			}
		}
	}

	if (counter % 120 == 0)
	{
		//DIAGONAL SHOT IMPLEMENTATION

		if (position.DistanceTo(App->player->position) < 350)
		{
			explosionDelay = 0;

			App->particles->AddParticle(App->particles->enemyBomb, position.x + 5, position.y + 15, Collider::Type::ENEMY_BOMB);
			App->particles->AddParticle(App->particles->bombExplosion, position.x + 5, position.y + 15, Collider::Type::NONE);
			if (explosionDelay == 118)
			{
				App->particles->bombExplosion.speed.x = 0;
				App->particles->bombExplosion.speed.y = 0;
			}
			
		}

	}

	if (explosionDelay == 118)
	{
		App->input->ShakeController(0, 120, 0.15f);
		App->particles->AddParticle(App->particles->bombExplosion, App->particles->bombExplosion.position.x + 5, App->particles->bombExplosion.position.y + 15, Collider::Type::NONE); // Does not work
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