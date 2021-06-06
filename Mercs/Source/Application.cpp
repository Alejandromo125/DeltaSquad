#include "Application.h"

#include "Module.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "ModuleGamepadInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePlayer.h"
#include "TitleScreen.h"
#include "whiteHouseIntro.h"
#include "HeroesIntro.h"
#include "InfoScreen.h"
#include "SceneIntro.h"
#include "SceneLevel1.h"
#include "SceneLevel2.h"
#include "ModuleBreakable.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleCollisions.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFonts.h"
#include "ModuleRender.h"

Application::Application()
{
	// The order in which the modules are added is very important.
	// It will define the order in which Pre/Update/Post will be called
	// Render should always be last, as our last action should be updating the screen

	modules[0] =	window =		new ModuleWindow(true);
	modules[1] =	input =			new ModuleInput(true);
	modules[2] =	gamepadInput =  new ModuleGamepadInput(true);
	modules[3] =	textures =		new ModuleTextures(true);
	modules[4] =	audio =			new ModuleAudio(true);

	modules[5] =	infoScreen =	new InfoScreen(true);
	modules[6] =    titleScreen =   new TitleScreen(false);
	modules[7] =	whiteHouseIntro = new WhiteHouseIntro(false);
	modules[8] =    heroesIntro =   new HeroesIntro(false);
	modules[9] =	sceneIntro =	new SceneIntro(false);
	modules[10] =	sceneLevel_1 =	new SceneLevel1(false);		//Gameplay scene starts disabled
	modules[11] =	sceneLevel_2 =  new SceneLevel2(false);		//Gameplay scene starts disabled
	modules[12] =	breakableParticles = new ModuleBreakable(false);
	modules[13] =	player =		new ModulePlayer(false);	//Player starts disabled
	modules[14] =	particles =		new ModuleParticles(false);
	modules[15] =	enemies =		new ModuleEnemies(false);	//Enemies start disabled

	modules[16] =	collisions =	new ModuleCollisions(true);
	modules[17] =	fade =			new ModuleFadeToBlack(true);
	modules[18] =	fonts =			new ModuleFonts(true);
	modules[19] =	render =		new ModuleRender(true);
}

Application::~Application()
{
	for (int i = 0; i < NUM_MODULES; ++i)
	{
		//Important: when deleting a pointer, set it to nullptr afterwards
		//It allows us for null check in other parts of the code
		delete modules[i];
		modules[i] = nullptr;
	}
}

bool Application::Init()
{
	bool ret = true;

	// All modules (active and disabled) will be initialized
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->Init();

	// Only active modules will be 'started'
	for (int i = 0; i < NUM_MODULES && ret; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

Update_Status Application::Update()
{
	Update_Status ret = Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : Update_Status::UPDATE_CONTINUE;

	for (int i = 0; i < NUM_MODULES && ret == Update_Status::UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : Update_Status::UPDATE_CONTINUE;

	return ret;
}
 
bool Application::CleanUp()
{
	bool ret = true;

	for (int i = NUM_MODULES - 1; i >= 0 && ret; --i)
		ret = modules[i]->IsEnabled() ? modules[i]->CleanUp() : true;

	return ret;
}
