#include "EnemyBile.h"
#include "Application.h"
#include "Animation.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleEnemies.h"
#include <math.h>
#include "SDL/include/SDL_timer.h"


EnemyBile::EnemyBile(int x, int y) : Enemy (x,y) {

	sprites = App->textures->Load("Rickme/Graphics/enemies.png");
	
	MoveRight.PushBack({ 4, 39, 21, 22 });
	MoveRight.speed = 0.2f;
	MoveRight.loop = false;

	MoveLeft.PushBack({ 4, 72, 22, 22 });
	MoveLeft.speed = 0.2f;
	MoveLeft.loop = false;

	MoveUp.PushBack({ 134, 74, 26, 20 });
	MoveUp.speed = 0.2f;
	MoveUp.loop = false;

	MoveDown.PushBack({ 134, 39, 26, 20 });
	MoveDown.speed = 0.2f;
	MoveDown.loop = false;

	collider = App->collision->AddCollider({0, 0, 22, 22}, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	animation = &MoveLeft;
	speed = 0.3f;
	life = 5;
	score = 150;
}

void EnemyBile::Move() {

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

	if (abs((int)playerPosition.x - (int)position.x) >= 10 || abs((int)playerPosition.y - (int)position.y) >= 10) {

		if (counter) {

			count = SDL_GetTicks();
			Shoot();
			counter = false;
		}

		if (SDL_GetTicks() == count + 2000) {

			count = 0;
			counter = true;
		}
		

	}
	//if ( (position.x - 1) > 70 || (position.x + 28) < 408 || (position.y + 38) < 224 || (position.y - 5) > 39){

	//	if ( (position.x + 28 <= playerPosition.x - 5) || (position.x >= playerPosition.x + 30) ||
	//	(position.y + 32 <= playerPosition.y - 5) || (position.y >= playerPosition.y + 40) ) {

	//		animation = &MoveLeft;
	//		//speed = 1.0f;
	//		position.x += speed * 1 * (SDL_cos(radians)); //MOVEMENT
	//		position.y += speed * 1 * (SDL_sin(radians));
	//	}
	//}

	if ((position.x + 22 <= playerPosition.x - 5) && position.x >= 70) {
		//position.x -= speed;
		position.x += speed * 1 * (SDL_cos(radians));
		position.y += speed * 1 * (SDL_sin(radians));
		animation = &MoveLeft;
	}
	
	else if ((position.x >= playerPosition.x + 30) && position.x + 22 <= 408) {
		//position.x += speed;
		position.x += speed * 1 * (SDL_cos(radians));
		position.y += speed * 1 * (SDL_sin(radians));
		animation = &MoveRight;
	}

	else if ((position.y >= playerPosition.y + 40) && position.y + 22 <= 224) {
		//position.y += speed;
		position.x += speed * 1 * (SDL_cos(radians));
		position.y += speed * 1 * (SDL_sin(radians));
		animation = &MoveDown;
	}

	else if ((position.y + 22 <= playerPosition.y - 5) && position.y - 5 > 39) {
		//position.y -= speed;
		position.x += speed * 1 * (SDL_cos(radians));
		position.y += speed * 1 * (SDL_sin(radians));
		animation = &MoveUp;
	}
}


void EnemyBile::Shoot() {

		App->particles->EnemyShoot.position.x += speed * -1 * (SDL_cos(radians));
		App->particles->EnemyShoot.position.y += speed * -1 * (SDL_sin(radians));
		App->particles->AddParticle(App->particles->EnemyShoot, position.x + 20, position.y + 10, COLLIDER_ENEMY_SHOT);

}



