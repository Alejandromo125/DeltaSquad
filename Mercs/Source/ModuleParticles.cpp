#include "ModuleParticles.h"

#include "Application.h"

#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		particles[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{

}

bool ModuleParticles::Start()
{
	LOG("Loading particles");
	texture = App->textures->Load("Assets/Art/Sprites/items.png");

	// Water Particles
	waterParticles.anim.PushBack({ 370, 32, 30, 35 });
	//waterParticles.anim.PushBack({ 370, 35, 23, 13 });
	//waterParticles.anim.PushBack({ 296, 35, 23, 13 });
	waterParticles.speed.x = 0;
	waterParticles.lifetime = 3;
	waterParticles.speed.y = 0;
	waterParticles.anim.loop = false;
	waterParticles.anim.speed = 0.2f;

	// Shadow particle
	shadow.anim.PushBack({ 3, 290, 20, 10 });
	shadow.speed.x = 0;
	shadow.speed.y = 0;
	shadow.anim.loop = false;
	shadow.anim.speed = 0.25f;

	// Explosion particle
	explosion.anim.PushBack({ 201, 152, 32, 30 });
	explosion.anim.PushBack({ 251, 296, 32, 30 });
	explosion.anim.PushBack({ 306, 296, 32, 30 });
	explosion.anim.PushBack({ 360, 296, 32, 30 });
	explosion.speed.x = 0;
	explosion.speed.y = 0;
	explosion.anim.loop = false;
	explosion.anim.speed = 0.25f;

	// Shots particles

	shotEffect.anim.PushBack({ 5, 272, 10, 10 });
	shotEffect.speed.x = 0;
	shotEffect.speed.y = 0;
	shotEffect.lifetime = 5;
	shotEffect.anim.loop = false;
	shotEffect.anim.speed = 0.2f;

	shotRight.anim.PushBack({ 30, 153, 10, 10 });
	shotRight.speed.x = 6;
	shotRight.speed.y = 0;
	shotRight.lifetime = 180;
	shotRight.anim.loop = false;
	shotRight.anim.speed = 0.2f;

	shotLeft.anim.PushBack({ 6, 180, 10, 10 });
	shotLeft.speed.x = -6;
	shotLeft.speed.y = 0;
	shotLeft.lifetime = 180;
	shotLeft.anim.loop = false;
	shotLeft.anim.speed = 0.2f;

	shotUp.anim.PushBack({ 6, 151, 10, 10 });
	shotUp.speed.x = 0;
	shotUp.speed.y = -6;
	shotUp.lifetime = 180;
	shotUp.anim.loop = false;
	shotUp.anim.speed = 0.2f;

	shotDown.anim.PushBack({ 28, 218, 10, 10 });
	shotDown.speed.x = 0;
	shotDown.speed.y = 6;
	shotDown.lifetime = 180;
	shotDown.anim.loop = false;
	shotDown.anim.speed = 0.2f;

	shotUpLeft.anim.PushBack({ 18, 178, 10, 10 });
	shotUpLeft.speed.x = -5;
	shotUpLeft.speed.y = -5;
	shotUpLeft.lifetime = 180;
	shotUpLeft.anim.loop = false;
	shotUpLeft.anim.speed = 0.2f;

	shotDownRight.anim.PushBack({ 16, 244, 10, 10 });
	shotDownRight.speed.x = 5;
	shotDownRight.speed.y = 5;
	shotDownRight.lifetime = 180;
	shotDownRight.anim.loop = false;
	shotDownRight.anim.speed = 0.2f;

	shotDownLeft.anim.PushBack({ 18, 217, 10, 10 });
	shotDownLeft.speed.x = -5;
	shotDownLeft.speed.y = 5;
	shotDownLeft.lifetime = 180;
	shotDownLeft.anim.loop = false;
	shotDownLeft.anim.speed = 0.2f;

	shotUpRight.anim.PushBack({ 17, 152, 10, 10 });
	shotUpRight.speed.x = 5;
	shotUpRight.speed.y = -5;
	shotUpRight.lifetime = 180;
	shotUpRight.anim.loop = false;
	shotUpRight.anim.speed = 0.2f;

	return true;
}

Update_Status ModuleParticles::PreUpdate()
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

bool ModuleParticles::CleanUp()
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

void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (particles[i] != nullptr && particles[i]->collider == c1)
		{
			particles[i]->pendingToDelete = true;
			particles[i]->collider->pendingToDelete = true;
			break;
		}
	}
}

Update_Status ModuleParticles::Update()
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

Update_Status ModuleParticles::PostUpdate()
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

Particle* ModuleParticles::AddParticle(const Particle& particle, int x, int y, Collider::Type colliderType, uint delay)
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