#include "Enemy.h"

#include "Application.h"
#include "ModuleCollisions.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "Enemy_Soldier.h"
#include "ModulePlayer.h"
#include "ModuleEnemies.h"



Enemy::Enemy(int x, int y) : position(x, y)
{
	
}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->pendingToDelete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Update()
{
	if (currentAnim != nullptr)
		currentAnim->Update();

	if (collider != nullptr)
		collider->SetPos(position.x + 5, position.y + 5);
	
	
	
}	

void Enemy::Draw()
{
	if (currentAnim != nullptr)
		App->render->Blit(texture, position.x, position.y, &(currentAnim->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* c2)
{
	if (c2->type == Collider::Type::PLAYER_SHOT)
	{
		
		if (App->player->collectedItemID==0)
		{
			EnemyHP = EnemyHP - 1;
			if (EnemyHP == 0)
			{
				App->particles->AddParticle(App->particles->explosion, position.x, position.y);
				App->audio->PlayFx(destroyedFx);
				App->player->score += 150;
				SetToDelete();
			}
			
		}
		if (App->player->collectedItemID == 1)
		{
			EnemyHP = EnemyHP - 2;
			if (EnemyHP == 0)
			{
				App->particles->AddParticle(App->particles->explosion, position.x, position.y);
				App->audio->PlayFx(destroyedFx);
				App->player->score += 150;
				SetToDelete();
			}
		}
		
	}

	if (c2->type == Collider::Type::WATER)
	{
		App->particles->AddParticle(App->particles->waterParticles, position.x, position.y + 30);

		EnemywaterSink = 20;
	}
	else
	{
		EnemywaterSink = 0;
	}

	if (c2->type == Collider::Type::WALL)
	{
		EnemySpeedX = 0;
		EnemySpeedY = 0;
		EnemywallCollision = true;
		
		if (App->player->EnemyLookingPosition==1)
		{
			position.y = position.y + 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 2)
		{
			position.y = position.y - 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 3)
		{
			position.x = position.x + 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 4)
		{
			position.x = position.x - 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 6)
		{
			position.x = position.x - 1;
			position.y = position.y + 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 5)
		{
			position.x = position.x + 1;
			position.y = position.y + 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 7)
		{
			position.x = position.x - 1;
			position.y = position.y - 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 8)
		{
			position.x = position.x + 1;
			position.y = position.y - 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
	}
	else if (c2->type != Collider::Type::WALL)
	{
		EnemySpeedX = 1;
		EnemySpeedY = 1;

		EnemywallCollision = false;
	}

	if (c2->type == Collider::Type::BREAKABLE_OBJECT)
	{
		EnemySpeedX = 0;
		EnemySpeedY = 0;
		EnemywallCollision = true;

		if (App->player->EnemyLookingPosition == 1)
		{
			position.y = position.y + 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 2)
		{
			position.y = position.y - 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 3)
		{
			position.x = position.x + 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 4)
		{
			position.x = position.x - 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 6)
		{
			position.x = position.x - 1;
			position.y = position.y + 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 5)
		{
			position.x = position.x + 1;
			position.y = position.y + 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 7)
		{
			position.x = position.x - 1;
			position.y = position.y - 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 8)
		{
			position.x = position.x + 1;
			position.y = position.y - 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
	}
	else if (c2->type != Collider::Type::BREAKABLE_OBJECT)
	{
		EnemySpeedX = 1;
		EnemySpeedY = 1;

		EnemywallCollision = false;
	}
	
	if (c2->type == Collider::Type::TRENCH_WALL)
	{
		EnemySpeedX = 0;
		EnemySpeedY = 0;
		EnemywallCollision = true;

		if (App->player->EnemyLookingPosition == 1)
		{
			position.y = position.y + 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 2)
		{
			position.y = position.y - 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 3)
		{
			position.x = position.x + 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 4)
		{
			position.x = position.x - 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 6)
		{
			position.x = position.x - 1;
			position.y = position.y + 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 5)
		{
			position.x = position.x + 1;
			position.y = position.y + 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 7)
		{
			position.x = position.x - 1;
			position.y = position.y - 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
		if (App->player->EnemyLookingPosition == 8)
		{
			position.x = position.x + 1;
			position.y = position.y - 1;
			EnemySpeedX = 1;
			EnemySpeedY = 1;
		}
	}
	else if (c2->type != Collider::Type::TRENCH_WALL)
	{
		EnemySpeedX = 1;
		EnemySpeedY = 1;

		EnemywallCollision = false;
	}
}
void Enemy::OnCollisionOther(Collider* c1, Collider* c2)
{
	if (c1->type == Collider::Type::BOSS) {
		if (c2->type == Collider::Type::PLAYER_SHOT)
		{

			if (App->player->collectedItemID == 0)
			{
				BossHP = BossHP - 1;
				if (BossHP == 0)
				{
					App->particles->AddParticle(App->particles->explosion, position.x, position.y);
					App->audio->PlayFx(destroyedFx);
					App->player->score += 150;
					SetToDelete();
				}

			}
			if (App->player->collectedItemID == 1)
			{
				BossHP = BossHP - 2;
				if (BossHP == 0)
				{
					App->particles->AddParticle(App->particles->explosion, position.x, position.y);
					App->audio->PlayFx(destroyedFx);
					App->player->score += 150;
					SetToDelete();
				}
			}
		}
	}
}

void Enemy::SetToDelete()
{
	pendingToDelete = true;
	if (collider != nullptr)
		collider->pendingToDelete = true;
}
