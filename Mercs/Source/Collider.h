#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "SDL/include/SDL_Rect.h"

#define MAX_LISTENERS 5

class Module;

struct Collider
{
	enum Type
	{
		NONE = -1,
		WALL,
		PLAYER,
		ENEMY,
		PLAYER_SHOT,
		ENEMY_SHOT,
		ENEMY_BOMB,
		BOSS,
		WATER,
		BOSS_ATTACK,
		BREAKABLE_OBJECT,
		HORIZONTAL_CAMERA_BOUND,
		VERTICAL_CAMERA_BOUND,
		BIDIMENSIONAL_CAMERA_BOUND,
		EVENT_TRIGGER,
		TRENCH_WALL,
		DOUBLE_SHOT_WEAPON_ID01,
		GREEN_SHOT_WEAPON_ID02,
		HEALING_FOOD_ID03,
		EVENT_TRIGGER_BOSS_ZONE,
		TOWER_ENEMY,
		NULL_COLLIDER,
		MULTI_USE,

		MAX
	};

	//Methods
	Collider(SDL_Rect rectangle, Type type, Module* listener = nullptr);

	void SetPos(int x, int y);

	bool Intersects(const SDL_Rect& r) const;

	void AddListener(Module* listener);

	//Variables
	SDL_Rect rect;
	bool pendingToDelete = false;
	Type type;
	Module* listeners[MAX_LISTENERS] = { nullptr };

};


#endif // !__COLLIDER_H__

