#include "HeroesIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

HeroesIntro::HeroesIntro(bool startEnabled) : Module(startEnabled)
{

}

HeroesIntro::~HeroesIntro()
{

}

// Load assets
bool HeroesIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	heroes = App->textures->Load("Assets/Art/Sequences/totalscene.png");

	white1 = App->textures->Load("Assets/Art/Sequences/white1.png");
	white2 = App->textures->Load("Assets/Art/Sequences/white2.png");
	white3 = App->textures->Load("Assets/Art/Sequences/white3.png");
	white4 = App->textures->Load("Assets/Art/Sequences/white4.png");
	

	App->audio->PlayMusic("Assets/Music/None.ogg", 1.0f);

	delay = 0;

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	timer = timerFinal;

	App->player->cameraXlimitation = true;
	App->player->cameraYlimitation = true;

	return ret;
}

Update_Status HeroesIntro::Update()
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

	if (timer <= 0)
	{
		if (counter < 2) {
			timerFinal = 500;
			timer = timerFinal;
			speed = 6;
			framesScroll = 124;
			counter++;
		}
	}

	timer--;
	scrollHeroes(speed, framesScroll);


	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status HeroesIntro::PostUpdate()
{
	// Draw everything --------------------------------------

	App->render->Blit(heroes, -203, -10 , NULL);

	// Cambiar los delays para ajustar la escena de disparo 
	
	if (delay >= 1200 && delay <= 1419) App->render->Blit(white1, -200, 396, NULL);
	if (delay >= 1420 && delay <= 1499) App->render->Blit(white2, -200, 396, NULL);
	if (delay >= 1500 && delay <= 1799) App->render->Blit(white3, -200, 396, NULL);
	if (delay >= 1800 && delay <= 2100) App->render->Blit(white4, -200, 396, NULL);

	//App->render->Blit(heroes, -202, -345, NULL);
	
	//App->render->Blit(heroes, -205, -768, NULL);



	return Update_Status::UPDATE_CONTINUE;
}

void HeroesIntro::scrollHeroes(int& speed, int& framesScroll)
{
	if (framesScroll > 0)
	{
		App->render->camera.y += speed;
		framesScroll--;
	}
	else
	{

		speed = 0;
	}
}