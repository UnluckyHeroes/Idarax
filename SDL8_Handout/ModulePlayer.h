#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "p2Point.h"

struct SDL_Texture;
struct Collider;

class ModulePlayer : public Module
{
public:
	ModulePlayer();
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

public:

	SDL_Texture* graphics = nullptr;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation up;
	Animation down;
	Animation right;
	Animation left;
	iPoint position;
	Collider* col;

	int speed;
	bool destroyed = false;

public:

	//Movement Limitation
	bool moveRight = false;
	bool stopRight = false;

	bool moveLeft = false;
	bool stopLeft = false;

	bool moveUp = false;
	bool stopUp = false;

	bool moveDown = false;
	bool stopDown = false;

};

#endif