#ifndef __WHITE_HOUSE_INTRO_H__
#define __WHITE_HOUSE_INTRO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class WhiteHouseIntro : public Module
{
public:
	//Constructor
	WhiteHouseIntro(bool startEnabled);

	//Destructor
	~WhiteHouseIntro();

	// Called when the module is activated
	// Loads the necessary textures for the map background
	bool Start() override;

	// Called at the middle of the application loop
	// Updates the scene's background animations
	Update_Status Update() override;

	// Called at the end of the application loop.
	// Performs the render call of all the parts of the scene's background
	Update_Status PostUpdate() override;

public:
	// The scene sprite sheet loaded into an SDL_Texture
	SDL_Texture* whiteHouse = nullptr;
	SDL_Texture* houseTop = nullptr;
	SDL_Texture* helicopter = nullptr;

	SDL_Texture* messagePart1 = nullptr;
	SDL_Texture* messagePart2 = nullptr;
	SDL_Texture* messagePart3 = nullptr;
	SDL_Texture* messagePart4 = nullptr;
	SDL_Texture* messagePart5 = nullptr;

	int delay;
	
};

#endif