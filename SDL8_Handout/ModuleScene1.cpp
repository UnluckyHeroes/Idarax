#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleEnemies.h"
#include "ModuleScene1.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleScene1::ModuleScene1()
{}

ModuleScene1::~ModuleScene1()
{}

// Load assets
bool ModuleScene1::Start()
{
	LOG("Loading space scene");
	
	background = App->textures->Load("Rickme/Graphics/Room1/Room1.png");

	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->enemies->Enable();

	// Colliders ---
	
	App->collision->AddCollider({70, 224, 340, 25}, COLLIDER_WALL); //Down Wall
	App->collision->AddCollider({ 70, 19, 340, 25 }, COLLIDER_WALL); //Up Wall
	App->collision->AddCollider({ 408, 43, 25, 185 }, COLLIDER_WALL); //Right Wall
	App->collision->AddCollider({ 46, 43, 25, 185 }, COLLIDER_WALL); //Left Wall


	// Enemies ---
	
	return true;
}

// UnLoad assets
bool ModuleScene1::CleanUp()
{
	LOG("Unloading space scene");

 	App->textures->Unload(background);

	App->enemies->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->player->Disable();

	return true;
}

// Update: draw background
update_status ModuleScene1::Update()
{
	// Move camera forward -----------------------------
	//App->render->camera.x += 1 * SCREEN_SIZE;

	// Draw everything --------------------------------------
	App->render->Blit(background, 0, 0, NULL);
	
	return UPDATE_CONTINUE;
}