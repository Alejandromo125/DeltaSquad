#ifndef __MODULE_SCENE_H__
#define __MODULE_SCENE_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class ModuleScene : public Module
{
public:
	//Constructor
	ModuleScene();

	//Destructor
	~ModuleScene();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	update_status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	update_status PostUpdate() override;

public:
	
	// The scene sprite sheets loaded into an SDL_Texture
	SDL_Texture* Level1FullMapTexture = nullptr;
	SDL_Texture* bgTexture = nullptr;
	SDL_Texture* Houses1Texture = nullptr;
	SDL_Texture* Houses2Texture = nullptr;
	SDL_Texture* LevelIntroTexture = nullptr;
	SDL_Texture* MovingAndChangingTilesTexture = nullptr;
	
	// The sprite rectangle for the ground
	SDL_Texture* starsTexture = nullptr;
};

#endif