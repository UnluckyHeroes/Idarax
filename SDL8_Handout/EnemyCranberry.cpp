#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "EnemyCranberry.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleEnemies.h"


EnemyCranberry::EnemyCranberry(int x, int y) : Enemy (x,y) {

	sprites = App->textures->Load("Rickme/Graphics/enemies.png");

	MoveLeft.PushBack({ 72, 105, 28, 32 });
	MoveLeft.PushBack({ 38, 108, 30, 29 });
	MoveLeft.PushBack({ 6, 108, 30, 29 });
	MoveLeft.loop = true;
	MoveLeft.speed = 0.2f;

	Idle.PushBack({ 72, 105, 28, 32 });
	Idle.loop = false;
	Idle.speed = 0.2f;

	MoveRight.PushBack({ 106, 105, 28, 32 });
	MoveRight.PushBack({ 137, 108, 30, 29 });
	MoveRight.PushBack({ 170, 108, 30, 29 });
	MoveRight.loop = true;
	MoveRight.speed = 0.2f;

	collider = App->collision->AddCollider({ 106, 105, 28, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	animation = &Idle;
	life = 0;
	score = 100;
	speed = 1.0f;

}


void EnemyCranberry::Move()
{

	//animation = &Idle;

	if (App->player->IsEnabled()) {
		playerPosition = App->player->position;
		radians = atan2((position.y - playerPosition.y), (position.x - playerPosition.x));
	}
	else
		LOG("Player is dead or is not in the room, enemies don't move");


	angle = radians * (180 / PI);
	if (radians < 0) {
		angle += 360;
	}

	if ( (position.x + 28 <= playerPosition.x - 5) || (position.x >= playerPosition.x + 30) ||
		(position.y + 32 <= playerPosition.y - 5) || (position.y >= playerPosition.y + 40) ){

		animation = &MoveLeft;
		//speed = 1.0f;
		position.x += speed * -1 * (SDL_cos(radians)); //MOVEMENT
		position.y += speed * -1 * (SDL_sin(radians));
	}
}


