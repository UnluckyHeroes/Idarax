#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"

#define SPAWN_MARGIN 50

//Include Enemies
#include "EnemyRapier.h"
#include "EnemyCranberry.h"


//				 ---------------	IMPORTANT	-------------------------
// We must add something to the switch in the EnemySpawn function each time we add an enemy



ModuleEnemies::ModuleEnemies()
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	sprites = App->textures->Load("Rickme/Graphics/enemies.png");
	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if(queue[i].x * SCREEN_SIZE < App->render->camera.x + (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	}

	return UPDATE_CONTINUE;
}


update_status ModuleEnemies::Update()
{
	for(uint i = 0; i < MAX_ENEMIES; ++i)
		if(enemies[i] != nullptr) enemies[i]->Move();

	for(uint i = 0; i < MAX_ENEMIES; ++i)
		if(enemies[i] != nullptr) enemies[i]->Draw(sprites);

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			if(enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");

	App->textures->Unload(sprites);

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}

		queue[i].type = ENEMY_TYPES::NO_TYPE;
		queue[i].x = 0;
		queue[i].y = 0;
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type, int x, int y)
{
	bool ret = false;

	for(uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if(queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for(; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if(i != MAX_ENEMIES)
	{
		switch(info.type)
		{
							/*In this switch we must add the case for each enemy spawning, for example:
	
									case ENEMY_TYPES::REDBIRD:
									enemies[i] = new Enemy_RedBird(info.x,info.y);
									break;

							*/
		case ENEMY_TYPES::ENEMY_RAPIER:
			enemies[i] = new EnemyRapier(info.x, info.y);
			break;
		case ENEMY_TYPES::ENEMY_CRANBERRY:
			enemies[i] = new EnemyCranberry(info.x, info.y);
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2) {

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1) {

			if (enemies[i]->life > 1) {
				enemies[i]->life--;
				//Mix_PlayChannel(-1, enemyHit, 0);
				break;
			}
			else {

				enemies[i]->OnCollision(c2);
				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
		}
	}
}



	
