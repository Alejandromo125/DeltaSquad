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
	ModulePlayer(bool startEnabled);

	// Destructor
	~ModulePlayer();

	// Called when the module is activated
	// Loads the necessary textures for the player
	bool Start() override;

	// Called at the middle of the application loop
	// Processes new input and handles player movement
	Update_Status Update() override;

	// Called at the end of the application loop
	// Performs the render call of the player sprite
	Update_Status PostUpdate() override;

	// Collision callback, called when the player intersects with another collider
	void OnCollision(Collider* c1, Collider* c2) override;

public:
	// Position of the player in the map
	iPoint position;

	// The speed in which we move the player (pixels per frame)
	int speedX;
	int speedY;

	//Margin of movement
	int horizontalMargin = 45;
	int verticalMargin = 160;

	int EnemyLookingPosition;

	// F3
	bool activateWinCondition;

	// Camera limits
	bool cameraXlimitation;
	bool cameraYlimitation;
	bool bidimensionalCameraLimitation;

	//Collision variables for mechanics
	bool wallCollision;
	bool trenchWallCollision;

	// Player sink effect (in water)
	int waterSink; // 0 in ground, 20 in water

	// The player spritesheet loaded into an SDL_Texture
	SDL_Texture* texture = nullptr;
	SDL_Texture* merc = nullptr;
	SDL_Texture* insertcoin = nullptr;
	SDL_Texture* mercLife = nullptr;

	// Player Life Variable
	int playerLife;
	int immunityTime;

	//Player Direction of Looking variable

	int PlayerLookingPosition;

	// Items variables
	int collectedItemID;
	int collectedMegaBombsNumber;
	
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

	// The player's collider
	Collider* collider = nullptr;

	// A flag to detect when the player has been destroyed
	bool destroyed = false;

	// Sound effects indices
	uint shot06 = 0;
	uint dead26 = 0;

	// Font score index
	uint score = 000;
	int scoreFont = -1;
	char scoreText[10] = { "\0" };

	// Delay and time for some smooth experience
	
	int playerDelay;
	int time;

};

#endif //!__MODULE_PLAYER_H__
