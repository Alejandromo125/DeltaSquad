#include "InfoScreen.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

InfoScreen::InfoScreen(bool startEnabled) : Module(startEnabled)
{

}

InfoScreen::~InfoScreen()
{

}

// Load assets
bool InfoScreen::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	bgTexture = App->textures->Load("Assets/Art/Sequences/firstbg.png");

	App->audio->PlayMusic("Assets/Music/Assassin.ogg", 1.0f);

	delay = 0;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->cameraXlimitation = true;
	App->player->cameraYlimitation = true;

	return ret;
}

Update_Status InfoScreen::Update()
{

	delay++;
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->whiteHouseIntro, 90);
	}
	if (delay >= 420)
	{
		App->fade->FadeToBlack(this, (Module*)App->titleScreen, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status InfoScreen::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}