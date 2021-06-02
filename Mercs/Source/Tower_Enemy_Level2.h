#pragma once
#ifndef __TOWER_ENEMY_H__
#define __TOWER_ENEMY_H__

#include "Enemy.h"
#include "Path.h"

class TowerEnemy : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	TowerEnemy(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;

	int counter;

private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	

	Animation ShootDown;
	Animation ShootLeft;
	Animation ShootRight;
	Animation ShootDownLeft;
	Animation ShootDownRight;

};

#endif // __ENEMY_BROWNSHIP_H__