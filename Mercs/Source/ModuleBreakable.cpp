#include "ModuleBreakable.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"
#include "ModuleInput.h"
#include "SceneLevel1.h"
#include "SceneLevel1.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_timer.h"

ModuleBreakable::ModuleBreakable(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleBreakable::~ModuleBreakable()
{

}

bool ModuleBreakable::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Art/TileMaps/MovingAndChagingTiles.png"); // Should load a breakable object spritesheet

	palm.anim.PushBack({ 416, 292, 90, 163 });
	palm.speed.x = 0;
	palm.speed.y = 0;
	palm.lifetime = 0;
	palm.anim.loop = false;
	palm.anim.speed = 0.0f;

	house.anim.PushBack({ 260, 290, 130, 130 });
	house.speed.x = 0;
	house.speed.y = 0;
	house.lifetime = 0;
	house.anim.loop = false;
	house.anim.speed = 0.0f;

	fallingWall.anim.PushBack({ 283, 0, 130, 220 });
	fallingWall.speed.x = 0;
	fallingWall.speed.y = 0;
	fallingWall.lifetime = 0;
	fallingWall.anim.loop = false;
	fallingWall.anim.speed = 0.0f;

	fallingWallMoving.anim.PushBack({ 283, 0, 130, 220 });
	fallingWallMoving.speed.x = -1;
	fallingWallMoving.speed.y = 2;
	fallingWallMoving.lifetime = 75;
	fallingWallMoving.anim.loop = false;
	fallingWall.anim.speed = 0.0f;

	fallingWallEnd.anim.PushBack({ 100, 270, 130, 170 });
	fallingWallEnd.speed.x = 0;
	fallingWallEnd.speed.y = 0;
	fallingWallEnd.lifetime = 0;
	fallingWallEnd.anim.loop = false;
	fallingWallEnd.anim.speed = 0.0f;

	broken04 = App->audio->LoadFx("Assets/FX/04.wav");


	canBeDestoryed = true;

	return true;
}

Update_Status ModuleBreakable::PreUpdate()
{
	// Remove all particles scheduled for deletion
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (particles[i] != nullptr && particles[i]->pendingToDelete)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

bool ModuleBreakable::CleanUp()
{
	LOG("Unloading particles");

	// Delete all remaining active particles on application exit 
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if(particles[i] != nullptr)
		{
			delete particles[i];
			particles[i] = nullptr;
		}
	}

	return true;
}

void ModuleBreakable::OnCollision(Collider* c1, Collider* c2)
{
	// Always destroy particles that collide except with characters
	if ((c1->type != Collider::Type::PLAYER && c2->type != Collider::Type::BREAKABLE_OBJECT)
		|| (c1->type != Collider::Type::ENEMY && c2->type != Collider::Type::BREAKABLE_OBJECT)
		|| (c1->type != Collider::Type::ENEMY_BOMB && c2->type != Collider::Type::BREAKABLE_OBJECT)
		|| (c1->type != Collider::Type::ENEMY_SHOT && c2->type != Collider::Type::BREAKABLE_OBJECT)
		|| (c1->type != Collider::Type::BREAKABLE_OBJECT && c2->type != Collider::Type::PLAYER)
		|| (c1->type != Collider::Type::BREAKABLE_OBJECT && c2->type != Collider::Type::ENEMY)
		|| (c1->type != Collider::Type::BREAKABLE_OBJECT && c2->type != Collider::Type::ENEMY_BOMB)
		|| (c1->type != Collider::Type::BREAKABLE_OBJECT && c2->type != Collider::Type::ENEMY_SHOT)
		|| c1->type != Collider::Type::NONE || (c1->type == Collider::Type::WALL && App->sceneLevel_1->fallingWallEventDelays != 0))
	{
		canBeDestoryed = true;
		App->breakableParticles->fallingWall.SetToDelete();
	}

	if ((c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::BREAKABLE_OBJECT)
		|| (c1->type == Collider::Type::ENEMY && c2->type == Collider::Type::BREAKABLE_OBJECT)
		|| (c1->type == Collider::Type::ENEMY_BOMB && c2->type == Collider::Type::BREAKABLE_OBJECT)
		|| (c1->type == Collider::Type::ENEMY_SHOT && c2->type == Collider::Type::BREAKABLE_OBJECT)
		|| (c1->type == Collider::Type::BREAKABLE_OBJECT && c2->type == Collider::Type::PLAYER)
		|| (c1->type == Collider::Type::BREAKABLE_OBJECT && c2->type == Collider::Type::ENEMY)
		|| (c1->type == Collider::Type::BREAKABLE_OBJECT && c2->type == Collider::Type::ENEMY_BOMB)
		|| (c1->type == Collider::Type::BREAKABLE_OBJECT && c2->type == Collider::Type::ENEMY_SHOT)
		|| c1->type == Collider::Type::NONE || (c1->type == Collider::Type::WALL && App->sceneLevel_1->fallingWallEventDelays == 0))
	{
		canBeDestoryed = false;
	}

	if (canBeDestoryed == true)
	{
		for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		{
			if (particles[i] != nullptr && particles[i]->collider == c1)
			{
				App->input->ShakeController(0, 100, 0.15f);

				App->particles->AddParticle(App->particles->explosion, particles[i]->position.x + 20, particles[i]->position.y + 40, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->explosion, particles[i]->position.x + 40, particles[i]->position.y + 60, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->explosion, particles[i]->position.x + 30, particles[i]->position.y + 90, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->explosion, particles[i]->position.x + 80, particles[i]->position.y + 70, Collider::Type::NONE, 5);
				App->particles->AddParticle(App->particles->explosion, particles[i]->position.x + 10, particles[i]->position.y + 100, Collider::Type::NONE, 5);
				App->particles->AddParticle(App->particles->explosion, particles[i]->position.x + 100, particles[i]->position.y + 20, Collider::Type::NONE, 5);
				App->particles->AddParticle(App->particles->explosion, particles[i]->position.x + 60, particles[i]->position.y + 10, Collider::Type::NONE, 10);
				App->particles->AddParticle(App->particles->explosion, particles[i]->position.x + 50, particles[i]->position.y + 20, Collider::Type::NONE, 10);
				App->particles->AddParticle(App->particles->explosion, particles[i]->position.x + 70, particles[i]->position.y + 80, Collider::Type::NONE, 10);

				App->audio->PlayFx(broken04);

				particles[i]->pendingToDelete = true;
				particles[i]->collider->pendingToDelete = true;
				break;
			}
		}
	}
	
}

Update_Status ModuleBreakable::Update()
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if(particle == nullptr)	continue;

		// Call particle Update. If it has reached its lifetime, destroy it
		if(particle->Update() == false)
		{
			particles[i]->SetToDelete();
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleBreakable::PostUpdate()
{
	//Iterating all particle array and drawing any active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* particle = particles[i];

		if (particle != nullptr && particle->isAlive)
		{
			App->render->Blit(texture, particle->position.x, particle->position.y, &(particle->anim.GetCurrentFrame()));
		}
	}

	return Update_Status::UPDATE_CONTINUE;
}

Particle* ModuleBreakable::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
{
	Particle* newParticle = nullptr;

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		//Finding an empty slot for a new particle
		if (particles[i] == nullptr)
		{
			newParticle = new Particle(particle);
			newParticle->frameCount = -(int)delay;			// We start the frameCount as the negative delay
			newParticle->position.x = x;						// so when frameCount reaches 0 the particle will be activated
			newParticle->position.y = y;

			//Adding the particle's collider
			if (colliderType != Collider::Type::NONE)
				newParticle->collider = App->collisions->AddCollider(newParticle->anim.GetCurrentFrame(), colliderType, this);

			particles[i] = newParticle;
			break;
		}
	}

	return newParticle;
}