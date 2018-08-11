#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer()
{
	// idle animation (just the player)
	idle.PushBack({ 0, 0, 26, 38 });

	// move upwards
	up.PushBack({ 30, 0, 26, 38 });
	up.loop = false;
	//up.speed = 0.1f;

	// Move down
	down.PushBack({ 0, 0, 26, 38 });
	down.loop = false;
	//down.speed = 0.1f;

	//Move Left
	left.PushBack({ 90, 0, 28, 38 });
	left.loop = false;

	//Move Right
	right.PushBack({ 60, 0, 28, 38 });
	right.loop = false;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("rtype/Idara.png");

	destroyed = false;
	position.x = 150;
	position.y = 120;

	current_animation = &idle;

	col = App->collision->AddCollider({position.x, position.y, 26, 38}, COLLIDER_PLAYER, this);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);
	if (col != nullptr)
		col->to_delete = true;

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	//position.x += 1; // Automatic movement

	int speed = 1;

	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT && (position.x - 1) > 70)
		position.x -= speed;

	if(App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && (position.x + 28) < 408)
		position.x += speed;

	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT && (position.y + 38) < 224)
		position.y += speed;

	if(App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT && (position.y - 5) > 39)
		position.y -= speed;
  
	//_______________________________________________________

	/*if(App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
	{
		App->particles->AddParticle(App->particles->laser, position.x + 20, position.y, COLLIDER_PLAYER_SHOT);
	}*/

	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_DOWN) {

		if (current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}

		App->particles->laser.speed.x = 0;
		App->particles->laser.speed.y = -5;
		App->particles->AddParticle(App->particles->laser, position.x, position.y - 8, COLLIDER_PLAYER_SHOT);
		
	}
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_DOWN) {

		if (current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
		}

		App->particles->laser.speed.x = 0;
		App->particles->laser.speed.y = +5;
		App->particles->AddParticle(App->particles->laser, position.x + 12, position.y + 20, COLLIDER_PLAYER_SHOT);
		
	}
	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_DOWN) {

		if (current_animation != &left)
		{
			left.Reset();
			current_animation = &left;
		}

		App->particles->laser.speed.x = -5;
		App->particles->laser.speed.y = 0;
		App->particles->AddParticle(App->particles->laser, position.x - 12, position.y + 15, COLLIDER_PLAYER_SHOT);
	}

	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_DOWN) {

		if (current_animation != &right)
		{
			right.Reset();
			current_animation = &right;
		}

		App->particles->laser.speed.x = +5;
		App->particles->laser.speed.y = 0;
		App->particles->AddParticle(App->particles->laser, position.x + 23, position.y + 15, COLLIDER_PLAYER_SHOT);
	}

	//__________________________________________________


	col->SetPos(position.x, position.y);

	// Draw everything
	if(destroyed == false)
		App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));

	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{

	if(c1 == col && destroyed == false && App->fade->IsFading() == false)
	{
	
		App->fade->FadeToBlack((Module*)App->scene1, (Module*)App->scene_intro);

		App->particles->AddParticle(App->particles->explosion, position.x, position.y, COLLIDER_NONE, 150);
		App->particles->AddParticle(App->particles->explosion, position.x + 8, position.y + 11, COLLIDER_NONE, 220);
		App->particles->AddParticle(App->particles->explosion, position.x - 7, position.y + 12, COLLIDER_NONE, 670);
		App->particles->AddParticle(App->particles->explosion, position.x + 5, position.y - 5, COLLIDER_NONE, 480);
		App->particles->AddParticle(App->particles->explosion, position.x - 4, position.y - 4, COLLIDER_NONE, 350);

		destroyed = true;
	}
}