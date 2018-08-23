#include "Application.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModuleRender.h"
#include "EnemyRapier.h"
#include "Animation.h"
#include "ModuleTextures.h"
#include "ModuleEnemies.h"
#include "ModuleInput.h"


struct SDL_Texture;

EnemyRapier::EnemyRapier(int x, int y) :Enemy(x, y) {

	sprites = App->textures->Load("Rickme/Graphics/enemies.png");

	Idle.PushBack({ 5,6,24,24 });
	Idle.PushBack({ 38, 6, 24, 24 });
	Idle.PushBack({ 71, 6, 24, 24 });
	Idle.PushBack({ 104, 6, 24, 24 });
	Idle.PushBack({ 137, 6, 24, 24 });
	Idle.PushBack({ 170, 6, 24, 24 });
	Idle.PushBack({ 203, 6, 24, 24 });
	Idle.PushBack({ 236, 6, 24, 24 });
	Idle.loop = true;
	Idle.speed = 0.2f;

	animation = &Idle;
	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	speed = 1.0f;
	life = 2;
	score = 100;
}


void EnemyRapier::Move() {

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

	//Animation depending on the angle explained here: https://prnt.sc/k5t63x
	/*if (angle <= 45 && angle >= 0) 
		animation = &Right;
	
	if (angle <= 90 && angle >= 45) 
		animation = &Up;

	if (angle <= 135 && angle >= 90)
		animation = &Up;

	if (angle <= 180 && angle >= 135) 
		animation = &Left;

	if (angle <= 225 && angle >= 180) 
		animation = &Left;

	if (angle <= 270 && angle >= 225) 
		animation = &Down;

	if (angle <= 315 && angle >= 270) 
		animation = &Down;

	if (angle <= 360 && angle >= 315) 
		animation = &Right;*/

	//position.x += speed*0.02*(playerPosition.x - position.x); //MOVEMENT
	//position.y += speed*0.02*(playerPosition.y - position.y);
	position.x += speed * -1*(SDL_cos(radians)); //MOVEMENT
	position.y += speed * -1*(SDL_sin(radians));

}