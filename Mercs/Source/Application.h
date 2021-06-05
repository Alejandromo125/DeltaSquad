#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 19

class Module;
class ModuleWindow;
class ModuleInput;
class ModuleGamepadInput;
class ModuleTextures;
class ModuleAudio;
class ModulePlayer;
class InfoScreen;
class TitleScreen;
class WhiteHouseIntro;
class SceneIntro;
class SceneLevel1;
class SceneLevel2;
class ModuleBreakable;
class ModuleParticles;
class ModuleCollisions;
class ModuleEnemies;
class ModuleFadeToBlack;
class ModuleFonts;
class ModuleRender;

class Application
{

public:

	//Constructor. Creates all necessary modules for the application
	Application();

	//Destructor. Removes all module objects
	~Application();

	//Initializes all modules
	bool Init();

	//Updates all modules (PreUpdate, Update and PostUpdate)
	Update_Status Update();

	//Releases all the application data
	bool CleanUp();

public:
	// An array to store all modules
	Module* modules[NUM_MODULES];

	// All the modules stored individually
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleGamepadInput* gamepadInput = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleAudio* audio = nullptr;

	ModulePlayer* player = nullptr;

	InfoScreen* infoScreen = nullptr;
	TitleScreen* titleScreen = nullptr;
	WhiteHouseIntro* whiteHouseIntro = nullptr;
	SceneIntro* sceneIntro = nullptr;
	SceneLevel1* sceneLevel_1 = nullptr;
	SceneLevel2* sceneLevel_2 = nullptr;
	ModuleBreakable* breakableParticles = nullptr;

	ModuleEnemies* enemies = nullptr;
	ModuleParticles* particles = nullptr;

	ModuleCollisions* collisions = nullptr;
	ModuleFadeToBlack* fade = nullptr;
	ModuleFonts* fonts = nullptr;

	ModuleRender* render = nullptr;
};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__
