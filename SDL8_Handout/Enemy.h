#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "p2Point.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleEnemies.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
protected:
	
	Collider* collider = nullptr;
	
public:
	
	uint life = 1;
	float speed = 0;
	uint score = 0;

	SDL_Texture* sprites = nullptr;
	Animation* animation = nullptr;
	fPoint position;

public:

	Enemy(int x, int y);
	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	virtual void Draw(SDL_Texture* sprites);
	virtual void OnCollision(Collider* collider);

};

#endif // __ENEMY_H__