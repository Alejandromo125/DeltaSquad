#include "SceneIntro.h"

#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include <SDL_mixer/include/SDL_mixer.h>

SceneIntro::SceneIntro(bool startEnabled) : Module(startEnabled)
{

}

SceneIntro::~SceneIntro()
{

}

// Load assets
bool SceneIntro::Start()
{
	LOG("Loading background assets");

	bool ret = true;

	Mix_ResumeMusic();

	bgTexture = App->textures->Load("Assets/Art/Sequences/backgroundblack.png");
	mercsTitle = App->textures->Load("Assets/Art/UI/mercsTitle.png");
	mercsTitle2 = App->textures->Load("Assets/Art/UI/title2.png");
	
	App->audio->PlayMusic("Assets/Music/None.ogg", 1.0f);

	App->render->camera.x = 0;
	App->render->camera.y = 0;

	App->player->cameraXlimitation = true;
	App->player->cameraYlimitation = true;

	return ret;
}

Update_Status SceneIntro::Update()
{

	if (App->input->keys[SDL_SCANCODE_SPACE] == Key_State::KEY_DOWN)
	{
		App->audio->PlayMusic("Assets/Music/Credit.ogg", 1.0f);
		App->fade->FadeToBlack(this, (Module*)App->sceneLevel_1, 90);
	}

	return Update_Status::UPDATE_CONTINUE;
}

// Update: draw background
Update_Status SceneIntro::PostUpdate()
{
	// Draw everything --------------------------------------
	App->render->Blit(bgTexture, 0, 0, NULL);
	App->render->Blit(mercsTitle, 40, 60, NULL);
	App->render->Blit(mercsTitle2, 23, 120, NULL);

	return Update_Status::UPDATE_CONTINUE;
}
