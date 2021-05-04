#ifndef __ENEMY_SOLDIER_NONMOVABLE_H__
#define __ENEMY_SOLDIER_NONMOVABLE_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Soldier2 : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Soldier2(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;


	int counterEnemy2;



private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	

	Animation Enemy2shootUp;
	Animation Enemy2shootDown;
	Animation Enemy2shootLeft;
	Animation Enemy2shootRight;
	Animation Enemy2shootUpLeft;
	Animation Enemy2shootUpRight;
	Animation Enemy2shootDownLeft;
	Animation Enemy2shootDownRight;


	
};

#endif // __ENEMY_BROWNSHIP_H__
