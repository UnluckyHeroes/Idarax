#pragma once
#ifndef ENEMYRAPIER_H__
#define ENEMYRAPIER_H__

#include "Enemy.h"
#include "Animation.h"

struct SDL_Texture;

class EnemyRapier : public Enemy {

public:

	EnemyRapier(int x, int y);
	void Move();

public:

	Animation Idle;
	/*Animation Up;
	Animation Down;
	Animation Right;
	Animation Left;*/

public:

	iPoint playerPosition;
	float radians;
	float angle;
};




#endif