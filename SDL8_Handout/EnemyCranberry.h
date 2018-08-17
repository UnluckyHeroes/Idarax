#pragma once
#ifndef __ENEMYCRANBERRY_H__
#define __ENEMYCRANBERRY_H__

#include "Enemy.h"
#include "Animation.h"

struct SDL_Texture;

class EnemyCranberry : public Enemy
{

public:

	EnemyCranberry(int x, int y);
	void Move();

public:
	
	iPoint playerPosition;
	float angle, radians;
	Animation MoveLeft;
	Animation MoveRight;
	Animation Idle;

};

#endif