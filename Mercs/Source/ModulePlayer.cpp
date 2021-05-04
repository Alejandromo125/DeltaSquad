#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"

#include <stdio.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{

	// Idle Animations
	// Up
	idleUpAnim.PushBack({ 140, 0, 30, 43 - waterSink }); //Water sink effect does not work
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
	upLeftAnim.speed = 0.1f;

	// Move Down Left
	downLeftAnim.PushBack({ 8, 147, 30, 43 - waterSink });
	downLeftAnim.PushBack({ 40, 147, 30, 43 - waterSink });
	downLeftAnim.PushBack({ 75, 147, 30, 43 - waterSink });
	downLeftAnim.PushBack({ 105, 147, 30, 43 - waterSink });
	downLeftAnim.loop = true;
	downLeftAnim.speed = 0.1f;

	// Move Up Right
	upRightAnim.PushBack({ 3, 332, 30, 43 - waterSink });
	upRightAnim.PushBack({ 35, 332, 30, 43 - waterSink });
	upRightAnim.PushBack({ 65, 332, 30, 43 - waterSink });
	upRightAnim.PushBack({ 98, 332, 30, 43 - waterSink });
	upRightAnim.loop = true;
	upRightAnim.speed = 0.1f;

	// Move Down Right
	downRightAnim.PushBack({ 8, 238, 30, 43 - waterSink });
	downRightAnim.PushBack({ 40, 238, 30, 43 - waterSink });
	downRightAnim.PushBack({ 70, 238, 30, 43 - waterSink });
	downRightAnim.PushBack({ 104, 238, 30, 43 - waterSink });
	downRightAnim.loop = true;
	downRightAnim.speed = 0.1f;

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
	merc = App->textures->Load("Assets/Art/UI/merc1.1_ss.png");
	insertcoin = App->textures->Load("Assets/Art/UI/insertcoin_ss.png");
	mercLife = App->textures->Load("Assets/Art/UI/mercLife.png");

	currentAnimation = &idledownAnim;

	shot06 = App->audio->LoadFx("Assets/FX/06.wav");
	dead26 = App->audio->LoadFx("Assets/FX/26.wav");

	position.x = 150;
	position.y = 100;

	speedX = 1;
	speedY = 1;

	destroyed = false;

	//playerLife = 100;   <-- Not used for now

	collectedItemID = 0; // ID 0 is single shot weapon, ID 1 is dual shot weapon, ID 2 is triple shot weapon (only ID 0 and 1 are used in level 1)
	//collectedMegaBombsNumber = 1; // Player starts with 1 MegaBomb available -=(MegaBomb mechanic is not implemented yet so it wont have any effect for now)=-

	collider = App->collisions->AddCollider({ position.x + 5, position.y + 3, 16, 32 }, Collider::Type::PLAYER, this);

	App->particles->AddParticle(App->particles->doubleShotWeapon, 570 - 120, 970 - 1100, Collider::Type::DOUBLE_SHOT_WEAPON_ID01);

	//App->render->camera.x = (SCREEN_WIDTH / 2) * SCREEN_SIZE;
	//App->render->camera.y = (SCREEN_HEIGHT / 2) * SCREEN_SIZE;

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "0123456789" };
	scoreFont = App->fonts->Load("Assets/Art/UI/numbers_s.png", lookupTable, 1);
	
	return ret;
}

Update_Status ModulePlayer::Update()
{
	// Moving the player with the camera scroll
	//App->player->position.x = App->render->camera.x;
	//App->player->position.y = App->render->camera.y;

	//App->render->camera.x = App->player->position.x - (SCREEN_WIDTH / 2);
	//App->render->camera.y = App->player->position.y - (SCREEN_HEIGHT / 2);
	//App->player->position.x = App->player->position.x - (App->render->camera.x / 20);
	//App->player->position.y = App->player->position.y - (App->render->camera.y / 20);

	//App->player->position.x = (SCREEN_WIDTH / 2) * SCREEN_SIZE;
	//App->player->position.y = (SCREEN_HEIGHT / 2) * SCREEN_SIZE;

	if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT)
	{
		App->player->position.x = App->player->position.x - speedX;
		//App->render->camera.x -= cameraSpeedX;
		if (currentAnimation != &leftAnim)
		{
			//leftAnim.Reset();
			currentAnimation = &leftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
	{
		App->player->position.x = App->player->position.x + speedX;
		//App->render->camera.x += cameraSpeedX;
		if (currentAnimation != &rightAnim)
		{
			//rightAnim.Reset();
			currentAnimation = &rightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT)
	{
		App->player->position.y = App->player->position.y + speedY;
		//App->render->camera.y += cameraSpeedY;
		if (currentAnimation != &downAnim)
		{
			//downAnim.Reset();
			currentAnimation = &downAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT)
	{
		if (currentAnimation != &downLeftAnim)
		{
			//downLeftAnim.Reset();
			currentAnimation = &downLeftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT)
	{
		if (currentAnimation != &downRightAnim)
		{
			//downRightAnim.Reset();
			currentAnimation = &downRightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
	{
		App->player->position.y = App->player->position.y - speedY;
		//App->render->camera.y -= cameraSpeedY;
		if (currentAnimation != &upAnim)
		{
			//upAnim.Reset();
			currentAnimation = &upAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
	{
		if (currentAnimation != &upLeftAnim)
		{
			//upLeftAnim.Reset();
			currentAnimation = &upLeftAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
	{
		if (currentAnimation != &upRightAnim)
		{
			//upRightAnim.Reset();
			currentAnimation = &upRightAnim;
		}
	}

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->audio->PlayFx(shot06);

		if (currentAnimation == &idleUpAnim || currentAnimation == &upAnim)
		{
			if (collectedItemID == 0)
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->shotUp, position.x + 10, position.y, Collider::Type::PLAYER_SHOT);
			}
			else if (collectedItemID == 1)
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->dualShotUp, position.x + 10, position.y, Collider::Type::PLAYER_SHOT);
			}
		}

		if (currentAnimation == &idledownAnim || currentAnimation == &downAnim)
		{
			if (collectedItemID == 0)
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x + 5, position.y + 25, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->shotDown, position.x + 5, position.y + 15, Collider::Type::PLAYER_SHOT);
			}
			else if (collectedItemID == 1)
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x + 5, position.y + 25, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->dualShotDown, position.x + 5, position.y + 15, Collider::Type::PLAYER_SHOT);
			}
		}

		if (currentAnimation == &idleLeftAnim || currentAnimation == &leftAnim)
		{
			if (collectedItemID == 0)
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x - 8, position.y + 8, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->shotLeft, position.x - 3, position.y + 8, Collider::Type::PLAYER_SHOT);
			}
			else if (collectedItemID == 1)
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x - 8, position.y + 8, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->dualShotLeft, position.x - 3, position.y + 8, Collider::Type::PLAYER_SHOT);
			}
		}

		if (currentAnimation == &idleRightAnim || currentAnimation == &rightAnim)
		{
			if (collectedItemID == 0)
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x + 25, position.y + 8, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->shotRight, position.x + 18, position.y + 8, Collider::Type::PLAYER_SHOT);
			}
			else if (collectedItemID == 1)
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x + 25, position.y + 8, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->dualShotRight, position.x + 18, position.y + 8, Collider::Type::PLAYER_SHOT);
			}
		}

		if (currentAnimation == &idleUpLeftAnim || currentAnimation == &upLeftAnim)
		{
			if (collectedItemID == 0)
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x - 5, position.y - 5, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->shotUpLeft, position.x, position.y, Collider::Type::PLAYER_SHOT);
			}
			else if (collectedItemID == 1)
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x - 5, position.y - 5, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->dualShotUpLeft, position.x, position.y, Collider::Type::PLAYER_SHOT);
			}
		}

		if (currentAnimation == &idleDownLeftAnim || currentAnimation == &downLeftAnim)
		{
			if (collectedItemID == 0)
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x - 5, position.y + 20, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->shotDownLeft, position.x, position.y + 15, Collider::Type::PLAYER_SHOT);
			}
			else if (collectedItemID == 1)
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x - 5, position.y + 20, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->dualShotDownLeft, position.x, position.y + 15, Collider::Type::PLAYER_SHOT);
			}
		}

		if (currentAnimation == &idleUpRightAnim || currentAnimation == &upRightAnim)
		{
			if (collectedItemID == 0)
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x + 25, position.y - 5, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->shotUpRight, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			}
			else if (collectedItemID == 1)
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x + 25, position.y - 5, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->dualShotUpRight, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
			}
		}

		if (currentAnimation == &idleDownRightAnim || currentAnimation == &downRightAnim)
		{
			if (collectedItemID == 0)
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x + 25, position.y + 20, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->shotDownRight, position.x + 15, position.y + 10, Collider::Type::PLAYER_SHOT);
			}
			else if (collectedItemID == 1)
			{
				App->particles->AddParticle(App->particles->shotEffect, position.x + 25, position.y + 20, Collider::Type::NONE);
				App->particles->AddParticle(App->particles->dualShotDownRight, position.x + 15, position.y + 10, Collider::Type::PLAYER_SHOT);
			}
		}
	}

	// If no up/down movement detected, set the current animation back to idle
	if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE
		&& App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE)
		currentAnimation = &idledownAnim;

	if (App->input->keys[SDL_SCANCODE_F3] == Key_State::KEY_DOWN)
	{
		activateWinCondition = true;
	}

	collider->SetPos(position.x + 6, position.y + 3);

	currentAnimation->Update();

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (!destroyed)
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect, 1.0);
	}

	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%5d", score);


	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(40, 25, scoreFont, scoreText);


	App->render->Blit(merc, 10, 10, NULL, 0, true);
	App->render->Blit(mercLife, -15, 315, NULL, 0, true);
	App->render->Blit(insertcoin, 80, 360, NULL, 0, true);
	App->render->Blit(insertcoin, 160, 360, NULL, 0, true);
		

	
	//App->fonts->BlitText(100, 10, scoreFont, "0123456789");

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (((c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY_SHOT) ||
		(c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY)) && destroyed == false)
	{

		App->audio->PlayFx(dead26);

		if (currentAnimation == &idleUpAnim || currentAnimation == &idleUpLeftAnim || currentAnimation == &idleLeftAnim || currentAnimation == &idleUpRightAnim ||
			currentAnimation == &upAnim || currentAnimation == &upLeftAnim || currentAnimation == &upRightAnim || currentAnimation == &leftAnim)
			currentAnimation = &deadBackAnim;

		if (currentAnimation == &idledownAnim || currentAnimation == &idleDownLeftAnim || currentAnimation == &idleRightAnim || currentAnimation == &idleDownRightAnim ||
			currentAnimation == &downAnim || currentAnimation == &downLeftAnim || currentAnimation == &downRightAnim || currentAnimation == &rightAnim)
			currentAnimation = &deadFrontAnim;

		App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneIntro, 60);

		destroyed = true;
	}

	if (c1->type == Collider::Type::PLAYER_SHOT && c2->type == Collider::Type::ENEMY)
	{
		 score += 150;
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WALL)
	{
		speedX = 0;
		speedY = 0;
		if (wallCollision == false)
		{
			wallCollision = true;
		}

		if (currentAnimation == &downAnim)
		{
			position.y = position.y - 1;
			speedX = 1;
			speedY = 1;
		}
		if (currentAnimation == &upAnim)
		{
			position.y = position.y + 1;
			speedX = 1;
			speedY = 1;
		}
		if (currentAnimation == &leftAnim)
		{
			position.x = position.x + 1;
			speedX = 1;
			speedY = 1;
		}
		if (currentAnimation == &rightAnim)
		{
			position.x = position.x - 1;
			speedX = 1;
			speedY = 1;
		}
		if (currentAnimation == &upRightAnim)
		{
			position.x = position.x - 1;
			position.y = position.y + 1;
			speedX = 1;
			speedY = 1;
		}
		if (currentAnimation == &upLeftAnim)
		{
			position.x = position.x + 1;
			position.y = position.y + 1;
			speedX = 1;
			speedY = 1;
		}
		if (currentAnimation == &downRightAnim)
		{
			position.x = position.x - 1;
			position.y = position.y - 1;
			speedX = 1;
			speedY = 1;
		}
		if (currentAnimation == &downLeftAnim)
		{
			position.x = position.x + 1;
			position.y = position.y - 1;
			speedX = 1;
			speedY = 1;
		}
	}
	else if (c1->type == Collider::Type::PLAYER && c2->type != Collider::Type::WALL)
	{
		speedX = 1;
		speedY = 1;

		wallCollision = false;
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::TRENCH_WALL)
	{
		speedX = 0;
		speedY = 0;
		if (trenchWallCollision == false)
		{
			trenchWallCollision = true;
		}

		if (currentAnimation == &downAnim)
		{
			position.y = position.y - 1;
			speedX = 1;
			speedY = 1;
		}
		if (currentAnimation == &upAnim)
		{
			position.y = position.y + 1;
			speedX = 1;
			speedY = 1;
		}
		if (currentAnimation == &leftAnim)
		{
			position.x = position.x + 1;
			speedX = 1;
			speedY = 1;
		}
		if (currentAnimation == &rightAnim)
		{
			position.x = position.x - 1;
			speedX = 1;
			speedY = 1;
		}
		if (currentAnimation == &upRightAnim)
		{
			position.x = position.x - 1;
			position.y = position.y + 1;
			speedX = 1;
			speedY = 1;
		}
		if (currentAnimation == &upLeftAnim)
		{
			position.x = position.x + 1;
			position.y = position.y + 1;
			speedX = 1;
			speedY = 1;
		}
		if (currentAnimation == &downRightAnim)
		{
			position.x = position.x - 1;
			position.y = position.y - 1;
			speedX = 1;
			speedY = 1;
		}
		if (currentAnimation == &downLeftAnim)
		{
			position.x = position.x + 1;
			position.y = position.y - 1;
			speedX = 1;
			speedY = 1;
		}
	}
	else if (c1->type == Collider::Type::PLAYER && c2->type != Collider::Type::TRENCH_WALL)
	{
		speedX = 1;
		speedY = 1;

		trenchWallCollision = false;
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::HORIZONTAL_CAMERA_BOUND)
	{
		cameraXlimitation = true;
	}
	else if (c1->type == Collider::Type::PLAYER && c2->type != Collider::Type::HORIZONTAL_CAMERA_BOUND)
	{
		cameraXlimitation = false;
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::VERTICAL_CAMERA_BOUND)
	{
		cameraYlimitation = true;
	}
	else if (c1->type == Collider::Type::PLAYER && c2->type != Collider::Type::VERTICAL_CAMERA_BOUND)
	{
		cameraYlimitation = false;
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WATER)
	{
		waterSink = 20;
		App->particles->AddParticle(App->particles->waterParticles, position.x, position.y + 20, Collider::Type::NONE);
	}
	else if (c1->type == Collider::Type::PLAYER && c2->type != Collider::Type::WATER)
	{
		waterSink = 0;
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::BIDIMENSIONAL_CAMERA_BOUND)
	{
		bidimensionalCameraLimitation = true;
	}
	else if (c1->type == Collider::Type::PLAYER && c2->type != Collider::Type::BIDIMENSIONAL_CAMERA_BOUND)
	{
		bidimensionalCameraLimitation = false;
	}

	if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::DOUBLE_SHOT_WEAPON_ID01)
	{
		collectedItemID = 1;
	}
}
