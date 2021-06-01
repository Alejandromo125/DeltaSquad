#pragma once
#ifndef __ENEMY_SOLDIER_LEVEL2_H__
#define __ENEMY_SOLDIER_LEVEL2_H__

#include "Enemy.h"
#include "Path.h"

class Enemy_Soldier_Level2 : public Enemy
{
public:
	// Constructor (x y coordinates in the world)
	// Creates animation and movement data and the collider
	Enemy_Soldier_Level2(int x, int y);

	// The enemy is going to follow the different steps in the path
	// Position will be updated depending on the speed defined at each step
	void Update() override;


	int counter;



private:
	// A set of steps that define the position in the screen
	// And an animation for each step
	Path path;

	Animation walkUp_Soldier_Level2;
	Animation walkDown_Soldier_Level2;
	Animation walkLeft_Soldier_Level2;
	Animation walkRight_Soldier_Level2;
	Animation walkUpLeft_Soldier_Level2;
	Animation walkUpRight_Soldier_Level2;
	Animation walkDownLeft_Soldier_Level2;
	Animation walkDownRight_Soldier_Level2;

	Animation shootUp_Soldier_Level2;
	Animation shootDown_Soldier_Level2;
	Animation shootLeft_Soldier_Level2;
	Animation shootRight_Soldier_Level2;
	Animation shootUpLeft_Soldier_Level2;
	Animation shootUpRight_Soldier_Level2;
	Animation shootDownLeft_Soldier_Level2;
	Animation shootDownRight_Soldier_Level2;



};

#endif // __ENEMY_BROWNSHIP_H__