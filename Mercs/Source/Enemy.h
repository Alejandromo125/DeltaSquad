#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
public:
	// Constructor
	// Saves the spawn position for later movement calculations
	Enemy(int x, int y);

	// Destructor
	virtual ~Enemy();

	// Returns the enemy's collider
	const Collider* GetCollider() const;

	// Called from inhering enemies' Udpate
	// Updates animation and collider position
	virtual void Update();

	// Called from ModuleEnemies' Update
	virtual void Draw();

	// Collision response
	virtual void OnCollision(Collider* c2);

	//Collision for the boss
	//virtual void OnCollisionOther(Collider*c1,Collider* c2);

	// Sets flag for deletion and for the collider aswell
	virtual void SetToDelete();

public:
	// The current position in the world
	iPoint  position;

	// The enemy's texture
	SDL_Texture* texture = nullptr;

	// Sound fx when destroyed
	int destroyedFx = 0;

	//speedEnemy
	int EnemySpeedX;
	int EnemySpeedY;
	//EnemyHits
	int EnemyHP;
	//BossHits
	
	
	//Test for hp implementing

	//wall Collision
	bool EnemywallCollision;

	// A flag for the enemy removal. Important! We do not delete objects instantly
	bool pendingToDelete = false;

	// Enemy sink effect (in water)
	int EnemywaterSink = 0; // 0 in ground, 20 in water

protected:
	// A ptr to the current animation
	Animation* currentAnim = nullptr;

	

	// The enemy's collider
	Collider* collider = nullptr;

	// Original spawn position. Stored for movement calculations
	iPoint spawnPos;
};

#endif // __ENEMY_H__