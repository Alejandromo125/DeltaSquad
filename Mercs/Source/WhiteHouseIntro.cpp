#include "WhiteHouseIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

WhiteHouseIntro::WhiteHouseIntro(bool startEnabled) : Module(startEnabled)
{

}

WhiteHouseIntro::~WhiteHouseIntro()
{

}

// Load assets
bool WhiteHouseIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	whiteHouse = App->textures->Load("Assets/Art/Sequences/house.png");
	houseTop = App->textures->Load("Assets/Art/Sequences/houseTop.png");
	helicopter = App->textures->Load("Assets/Art/Sequences/helicopter.png");

	App->audio->PlayMusic("Assets/Music/None.ogg", 1.0f);

	delay = 0;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->cameraXlimitation = true;
	App->player->cameraYlimitation = true;

	return ret;
}

Update_Status WhiteHouseIntro::Update()
{

	delay++;
	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}
	if (delay >= 1200) // <-- Whatever the animation takes
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status WhiteHouseIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(whiteHouse, 0, 0, NULL);
	App->render->Blit(helicopter, 0, 0, NULL);
	App->render->Blit(houseTop, 0, 0, NULL);

	App->render->Blit(messagePart1, 0, 0, NULL);
	App->render->Blit(messagePart2, 0, 0, NULL);
	App->render->Blit(messagePart3, 0, 0, NULL);
	App->render->Blit(messagePart4, 0, 0, NULL);

	return Update_Status::UPDATE_CONTINUE;
}