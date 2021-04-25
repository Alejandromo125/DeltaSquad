#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"

#include "SDL/include/SDL_scancode.h"


ModulePlayer::ModulePlayer()
{
	// Idle Animations
	// Up
	idleUpAnim.PushBack({ 140, 0, 30, 43 - waterSink });
	idleUpAnim.loop = false;
	// Down
	idledownAnim.PushBack({ 140, 196, 30, 43 - waterSink });
	idledownAnim.loop = false;
	// Right
	idleRightAnim.PushBack({ 140, 285, 30, 43 - waterSink });
	idleRightAnim.loop = false;
	// Left
	idleLeftAnim.PushBack({ 140, 100, 30, 43 - waterSink });
	idleLeftAnim.loop = false;
	// Up Left
	//Insert pushBack
	idleUpLeftAnim.loop = false;
	// Up Right
	//Insert pushBack
	idleUpRightAnim.loop = false;
	// Down Left
	//Insert pushBack
	idleDownLeftAnim.loop = false;
	// Down Right
	//Insert pushBack
	idleDownRightAnim.loop = false;

	// Move Upwards
	upAnim.PushBack({ 5, 7, 30, 43 - waterSink });
	upAnim.PushBack({ 36, 7, 30, 43 - waterSink });
	upAnim.PushBack({ 68, 7, 30, 43 - waterSink });
	upAnim.PushBack({ 100, 7, 30, 43 - waterSink });
	upAnim.loop = true;
	upAnim.speed = 0.1f;

	// Move down
	downAnim.PushBack({ 10, 192, 30, 43 - waterSink });
	downAnim.PushBack({ 43, 192, 30, 43 - waterSink });
	downAnim.PushBack({ 75, 192, 30, 43 - waterSink });
	downAnim.PushBack({ 107, 192, 30, 43 - waterSink });
	downAnim.loop = true;
	downAnim.speed = 0.1f;

	// Move Left
	leftAnim.PushBack({ 7, 102, 30, 43 - waterSink });
	leftAnim.PushBack({ 38, 102, 30, 43 - waterSink });
	leftAnim.PushBack({ 72, 102, 30, 43 - waterSink });
	leftAnim.PushBack({ 102, 102, 30, 43 - waterSink });
	leftAnim.loop = true;
	leftAnim.speed = 0.1f;

	// Move Right
	rightAnim.PushBack({ 8, 284, 30, 43 - waterSink });
	rightAnim.PushBack({ 41, 284, 30, 43 - waterSink });
	rightAnim.PushBack({ 71, 284, 30, 43 - waterSink });
	rightAnim.PushBack({ 107, 284, 30, 43 - waterSink });
	rightAnim.loop = true;
	rightAnim.speed = 0.1f;

	// Move Up Left
	upLeftAnim.PushBack({ 5, 53, 30, 43 - waterSink });
	upLeftAnim.PushBack({ 35, 53, 30, 43 - waterSink });
	upLeftAnim.PushBack({ 70, 53, 30, 43 - waterSink });
	upLeftAnim.PushBack({ 100, 53, 30, 43 - waterSink });
	upLeftAnim.loop = true;
	upLeftAnim.speed = 0.14f;

	// Move Down Left
	downLeftAnim.PushBack({ 8, 147, 30, 43 - waterSink });
	downLeftAnim.PushBack({ 40, 147, 30, 43 - waterSink });
	downLeftAnim.PushBack({ 75, 147, 30, 43 - waterSink });
	downLeftAnim.PushBack({ 105, 147, 30, 43 - waterSink });
	downLeftAnim.loop = true;
	downLeftAnim.speed = 0.14f;

	// Move Up Right
	upRightAnim.PushBack({ 3, 332, 30, 43 - waterSink });
	upRightAnim.PushBack({ 35, 332, 30, 43 - waterSink });
	upRightAnim.PushBack({ 65, 332, 30, 43 - waterSink });
	upRightAnim.PushBack({ 98, 332, 30, 43 - waterSink });
	upRightAnim.loop = true;
	upRightAnim.speed = 0.14f;

	// Move Down Right
	downRightAnim.PushBack({ 8, 238, 30, 43 - waterSink });
	downRightAnim.PushBack({ 40, 238, 30, 43 - waterSink });
	downRightAnim.PushBack({ 70, 238, 30, 43 - waterSink });
	downRightAnim.PushBack({ 104, 238, 30, 43 - waterSink });
	downRightAnim.loop = true;
	downRightAnim.speed = 0.14f;

	// Die Up
	//Insert pushBack
	deadFrontAnim.loop = false;
	deadFrontAnim.speed = 0.1f;

	// Die Down
	//Insert pushBack
	deadBackAnim.loop = false;
	deadBackAnim.speed = 0.1f;
}

ModulePlayer::~ModulePlayer()
{

}

bool ModulePlayer::Start()
{
	LOG("Loading player textures");

	bool ret = true;

	texture = App->textures->Load("Assets/Art/Sprites/player1.png");
	currentAnimation = &idledownAnim;

	shot06 = App->audio->LoadFx("Assets/FX/06.wav");
	dead26 = App->audio->LoadFx("Assets/FX/26.wav");

	position.x = 200;
	position.y = 100;

	collider = App->collisions->AddCollider({ position.x + 6, position.y + 5, 15, 30 }, Collider::Type::PLAYER, this);

	return ret;
}

update_status ModulePlayer::Update()
{

	// Camera speed and player speed value conditions

	if (cameraSpeedX == 0)
	{
		speedX = 2;
	}
	else
	{
		speedX = 1;
	}

	if (cameraSpeedY == 0)
	{
		speedY = 2;
	}
	else
	{
		speedY = 1;
	}
	// Moving the player with the camera scroll
	//App->player->position.x = App->render->camera.x;
	//App->player->position.y = App->render->camera.y;
	//App->player->position.x = (SCREEN_WIDTH / 2) * SCREEN_SIZE;
	//App->player->position.y = (SCREEN_HEIGHT / 2) * SCREEN_SIZE;

	if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{
		App->player->position.x -= speedX;
		App->render->camera.x -= cameraSpeedX;
		if (currentAnimation != &leftAnim)
		{
			//leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
	{
		App->player->position.x += speedX;
		App->render->camera.x += cameraSpeedX;
		if (currentAnimation != &rightAnim)
		{
			//rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{
		App->player->position.y += speedY;
		App->render->camera.y += cameraSpeedY;
		if (currentAnimation != &downAnim)
		{
			//downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{
		if (currentAnimation != &downLeftAnim)
		{
			//downLeftAnim.Reset();
			currentAnimation = &downLeftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{
		if (currentAnimation != &downRightAnim)
		{
			//downRightAnim.Reset();
			currentAnimation = &downRightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{
		App->player->position.y -= speedY;
		App->render->camera.y -= cameraSpeedY;
		if (currentAnimation != &upAnim)
		{
			//upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{
		if (currentAnimation != &upLeftAnim)
		{
			//upLeftAnim.Reset();
			currentAnimation = &upLeftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT && App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{
		if (currentAnimation != &upRightAnim)
		{
			//upRightAnim.Reset();
			currentAnimation = &upRightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->audio->PlayFx(shot06);

		if (currentAnimation == &idleUpAnim || currentAnimation == &upAnim)
		{
			App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotUp, position.x + 10, position.y, Collider::Type::PLAYER_SHOT);
		}

		if (currentAnimation == &idledownAnim || currentAnimation == &downAnim)
		{
			App->particles->AddParticle(App->particles->shotEffect, position.x + 5, position.y + 25, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotDown, position.x + 5, position.y + 15, Collider::Type::PLAYER_SHOT);
		}

		if (currentAnimation == &idleLeftAnim || currentAnimation == &leftAnim)
		{
			App->particles->AddParticle(App->particles->shotEffect, position.x - 8, position.y + 8, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotLeft, position.x - 3, position.y + 8, Collider::Type::PLAYER_SHOT);
		}

		if (currentAnimation == &idleRightAnim || currentAnimation == &rightAnim)
		{
			App->particles->AddParticle(App->particles->shotEffect, position.x + 25, position.y + 8, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotRight, position.x + 18, position.y + 8, Collider::Type::PLAYER_SHOT);
		}

		if (currentAnimation == &idleUpLeftAnim || currentAnimation == &upLeftAnim)
		{
			App->particles->AddParticle(App->particles->shotEffect, position.x - 5, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotUpLeft, position.x, position.y, Collider::Type::PLAYER_SHOT);
		}
		
		if (currentAnimation == &idleDownLeftAnim || currentAnimation == &downLeftAnim)
		{
			App->particles->AddParticle(App->particles->shotEffect, position.x - 5, position.y + 20, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotDownLeft, position.x, position.y + 15, Collider::Type::PLAYER_SHOT);
		}

		if (currentAnimation == &idleUpRightAnim || currentAnimation == &upRightAnim)
		{
			App->particles->AddParticle(App->particles->shotEffect, position.x + 25, position.y - 5, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotUpRight, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
		}

		if (currentAnimation == &idleDownRightAnim || currentAnimation == &downRightAnim)
		{
			App->particles->AddParticle(App->particles->shotEffect, position.x + 25, position.y + 20, Collider::Type::NONE);
			App->particles->AddParticle(App->particles->shotDownRight, position.x + 15, position.y + 10, Collider::Type::PLAYER_SHOT);
		}
	}

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE)
		currentAnimation = &idledownAnim;

	collider->SetPos(position.x + 6, position.y + 5);

	currentAnimation->Update();

	if (destroyed)
	{
		destroyedCountdown--;
		if (destroyedCountdown <= 0)
			return update_status::UPDATE_STOP;
	}

	return update_status::UPDATE_CONTINUE;
}

update_status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect);
	}

	// Add player shadow
	//App->particles->AddParticle(App->particles->shadow, position.x + 5, position.y + 30, Collider::Type::NONE); // <-- Does not work well (Z-layer problem)
	
	return update_status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (c1 == collider && destroyed == false)
	{
		App->audio->PlayFx(dead26);

		if(currentAnimation == &idleUpAnim || currentAnimation == &idleUpLeftAnim || currentAnimation == &idleLeftAnim || currentAnimation == &idleUpRightAnim ||
			currentAnimation == &upAnim || currentAnimation == &upLeftAnim || currentAnimation == &upRightAnim || currentAnimation == &leftAnim)
			currentAnimation = &deadBackAnim;

		if (currentAnimation == &idledownAnim || currentAnimation == &idleDownLeftAnim || currentAnimation == &idleRightAnim || currentAnimation == &idleDownRightAnim ||
			currentAnimation == &downAnim || currentAnimation == &downLeftAnim || currentAnimation == &downRightAnim || currentAnimation == &rightAnim)
			currentAnimation = &deadFrontAnim;

		destroyed = true;
	}
}