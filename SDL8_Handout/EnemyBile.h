#pragma once
#ifndef __ENEMYBILE_H__
#define __ENEMYBILE_H__

#include "Enemy.h"
#include "Animation.h"

struct SDL_Texture;

class EnemyBile : public Enemy {

public:

	EnemyBile(int x, int y);
	void Move();
	void Shoot();

public:

	iPoint playerPosition;
	float angle, radians;
	Animation MoveRight;
	Animation MoveLeft;
	Animation MoveUp;
	Animation MoveDown;

	bool counter = true;
	int count;
	
};

#endif