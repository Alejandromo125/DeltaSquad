#pragma once
#ifndef __ENEMY_BOSS_H__
#define __ENEMY_BOSS_H__

#include "Enemy.h"
#include "Path.h"

class Boss : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Boss(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	int counter;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	Animation Shot;
	Animation Idle;

};

#endif // __ENEMY_BROWNSHIP_H__