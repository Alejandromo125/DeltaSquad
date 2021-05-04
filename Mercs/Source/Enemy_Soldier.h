#ifndef __ENEMY_SOLDIER_H__
#define __ENEMY_SOLDIER_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Soldier : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Soldier(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	
	int counter;
	
	

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	Animation walkUp;
	Animation walkDown;
	Animation walkLeft;
	Animation walkRight;
	Animation walkUpLeft;
	Animation walkUpRight;
	Animation walkDownLeft;
	Animation walkDownRight;

	Animation shootUp;
	Animation shootDown;
	Animation shootLeft;
	Animation shootRight;
	Animation shootUpLeft;
	Animation shootUpRight;
	Animation shootDownLeft;
	Animation shootDownRight;


	
};

#endif // __ENEMY_BROWNSHIP_H__