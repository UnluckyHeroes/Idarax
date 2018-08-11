#pragma once
#ifndef ENEMY_RAPIER_H__
#define ENEMY_RAPIER_H__

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
	bool PlayerInTheRoom = false; //WTF? Should be in Enemies general

public:

	float radians;
	float angle;
};




#endif