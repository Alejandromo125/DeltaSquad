#include "ModulePlayer.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "Boss.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleInput.h"

#include <stdio.h>
#include <SDL\include\SDL_timer.h>
#include <SDL_mixer/include/SDL_mixer.h>
#include <SDL/include/SDL_gamecontroller.h>

ModulePlayer::ModulePlayer(bool startEnabled) : Module(startEnabled)
{

	// Idle Animations
	// Up
	idleUpAnim.PushBack({ 140, 7, 30, 43 - waterSink }); //Water sink effect does not work
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
	idleUpLeftAnim.PushBack({ 140, 54, 30, 43 - waterSink });
	idleUpLeftAnim.loop = false;
	// Up Right
	idleUpRightAnim.PushBack({ 135, 333, 30, 43 - waterSink });
	idleUpRightAnim.loop = false;
	// Down Left
	idleDownLeftAnim.PushBack({ 138, 147, 30, 43 - waterSink });
	idleDownLeftAnim.loop = false;
	// Down Right
	idleDownRightAnim.PushBack({ 138, 239, 30, 43 - waterSink });
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
	deadFrontAnim.PushBack({ 0, 420, 34, 45 - waterSink });
	deadFrontAnim.PushBack({ 178, 375, 35, 45 - waterSink });
	deadFrontAnim.PushBack({ 83, 420, 35, 45 - waterSink });
	deadFrontAnim.PushBack({ 148, 420, 38, 45 - waterSink });
	deadFrontAnim.loop = false;
	deadFrontAnim.speed = 0.1f;

	// Die Down
	//Insert pushBack
	deadBackAnim.PushBack({ 4, 375, 35, 45 - waterSink });
	deadBackAnim.PushBack({ 37, 375, 35, 45 - waterSink });
	deadBackAnim.PushBack({ 70, 375, 35, 45 - waterSink });
	deadBackAnim.PushBack({ 108, 375, 35, 45 - waterSink });
	deadBackAnim.loop = false;
	deadBackAnim.speed = 0.1f;

	winAnim.PushBack({ 393, 255, 35, 45 - waterSink });
	winAnim.loop = false;
	winAnim.speed = 0.1f;
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
	winScreen1 = App->textures->Load("Assets/Art/UI/mission1Complete.png");

	currentAnimation = &idledownAnim;

	shot06 = App->audio->LoadFx("Assets/FX/06.wav");
	dead26 = App->audio->LoadFx("Assets/FX/26.wav");
	hit28 = App->audio->LoadFx("Assets/FX/28.wav");
	collectItem18 = App->audio->LoadFx("Assets/FX/18.wav");

	roundClear = App->audio->LoadFx("Assets/FX/RoundClear.wav");
	gameClear = App->audio->LoadFx("Assets/FX/RankingDisplay.wav");
	gameOver = App->audio->LoadFx("Assets/FX/GameOver.wav");

	delay = 0;

	speedX = 1;
	speedY = 1;

	destroyed = false;
	activateWinCondition = false;
	activateWinCondition_FINAL = false;

	playerLife = 100;
	immunityTime = 0;
	playerDelay = 0;
	playerFPS = 0;
	bossZoneCounter = 0;

	fallingWallEvent = false;
	bossZoneEvent = false;

	timeCounter = 180;

	cameraXlimitation = false;
	cameraYlimitation = false;
	bidimensionalCameraLimitation = false;

	collectedItemID = 0; // ID 0 is single shot weapon, ID 1 is dual shot weapon, ID 2 is green shot weapon, ID 3 is healing food

	//collectedMegaBombsNumber = 1; // Player starts with 1 MegaBomb available -=(MegaBomb mechanic is not implemented yet so it wont have any effect for now)=-

	collider = App->collisions->AddCollider({ position.x + 5, position.y + 3, 16, 32 }, Collider::Type::PLAYER, this);


	//App->render->camera.x = (SCREEN_WIDTH / 2) * SCREEN_SIZE;
	//App->render->camera.y = (SCREEN_HEIGHT / 2) * SCREEN_SIZE;

	// TODO 0: Notice how a font is loaded and the meaning of all its arguments 
	//char lookupTable[] = { "!  ,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz" };
	//scoreFont = App->fonts->Load("Assets/Fonts/rtype_font.png", "! @,_./0123456789$;<&?abcdefghijklmnopqrstuvwxyz", 1);

	// TODO 4: Try loading "rtype_font3.png" that has two rows to test if all calculations are correct
	char lookupTable[] = { "0123456789" };
	scoreFont = App->fonts->Load("Assets/Art/UI/numbers_s.png", lookupTable, 1);
	timeFont = App->fonts->Load("Assets/Art/UI/numbers2.png", lookupTable, 1);
	
	return ret;
}

Update_Status ModulePlayer::Update()
{
	if (activateWinCondition == false)
	{
		delay++;
	}
	
	if (destroyed == false && activateWinCondition == false && activateWinCondition_FINAL == false)
	{
		if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && position.x > 0 )
		{
			if (bossZoneEvent == false)
			{
				App->player->position.x = App->player->position.x - speedX;
				//App->render->camera.x -= cameraSpeedX;
				if (currentAnimation != &leftAnim)
				{
					//leftAnim.Reset();
					currentAnimation = &leftAnim;
					PlayerLookingPosition = 1;
				}
			}
			else if (bossZoneEvent == true)
			{
				if (position.x > 630 - 120)
				{
					App->player->position.x = App->player->position.x - speedX;
					//App->render->camera.x -= cameraSpeedX;
					if (currentAnimation != &leftAnim)
					{
						//leftAnim.Reset();
						currentAnimation = &leftAnim;
						PlayerLookingPosition = 1;
					}
				}
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
				PlayerLookingPosition = 2;
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
				PlayerLookingPosition = 3;
			}
			
		}

		if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT)
		{
			if (currentAnimation != &downLeftAnim)
			{
				//downLeftAnim.Reset();
				currentAnimation = &downLeftAnim;
				PlayerLookingPosition = 5;
			}

		}

		if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_REPEAT)
		{
			if (currentAnimation != &downRightAnim)
			{
				//downRightAnim.Reset();
				currentAnimation = &downRightAnim;
				PlayerLookingPosition = 6;
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
				PlayerLookingPosition = 4;
			}
			
		}

		if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
		{
			if (currentAnimation != &upLeftAnim)
			{
				//upLeftAnim.Reset();
				currentAnimation = &upLeftAnim;
				PlayerLookingPosition = 7;
			}
			
		}

		if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT && App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
		{
			if (currentAnimation != &upRightAnim)
			{
				//upRightAnim.Reset();
				currentAnimation = &upRightAnim;
				PlayerLookingPosition = 8;
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
				else if (collectedItemID == 2)
				{
					App->particles->AddParticle(App->particles->shotEffect, position.x + 10, position.y - 5, Collider::Type::NONE);
					App->particles->AddParticle(App->particles->greenShotUp, position.x + 10, position.y, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->greenShotUpLeft, position.x + 10, position.y, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->greenShotUpRight, position.x + 10, position.y, Collider::Type::PLAYER_SHOT);
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
				else if (collectedItemID == 2)
				{
					App->particles->AddParticle(App->particles->shotEffect, position.x + 5, position.y + 25, Collider::Type::NONE);
					App->particles->AddParticle(App->particles->greenShotDown, position.x + 5, position.y + 15, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->greenShotDownLeft, position.x + 5, position.y + 15, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->greenShotDownRight, position.x + 5, position.y + 15, Collider::Type::PLAYER_SHOT);
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
				else if (collectedItemID == 2)
				{
					App->particles->AddParticle(App->particles->shotEffect, position.x - 8, position.y + 8, Collider::Type::NONE);
					App->particles->AddParticle(App->particles->greenShotLeft, position.x - 3, position.y + 8, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->greenShotUpLeft, position.x - 3, position.y + 8, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->greenShotDownLeft, position.x - 3, position.y + 8, Collider::Type::PLAYER_SHOT);
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
				else if (collectedItemID == 2)
				{
					App->particles->AddParticle(App->particles->shotEffect, position.x + 25, position.y + 8, Collider::Type::NONE);
					App->particles->AddParticle(App->particles->greenShotRight, position.x + 18, position.y + 8, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->greenShotUpRight, position.x + 18, position.y + 8, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->greenShotDownRight, position.x + 18, position.y + 8, Collider::Type::PLAYER_SHOT);
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
				else if (collectedItemID == 2)
				{
					App->particles->AddParticle(App->particles->shotEffect, position.x - 5, position.y - 5, Collider::Type::NONE);
					App->particles->AddParticle(App->particles->greenShotUpLeft, position.x, position.y, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->greenShotUp, position.x, position.y, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->greenShotLeft, position.x, position.y, Collider::Type::PLAYER_SHOT);
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
				else if (collectedItemID == 2)
				{
					App->particles->AddParticle(App->particles->shotEffect, position.x - 5, position.y + 20, Collider::Type::NONE);
					App->particles->AddParticle(App->particles->greenShotDownLeft, position.x, position.y + 15, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->greenShotDown, position.x, position.y + 15, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->greenShotLeft, position.x, position.y + 15, Collider::Type::PLAYER_SHOT);
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
				else if (collectedItemID == 2)
				{
					App->particles->AddParticle(App->particles->shotEffect, position.x + 25, position.y - 5, Collider::Type::NONE);
					App->particles->AddParticle(App->particles->greenShotUpRight, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->greenShotUp, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->greenShotRight, position.x + 20, position.y, Collider::Type::PLAYER_SHOT);
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
				else if (collectedItemID == 2)
				{
					App->particles->AddParticle(App->particles->shotEffect, position.x + 25, position.y + 20, Collider::Type::NONE);
					App->particles->AddParticle(App->particles->greenShotDownRight, position.x + 15, position.y + 10, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->greenShotDown, position.x + 15, position.y + 10, Collider::Type::PLAYER_SHOT);
					App->particles->AddParticle(App->particles->greenShotRight, position.x + 15, position.y + 10, Collider::Type::PLAYER_SHOT);
				}
			}
		}



		if (App->player->wallCollision == false && App->player->trenchWallCollision == false && App->player->breakableObjectCollision == false
			&& App->player->destroyed == false && bossZoneEvent == false)
		{
			if (App->player->cameraXlimitation == false && App->player->bidimensionalCameraLimitation == false)
			{
				if (App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_REPEAT)
				{

					if (App->render->camera.x / SCREEN_SIZE + App->render->camera.w + speedX < 1242)
					{

						if (position.x + 70 > App->render->camera.x / SCREEN_SIZE + App->render->camera.w - horizontalMargin)
						{
							App->render->camera.x += speedX + (SCREEN_SIZE - 1);
						}

					}

				}
				if (App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_REPEAT)
				{


					if (App->render->camera.x / SCREEN_SIZE - App->render->camera.w - speedX < 1242)
					{

						if (position.x - 285 < App->render->camera.x / SCREEN_SIZE - App->render->camera.w + horizontalMargin)
						{
							App->render->camera.x -= speedX + (SCREEN_SIZE - 1);
						}

					}
				}
			}

			if (App->player->cameraYlimitation == false && App->player->bidimensionalCameraLimitation == false)
			{
				if (App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_REPEAT)
				{
					if (position.y - 50 < (App->render->camera.y / SCREEN_SIZE + verticalMargin)) App->render->camera.y -= speedY + (SCREEN_SIZE - 1);
				}
				
			}

		}

		// If no up/down movement detected, set the current animation back to idle
		if (App->input->keys[SDL_SCANCODE_DOWN] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_UP] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_RIGHT] == Key_State::KEY_IDLE
			&& App->input->keys[SDL_SCANCODE_LEFT] == Key_State::KEY_IDLE)
		{
			switch(PlayerLookingPosition)
			{
			case 1:
				currentAnimation = &idleLeftAnim;
				break;
			case 2:
				currentAnimation = &idleRightAnim;
				break;
			case 3:
				currentAnimation = &idledownAnim;
				break;
			case 4:
				currentAnimation = &idleUpAnim;
				break;
			case 5:
				currentAnimation = &idleDownLeftAnim;
				break;
			case 6:
				currentAnimation = &idleDownRightAnim;
				break;
			case 7:
				currentAnimation = &idleUpLeftAnim;
				break;
			case 8:
				currentAnimation = &idleUpRightAnim;
				break;
			}
		}
			
	}

	if (destroyed == true)
	{
		bossZoneEvent = false;
		if (currentAnimation == &idleUpAnim || currentAnimation == &idleUpLeftAnim || currentAnimation == &idleLeftAnim || currentAnimation == &idleUpRightAnim ||
			currentAnimation == &upAnim || currentAnimation == &upLeftAnim || currentAnimation == &upRightAnim || currentAnimation == &leftAnim)
		{
			deadBackAnim.Reset();
			currentAnimation = &deadBackAnim;
		}

		if (currentAnimation == &idledownAnim || currentAnimation == &idleDownLeftAnim || currentAnimation == &idleRightAnim || currentAnimation == &idleDownRightAnim ||
			currentAnimation == &downAnim || currentAnimation == &downLeftAnim || currentAnimation == &downRightAnim || currentAnimation == &rightAnim)
		{
			deadFrontAnim.Reset();
			currentAnimation = &deadFrontAnim;
		}

		playerDelay++;
	}

	if (activateWinCondition == true)
	{
		bossZoneEvent = false;

		winAnim.Reset();
		currentAnimation = &winAnim;

		playerDelay++;
		
	}
	
	if (activateWinCondition_FINAL == true)
	{
		bossZoneEvent = false;
		winAnim.Reset();
		currentAnimation = &winAnim;

		playerDelay++;

	}

	if (App->player->bossZoneEvent == true)
	{
		if (bossZoneCounter < 1) Mix_PauseMusic();

		if (bossZoneCounter == 1)
		{
			App->audio->PlayMusic("Assets/Music/Boss1.ogg", 0.0f);
		}

		bossZoneCounter++;

	}

	if ((delay % 60) == 0 && destroyed == false && activateWinCondition == false && activateWinCondition_FINAL == false)
	{
		/*
		if (timeCounter <= 0)
		{
			timeCounter == 0;
		}
		*/
		timeCounter--;
	}
	
	if (App->input->keys[SDL_SCANCODE_F5] == Key_State::KEY_DOWN)
	{
		playerLife = 0;
		destroyed = true;
	}

	collider->SetPos(position.x + 6, position.y + 3);

	currentAnimation->Update();

	
	immunityTime++;
	playerFPS++;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModulePlayer::PostUpdate()
{
	if (destroyed == true)
	{
		App->fonts->BlitText(30, 100, scoreFont, "Mission Failed"); // Text UI does not work

		Mix_PauseMusic();
		if (playerDelay <= 1) App->audio->PlayFx(gameOver);
		
	}

	if (activateWinCondition == true)
	{

		if (playerDelay >= 215)
		{
			App->render->Blit(winScreen1, 8, 50, NULL, 0, true);
			Mix_PauseMusic();
			if (playerDelay < 216) App->audio->PlayFx(roundClear);

			if (playerDelay >= 480 + 215)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_1, (Module*)App->sceneLevel_2, 60);
			}
		}
		
	}

	if (activateWinCondition_FINAL == true)
	{

		Mix_PauseMusic();

		if (playerDelay >= 215)
		{
			App->fonts->BlitText(30, 100, scoreFont, "President Rescued!"); // Text UI does not work

			if (playerDelay <= 215) App->audio->PlayFx(gameClear);

			if (playerDelay >= 480 + 215)
			{
				App->fade->FadeToBlack((Module*)App->sceneLevel_2, (Module*)App->sceneIntro, 30);
			}
		}
		

	}

	if (immunityTime <= 120)
	{
		if ((playerFPS / 5) % 2 == 0)
		{
			SDL_Rect rect = currentAnimation->GetCurrentFrame();
			App->render->Blit(texture, position.x, position.y, &rect, 1.0);
		}
	}
	else
	{
		SDL_Rect rect = currentAnimation->GetCurrentFrame();
		App->render->Blit(texture, position.x, position.y, &rect, 1.0);
	}

	
	// Draw UI (score) --------------------------------------
	sprintf_s(scoreText, 10, "%5d", score);
	sprintf_s(timeText, 10, "%3d", timeCounter);

	SDL_Rect quad;
	quad = { 5, 338, playerLife, 10 };

	SDL_Rect bgquad;
	bgquad = { 3, 336, 104, 14 };
	App->render->DrawQuad(bgquad, 255, 255, 255, 165, 0.0f, true);

	if (playerLife > 50)
	{
		App->render->DrawQuad(quad, 0, 255, 0, 165, 0.0f, true);
	}
	else if (playerLife > 20 && playerLife <= 50)
	{
		App->render->DrawQuad(quad, 255, 255, 0, 165, 0.0f, true);
	}
	else
	{
		if ((playerFPS / 5) % 2 == 0)
		{
			App->render->DrawQuad(quad, 255, 0, 0, 165, 0.0f, true);
		}
		else
		{
			App->render->DrawQuad(quad, 255, 150, 0, 165, 0.0f, true);
		}

	}

	if (timeCounter <= 0)
	{
		timeCounter = 0;
		playerLife = 0;
		App->audio->PlayFx(dead26);
		destroyed = true;
	}

	// TODO 3: Blit the text of the score in at the bottom of the screen
	App->fonts->BlitText(40, 25, scoreFont, scoreText);

	// Timer
	App->fonts->BlitText(180, 10, timeFont, timeText);


	App->render->Blit(merc, 10, 10, NULL, 0, true);
	App->render->Blit(mercLife, -15, 315, NULL, 0, true);
	App->render->Blit(insertcoin, 80, 360, NULL, 0, true);
	App->render->Blit(insertcoin, 160, 360, NULL, 0, true);
		

	
	//App->fonts->BlitText(100, 10, scoreFont, "0123456789");

	return Update_Status::UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (activateWinCondition == false && activateWinCondition_FINAL == false)
	{
		if (((c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY_SHOT) ||
			(c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY)) && destroyed == false && immunityTime >= 120)
		{

			playerLife -= 10;
			if (playerLife < 0) playerLife = 0;
			immunityTime = 0;
			if (playerLife != 0) App->audio->PlayFx(hit28);

			if (playerLife <= 0)
			{

				playerLife = 0;
				App->audio->PlayFx(dead26);
				destroyed = true;

			}
		}

		if ((c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::ENEMY_BOMB) && destroyed == false && immunityTime >= 120)
		{

			playerLife -= 15;
			if (playerLife < 0) playerLife = 0;
			immunityTime = 0;
			if (playerLife != 0) App->audio->PlayFx(hit28);

			if (playerLife <= 0)
			{

				playerLife = 0;
				App->audio->PlayFx(dead26);
				destroyed = true;

			}
		}

		if ((c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::BOSS_ATTACK) && destroyed == false && immunityTime >= 120)
		{

			playerLife -= 18;
			if (playerLife < 0) playerLife = 0;
			immunityTime = 0;
			if (playerLife != 0) App->audio->PlayFx(hit28);

			if (playerLife <= 0)
			{

				playerLife = 0;
				App->audio->PlayFx(dead26);
				destroyed = true;

			}

			
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

			if (wallCollision == true)
			{
				wallCollision = false;
			}

		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::BREAKABLE_OBJECT)
		{
			speedX = 0;
			speedY = 0;

			if (breakableObjectCollision == false)
			{
				breakableObjectCollision = true;
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
		else if (c1->type == Collider::Type::PLAYER && c2->type != Collider::Type::BREAKABLE_OBJECT)
		{
			speedX = 1;
			speedY = 1;

			if (breakableObjectCollision == true)
			{
				breakableObjectCollision = false;
			}

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

			if (trenchWallCollision == true)
			{
				trenchWallCollision = false;
			}

		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::HORIZONTAL_CAMERA_BOUND)
		{
			if (cameraXlimitation == false)
			{
				cameraXlimitation = true;
			}
		}
		else if (c1->type == Collider::Type::PLAYER && c2->type != Collider::Type::HORIZONTAL_CAMERA_BOUND)
		{
			if (cameraXlimitation == true)
			{
				cameraXlimitation = false;
			}
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::VERTICAL_CAMERA_BOUND)
		{
			if (cameraYlimitation == false)
			{
				cameraYlimitation = true;
			}
		}
		else if (c1->type == Collider::Type::PLAYER && c2->type != Collider::Type::VERTICAL_CAMERA_BOUND)
		{
			if (cameraYlimitation == true)
			{
				cameraYlimitation = false;
			}
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::WATER)
		{
			waterSink = 20;
			if (cameraYlimitation == false)
			{
				cameraYlimitation = true; // Does not make sense but its needed
			}

			if (cameraXlimitation == false)
			{
				cameraXlimitation = true; // Does not make sense but its needed
			}

			App->particles->AddParticle(App->particles->waterParticles, position.x, position.y + 20, Collider::Type::NONE);
		}
		else if (c1->type == Collider::Type::PLAYER && c2->type != Collider::Type::WATER)
		{
			waterSink = 0;
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::BIDIMENSIONAL_CAMERA_BOUND)
		{
			if (bidimensionalCameraLimitation == false)
			{
				bidimensionalCameraLimitation = true;
			}
		}
		else if (c1->type == Collider::Type::PLAYER && c2->type != Collider::Type::BIDIMENSIONAL_CAMERA_BOUND)
		{
			if (bidimensionalCameraLimitation == true)
			{
				bidimensionalCameraLimitation = false;
			}
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::DOUBLE_SHOT_WEAPON_ID01)
		{
			collectedItemID = 1;
			App->particles->doubleShotWeapon.SetToDelete();
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::GREEN_SHOT_WEAPON_ID02)
		{
			collectedItemID = 2;
			App->particles->greenShotWeapon.SetToDelete();
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::HEALING_FOOD_ID03)
		{
			playerLife += 15;

			if (playerLife >= 100)
			{
				playerLife = 100;
			}

			App->audio->PlayFx(collectItem18);
			App->particles->healingFood.SetToDelete();
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::EVENT_TRIGGER)
		{
			fallingWallEvent = true;
		}

		if (c1->type == Collider::Type::PLAYER && c2->type == Collider::Type::EVENT_TRIGGER_BOSS_ZONE)
		{
			bossZoneEvent = true;
		}
	}
}