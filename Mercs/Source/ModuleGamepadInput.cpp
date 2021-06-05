#include "ModuleGamepadInput.h"
#include "ModulePlayer.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleInput.h"

#include <stdio.h>
#include <SDL\include\SDL_timer.h>
#include <SDL_mixer/include/SDL_mixer.h>
#include <SDL/include/SDL_gamecontroller.h>
#include <SDL/include/SDL_haptic.h>

ModuleGamepadInput::ModuleGamepadInput(bool startEnabled) : Module(startEnabled)
{

}

ModuleGamepadInput::~ModuleGamepadInput()
{

}

bool ModuleGamepadInput::Start()
{
	LOG("Loading Gamepad Module");

	bool ret = true;

	char lookupTable[] = { "0123456789" };
	scoreFont = App->fonts->Load("Assets/Art/UI/numbers_s.png", lookupTable, 1);

	keyDownDelay = 0;
	
	return ret;
}

Update_Status ModuleGamepadInput::Update()
{
	// Get gamepad info
	GamePad& pad = App->input->pads[0];
	
	if (pad.left_x < 0.0f)
	{
		App->input->keys[SDL_SCANCODE_LEFT] = Key_State::KEY_REPEAT;

	}

	if (pad.left_x > 0.0f)
	{
		App->input->keys[SDL_SCANCODE_RIGHT] = Key_State::KEY_REPEAT;

	}

	if (pad.left_y > 0.0f)
	{
		App->input->keys[SDL_SCANCODE_DOWN] = Key_State::KEY_REPEAT;

	}

	if (pad.left_x < 0.0f && pad.left_y > 0.0f)
	{
		App->input->keys[SDL_SCANCODE_LEFT] = Key_State::KEY_REPEAT;
		App->input->keys[SDL_SCANCODE_DOWN] = Key_State::KEY_REPEAT;

	}

	if (pad.left_x > 0.0f && pad.left_y > 0.0f)
	{
		App->input->keys[SDL_SCANCODE_RIGHT] = Key_State::KEY_REPEAT;
		App->input->keys[SDL_SCANCODE_DOWN] = Key_State::KEY_REPEAT;
	}

	if (pad.left_y < 0.0f)
	{
		App->input->keys[SDL_SCANCODE_UP] = Key_State::KEY_REPEAT;

	}

	if (pad.left_x < 0.0f && pad.left_y < 0.0f)
	{
		App->input->keys[SDL_SCANCODE_LEFT] = Key_State::KEY_REPEAT;
		App->input->keys[SDL_SCANCODE_UP] = Key_State::KEY_REPEAT;

	}

	if (pad.left_x > 0.0f && pad.left_y < 0.0f)
	{
		App->input->keys[SDL_SCANCODE_RIGHT] = Key_State::KEY_REPEAT;
		App->input->keys[SDL_SCANCODE_UP] = Key_State::KEY_REPEAT;
	}

	

	if (pad.a == true && keyDownDelay > 15)
	{
		App->input->keys[SDL_SCANCODE_SPACE] = Key_State::KEY_DOWN;

		if (App->sceneLevel_1->SceneCounter != 0)
		{
			App->input->ShakeController(0, 120, 0.05f);
		}
		if (App->sceneLevel_2->SceneCounter != 0)
		{
			App->input->ShakeController(0, 120, 0.05f);
		}
		

		keyDownDelay = 0;
	}

	keyDownDelay++;

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleGamepadInput::DebugDrawGamepadInfo()
{
	GamePad& pad = App->input->pads[0];

	sprintf_s(scoreText, 150, "pad 0 %s, press 1/2/3 for rumble", (pad.enabled) ? "plugged" : "not detected");
	App->fonts->BlitText(5, 10, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "buttons %s %s %s %s %s %s %s %s %s %s %s",
		(pad.a) ? "a" : "",
		(pad.b) ? "b" : "",
		(pad.x) ? "x" : "",
		(pad.y) ? "y" : "",
		(pad.start) ? "start" : "",
		(pad.back) ? "back" : "",
		(pad.guide) ? "guide" : "",
		(pad.l1) ? "lb" : "",
		(pad.r1) ? "rb" : "",
		(pad.l3) ? "l3" : "",
		(pad.r3) ? "r3" : ""
	);
	App->fonts->BlitText(5, 20, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "dpad %s %s %s %s",
		(pad.up) ? "up" : "",
		(pad.down) ? "down" : "",
		(pad.left) ? "left" : "",
		(pad.right) ? "right" : ""
	);
	App->fonts->BlitText(5, 30, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "left trigger  %0.2f", pad.l2);
	App->fonts->BlitText(5, 40, scoreFont, scoreText);
	sprintf_s(scoreText, 150, "right trigger %0.2f", pad.r2);
	App->fonts->BlitText(5, 50, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "left thumb    %.2fx, %0.2fy", pad.left_x, pad.left_y);
	App->fonts->BlitText(5, 60, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "   deadzone   %0.2f", pad.left_dz);
	App->fonts->BlitText(5, 70, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "right thumb   %.2fx, %0.2fy", pad.right_x, pad.right_y);
	App->fonts->BlitText(5, 80, scoreFont, scoreText);

	sprintf_s(scoreText, 150, "   deadzone   %0.2f", pad.right_dz);
	App->fonts->BlitText(5, 90, scoreFont, scoreText);
}