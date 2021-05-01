#include "ModuleCollisions.h"

#include "Application.h"

#include "ModuleRender.h"
#include "ModuleInput.h"
#include "SDL/include/SDL_Scancode.h"

ModuleCollisions::ModuleCollisions(bool startEnabled) : Module(startEnabled)
{
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[Collider::Type::WALL][Collider::Type::WALL] = false;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WALL][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::WALL][Collider::Type::WATER] = false;
	matrix[Collider::Type::WALL][Collider::Type::ENEMY_BOMB] = true;
	matrix[Collider::Type::WALL][Collider::Type::BOSS_ATTACK] = false;
	matrix[Collider::Type::WALL][Collider::Type::BREAKABLE_OBJECT] = false;
	matrix[Collider::Type::WALL][Collider::Type::HORIZONTAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::WALL][Collider::Type::VERTICAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::WALL][Collider::Type::EVENT_TRIGGER] = false;
	matrix[Collider::Type::WALL][Collider::Type::BOSS] = false;

	matrix[Collider::Type::PLAYER][Collider::Type::WALL] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::WATER] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::ENEMY_BOMB] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BOSS_ATTACK] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BREAKABLE_OBJECT] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::HORIZONTAL_CAMERA_BOUND] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::VERTICAL_CAMERA_BOUND] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::EVENT_TRIGGER] = true;
	matrix[Collider::Type::PLAYER][Collider::Type::BOSS] = true;

	matrix[Collider::Type::ENEMY][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::WATER] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::ENEMY_BOMB] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::BOSS_ATTACK] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::BREAKABLE_OBJECT] = true;
	matrix[Collider::Type::ENEMY][Collider::Type::HORIZONTAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::VERTICAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::EVENT_TRIGGER] = false;
	matrix[Collider::Type::ENEMY][Collider::Type::BOSS] = false;

	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::WATER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::ENEMY_BOMB] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BOSS_ATTACK] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BREAKABLE_OBJECT] = true;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::HORIZONTAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::VERTICAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::EVENT_TRIGGER] = false;
	matrix[Collider::Type::PLAYER_SHOT][Collider::Type::BOSS] = true;

	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WALL] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::WATER] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::ENEMY_BOMB] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::BOSS_ATTACK] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::BREAKABLE_OBJECT] = true;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::HORIZONTAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::VERTICAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::EVENT_TRIGGER] = false;
	matrix[Collider::Type::ENEMY_SHOT][Collider::Type::BOSS] = false;

	matrix[Collider::Type::BOSS][Collider::Type::WALL] = false;
	matrix[Collider::Type::BOSS][Collider::Type::PLAYER] = false;
	matrix[Collider::Type::BOSS][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::BOSS][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::BOSS][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::BOSS][Collider::Type::WATER] = false;
	matrix[Collider::Type::BOSS][Collider::Type::ENEMY_BOMB] = false;
	matrix[Collider::Type::BOSS][Collider::Type::BOSS_ATTACK] = false;
	matrix[Collider::Type::BOSS][Collider::Type::BREAKABLE_OBJECT] = false;
	matrix[Collider::Type::BOSS][Collider::Type::HORIZONTAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::BOSS][Collider::Type::VERTICAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::BOSS][Collider::Type::EVENT_TRIGGER] = false;
	matrix[Collider::Type::BOSS][Collider::Type::BOSS] = false;

	matrix[Collider::Type::WATER][Collider::Type::WALL] = false;
	matrix[Collider::Type::WATER][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::WATER][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::WATER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::WATER][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::WATER][Collider::Type::WATER] = false;
	matrix[Collider::Type::WATER][Collider::Type::ENEMY_BOMB] = false;
	matrix[Collider::Type::WATER][Collider::Type::BOSS_ATTACK] = false;
	matrix[Collider::Type::WATER][Collider::Type::BREAKABLE_OBJECT] = false;
	matrix[Collider::Type::WATER][Collider::Type::HORIZONTAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::WATER][Collider::Type::VERTICAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::WATER][Collider::Type::EVENT_TRIGGER] = false;
	matrix[Collider::Type::WATER][Collider::Type::BOSS] = false;
	
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::WALL] = false;
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::WATER] = false;
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::ENEMY_BOMB] = false;
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::BOSS_ATTACK] = false;
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::BREAKABLE_OBJECT] = false;
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::HORIZONTAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::VERTICAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::EVENT_TRIGGER] = false;
	matrix[Collider::Type::BOSS_ATTACK][Collider::Type::BOSS] = false;

	matrix[Collider::Type::BREAKABLE_OBJECT][Collider::Type::WALL] = false;
	matrix[Collider::Type::BREAKABLE_OBJECT][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::BREAKABLE_OBJECT][Collider::Type::ENEMY] = true;
	matrix[Collider::Type::BREAKABLE_OBJECT][Collider::Type::PLAYER_SHOT] = true;
	matrix[Collider::Type::BREAKABLE_OBJECT][Collider::Type::ENEMY_SHOT] = true;
	matrix[Collider::Type::BREAKABLE_OBJECT][Collider::Type::WATER] = false;
	matrix[Collider::Type::BREAKABLE_OBJECT][Collider::Type::ENEMY_BOMB] = false;
	matrix[Collider::Type::BREAKABLE_OBJECT][Collider::Type::BOSS_ATTACK] = false;
	matrix[Collider::Type::BREAKABLE_OBJECT][Collider::Type::BREAKABLE_OBJECT] = false;
	matrix[Collider::Type::BREAKABLE_OBJECT][Collider::Type::HORIZONTAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::BREAKABLE_OBJECT][Collider::Type::VERTICAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::BREAKABLE_OBJECT][Collider::Type::EVENT_TRIGGER] = false;
	matrix[Collider::Type::BREAKABLE_OBJECT][Collider::Type::BOSS] = false;

	matrix[Collider::Type::HORIZONTAL_CAMERA_BOUND][Collider::Type::WALL] = false;
	matrix[Collider::Type::HORIZONTAL_CAMERA_BOUND][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::HORIZONTAL_CAMERA_BOUND][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::HORIZONTAL_CAMERA_BOUND][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::HORIZONTAL_CAMERA_BOUND][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::HORIZONTAL_CAMERA_BOUND][Collider::Type::WATER] = false;
	matrix[Collider::Type::HORIZONTAL_CAMERA_BOUND][Collider::Type::ENEMY_BOMB] = false;
	matrix[Collider::Type::HORIZONTAL_CAMERA_BOUND][Collider::Type::BOSS_ATTACK] = false;
	matrix[Collider::Type::HORIZONTAL_CAMERA_BOUND][Collider::Type::BREAKABLE_OBJECT] = false;
	matrix[Collider::Type::HORIZONTAL_CAMERA_BOUND][Collider::Type::HORIZONTAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::HORIZONTAL_CAMERA_BOUND][Collider::Type::VERTICAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::HORIZONTAL_CAMERA_BOUND][Collider::Type::EVENT_TRIGGER] = false;
	matrix[Collider::Type::HORIZONTAL_CAMERA_BOUND][Collider::Type::BOSS] = false;

	matrix[Collider::Type::VERTICAL_CAMERA_BOUND][Collider::Type::WALL] = false;
	matrix[Collider::Type::VERTICAL_CAMERA_BOUND][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::VERTICAL_CAMERA_BOUND][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::VERTICAL_CAMERA_BOUND][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::VERTICAL_CAMERA_BOUND][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::VERTICAL_CAMERA_BOUND][Collider::Type::WATER] = false;
	matrix[Collider::Type::VERTICAL_CAMERA_BOUND][Collider::Type::ENEMY_BOMB] = false;
	matrix[Collider::Type::VERTICAL_CAMERA_BOUND][Collider::Type::BOSS_ATTACK] = false;
	matrix[Collider::Type::VERTICAL_CAMERA_BOUND][Collider::Type::BREAKABLE_OBJECT] = false;
	matrix[Collider::Type::VERTICAL_CAMERA_BOUND][Collider::Type::HORIZONTAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::VERTICAL_CAMERA_BOUND][Collider::Type::VERTICAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::VERTICAL_CAMERA_BOUND][Collider::Type::EVENT_TRIGGER] = false;
	matrix[Collider::Type::VERTICAL_CAMERA_BOUND][Collider::Type::BOSS] = false;

	matrix[Collider::Type::EVENT_TRIGGER][Collider::Type::WALL] = false;
	matrix[Collider::Type::EVENT_TRIGGER][Collider::Type::PLAYER] = true;
	matrix[Collider::Type::EVENT_TRIGGER][Collider::Type::ENEMY] = false;
	matrix[Collider::Type::EVENT_TRIGGER][Collider::Type::PLAYER_SHOT] = false;
	matrix[Collider::Type::EVENT_TRIGGER][Collider::Type::ENEMY_SHOT] = false;
	matrix[Collider::Type::EVENT_TRIGGER][Collider::Type::WATER] = false;
	matrix[Collider::Type::EVENT_TRIGGER][Collider::Type::ENEMY_BOMB] = false;
	matrix[Collider::Type::EVENT_TRIGGER][Collider::Type::BOSS_ATTACK] = false;
	matrix[Collider::Type::EVENT_TRIGGER][Collider::Type::BREAKABLE_OBJECT] = false;
	matrix[Collider::Type::EVENT_TRIGGER][Collider::Type::HORIZONTAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::EVENT_TRIGGER][Collider::Type::VERTICAL_CAMERA_BOUND] = false;
	matrix[Collider::Type::EVENT_TRIGGER][Collider::Type::EVENT_TRIGGER] = false;
	matrix[Collider::Type::EVENT_TRIGGER][Collider::Type::BOSS] = false;
}

// Destructor
ModuleCollisions::~ModuleCollisions()
{

}

Update_Status ModuleCollisions::PreUpdate()
{
	if (activateGodMode == false)
	{
		// Remove all colliders scheduled for deletion
		for (uint i = 0; i < MAX_COLLIDERS; ++i)
		{
			if (colliders[i] != nullptr && colliders[i]->pendingToDelete == true)
			{
				delete colliders[i];
				colliders[i] = nullptr;
			}
		}

		Collider* c1;
		Collider* c2;

		for (uint i = 0; i < MAX_COLLIDERS; ++i)
		{
			// skip empty colliders
			if (colliders[i] == nullptr)
				continue;

			c1 = colliders[i];

			// avoid checking collisions already checked
			for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
			{
				// skip empty colliders
				if (colliders[k] == nullptr)
					continue;

				c2 = colliders[k];

				if (matrix[c1->type][c2->type] && c1->Intersects(c2->rect))
				{
					for (uint i = 0; i < MAX_LISTENERS; ++i)
						if (c1->listeners[i] != nullptr) c1->listeners[i]->OnCollision(c1, c2);

					for (uint i = 0; i < MAX_LISTENERS; ++i)
						if (c2->listeners[i] != nullptr) c2->listeners[i]->OnCollision(c2, c1);
				}
			}
		}
	}
	

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::Update()
{

	if (App->input->keys[SDL_SCANCODE_F1] == KEY_DOWN)
		debug = !debug;

	if (App->input->keys[SDL_SCANCODE_F2] == KEY_DOWN)
		activateGodMode = !activateGodMode;

	return Update_Status::UPDATE_CONTINUE;
}

Update_Status ModuleCollisions::PostUpdate()
{
	if (debug)
		DebugDraw();

	return Update_Status::UPDATE_CONTINUE;
}

void ModuleCollisions::DebugDraw()
{
	Uint8 alpha = 80;
	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
			continue;
		if (activateGodMode == false)
		{
			switch (colliders[i]->type)
			{
			case Collider::Type::NONE: // white
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::WALL: // blue
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
				break;
			case Collider::Type::PLAYER: // green
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
				break;
			case Collider::Type::ENEMY: // red
				App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
				break;
			case Collider::Type::PLAYER_SHOT: // yellow
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
				break;
			case Collider::Type::ENEMY_SHOT: // magenta
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
				break;
			}
		}
		else if (activateGodMode == true)
		{
			switch (colliders[i]->type)
			{
			case Collider::Type::NONE: // white
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::WALL: // blue
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::PLAYER: // green
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::ENEMY: // red
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::PLAYER_SHOT: // yellow
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			case Collider::Type::ENEMY_SHOT: // magenta
				App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
				break;
			}
		}

	}
}

// Called before quitting
bool ModuleCollisions::CleanUp()
{
	LOG("Freeing all colliders");

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* ModuleCollisions::AddCollider(SDL_Rect rect, Collider::Type type, Module* listener)
{
	Collider* ret = nullptr;

	for(uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if(colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, listener);
			break;
		}
	}

	return ret;
}

void ModuleCollisions::RemoveCollider(Collider* collider)
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == collider)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}
}