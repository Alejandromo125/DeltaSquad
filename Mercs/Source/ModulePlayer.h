#ifndef __MODULE_PLAYER_H__
#define __MODULE_PLAYER_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	// Constructor
	ModulePlayer();

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	update_status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	update_status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speedX = 1;
	int speedY = 1;
	// The speed in which we move the player camera (pixels per frame)
	int cameraSpeedX = 3;
	int cameraSpeedY = 3;

	// Player sink effect (in water)
	int waterSink = 0; // 0 in ground, 20 in water

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	
	// The pointer to the current player animation
	// It will be switched depending on the player's movement direction
	Animation* currentAnimation = nullptr;

	// A set of animations
	Animation idleUpAnim;
	Animation idledownAnim;
	Animation idleRightAnim;
	Animation idleLeftAnim;

	Animation idleUpRightAnim;
	Animation idleDownRightAnim;
	Animation idleUpLeftAnim;
	Animation idleDownLeftAnim;

	Animation upAnim;
	Animation downAnim;
	Animation leftAnim;
	Animation rightAnim;

	Animation upRightAnim;
	Animation downRightAnim;
	Animation upLeftAnim;
	Animation downLeftAnim;

	Animation deadBackAnim;
	Animation deadFrontAnim;
	Animation deadLeftAnim;
	Animation deadRightAnim;

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// A countdown to when the player gets destroyed. After a while, the game exits
	uint destroyedCountdown = 120;

	// Sound effects indices
	uint shot06 = 0;
	uint dead26 = 0;

};

#endif //!__MODULE_PLAYER_H__