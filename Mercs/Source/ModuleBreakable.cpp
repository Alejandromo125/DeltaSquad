#include "ModuleBreakable.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

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

	// Example
	palm.anim.PushBack({ 416, 292, 90, 163 });
	palm.speed.x = 0;
	palm.speed.y = 0;
	palm.lifetime = 0;
	palm.anim.loop = false;
	palm.anim.speed = 0.0f;

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
		|| (c1->type != Collider::Type::BREAKABLE_OBJECT && c2->type != Collider::Type::ENEMY_SHOT))
	{
		canBeDestoryed = true;
	}

	if ((c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::BREAKABLE_OBJECT)
		|| (c1->type == Collider::Type::ENEMY && c2->type == Collider::Type::BREAKABLE_OBJECT)
		|| (c1->type == Collider::Type::ENEMY_BOMB && c2->type == Collider::Type::BREAKABLE_OBJECT)
		|| (c1->type == Collider::Type::ENEMY_SHOT && c2->type == Collider::Type::BREAKABLE_OBJECT)
		|| (c1->type == Collider::Type::BREAKABLE_OBJECT && c2->type == Collider::Type::PLAYER)
		|| (c1->type == Collider::Type::BREAKABLE_OBJECT && c2->type == Collider::Type::ENEMY)
		|| (c1->type == Collider::Type::BREAKABLE_OBJECT && c2->type == Collider::Type::ENEMY_BOMB)
		|| (c1->type == Collider::Type::BREAKABLE_OBJECT && c2->type == Collider::Type::ENEMY_SHOT))
	{
		canBeDestoryed = false;
	}

	if (canBeDestoryed == true)
	{
		for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		{
			if (particles[i] != nullptr && particles[i]->collider == c1)
			{
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