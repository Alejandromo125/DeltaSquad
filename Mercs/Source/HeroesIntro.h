#ifndef __HEROES_INTRO_H__
#define __HEROES_INTRO_H__

#include "Module.h"
#include "Animation.h"

struct SDL_Texture;

class HeroesIntro : public Module
{
public:
	//Constructor
	HeroesIntro(bool startEnabled);

	//Destructor
	~HeroesIntro();

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
	SDL_Texture* heroes = nullptr;

	SDL_Texture* white1 = nullptr;
	SDL_Texture* white2 = nullptr;
	SDL_Texture* white3 = nullptr;
	SDL_Texture* white4 = nullptr;

	int timer;
	int timerFinal = 400;
	int speed = 0;
	int framesScroll = 0;
	int counter = 0;

	int delay;

	void scrollHeroes(int& speed, int& frames);

};

#endif