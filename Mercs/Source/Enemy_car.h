#pragma once
#ifndef __ENEMY_CAR_H__
#define __ENEMY_CAR_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_car : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_car(int x, int y);

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


};

#endif // __ENEMY_BROWNSHIP_H__