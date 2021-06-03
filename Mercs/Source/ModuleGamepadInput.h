#ifndef __MODULE_GAMEPADINPUT_H__
#define __MODULE_GAMEPADINPUT_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModuleGamepadInput : public Module
{
public:
	// Constructor
	ModuleGamepadInput(bool startEnabled);

	// Destructor
	~ModuleGamepadInput();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Draws gamepad debug info in the screen
	void DebugDrawGamepadInfo();

public:

	// Font score index
	uint score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	// Debugdraw for gamepad data
	bool debugGamepadInfo = false;

	UINT32 keyDownDelay;

};

#endif //!__MODULE_GAMEPADINPUT_H__
