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
	helicopterAnimation.PushBack({ 14, 24, 50, 26 });
	helicopterAnimation.PushBack({ 66, 24, 50, 26 });
	helicopterAnimation.PushBack({ 39, 60, 50, 26 });
	helicopterAnimation.loop = true;
	helicopterAnimation.speed = 0.2f;
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
	helicopter1 = App->textures->Load("Assets/Art/Sequences/h1.png");
	helicopter2 = App->textures->Load("Assets/Art/Sequences/h2.png");
	helicopter3 = App->textures->Load("Assets/Art/Sequences/h3.png");

	messagePart1 = App->textures->Load("Assets/Art/Sequences/textintro1.png");
	messagePart2 = App->textures->Load("Assets/Art/Sequences/textintro2.png");
	messagePart3 = App->textures->Load("Assets/Art/Sequences/textintro3.png");
	messagePart4 = App->textures->Load("Assets/Art/Sequences/textintro4.png");
	messagePart5 = App->textures->Load("Assets/Art/Sequences/textintro5.png");


	App->audio->PlayMusic("Assets/Music/None.ogg", 1.0f);

	delay = 0;
	//On apareixen els Helicopters
	counterFrame_x = 80;
	counterFrame_y = 70;

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
	if (delay >= 2050) // <-- Whatever the animation takes
	{
		App->fade->FadeToBlack(this, (Module*)App->sceneIntro, 90);
	}

	if ((delay % 10) == 0)
	{
		counterFrame_y--;
		if (delay >= 180)
		{
			counterFrame_x--;
		}
	}
	if ((delay % 2) == 0)
	{
		helicopter = helicopter2;
	}
	if ((delay % 4) == 0)
	{
		helicopter = helicopter3;
	}
	if ((delay % 6) == 0)
	{
		helicopter = helicopter1;
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status WhiteHouseIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(whiteHouse, 0, 0, NULL);
	App->render->Blit(helicopter, counterFrame_x, counterFrame_y, NULL);
	App->render->Blit(houseTop, 0, 0, NULL);

	//Si va muy rapido cambiar el delay de abajo

	if (delay >= 200 && delay <= 600) App->render->Blit(messagePart1, -200, 10, NULL);
	if (delay >= 650 && delay <= 950) App->render->Blit(messagePart2, -200, 10, NULL);
	if (delay >= 1000 && delay <= 1300) App->render->Blit(messagePart3, -200, 10, NULL);
	if (delay >= 1350 && delay <= 1650) App->render->Blit(messagePart4, -200, 10, NULL);
	if (delay >= 1700 && delay <= 2000) App->render->Blit(messagePart5, -200, 10, NULL);

	return Update_Status::UPDATE_CONTINUE;
}