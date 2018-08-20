#include "ModuleFloor.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

ModuleFloor::ModuleFloor() {
	
	//Before we create the map, we fill the matrix with nullptr
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			room_matrix[i][j] = nullptr;
};

ModuleFloor::~ModuleFloor() {};

bool ModuleFloor::Start() {
	
	return true;
};

bool ModuleFloor::CleanUp() {
	
	return true;
};

update_status ModuleFloor::Update() {
	
	return update_status::UPDATE_CONTINUE;
};

void ModuleFloor::Generate_floor() {
	
	//Each floor will have between 8 and 15 rooms
	int roomsNumber;
	srand(time(NULL));
	roomsNumber = (rand() % 8) + 7;

	//First, we create a room in the center of the floor
	room_matrix[3][3] = new Room;

	while (roomsNumber > 0)
	{
		
	}



};

bool ModuleFloor::Adjacent_room(int x, int y){
	
	bool ret = false;

	//If the room is not at the border of the matrix
	if (x>0 && x<4 && y>0 && y<4){
		if (room_matrix[x - 1][y] != nullptr || 
			room_matrix[x + 1][y] != nullptr || 
			room_matrix[x][y - 1] != nullptr || 
			room_matrix[x][y + 1] != nullptr)
			ret = true;
	}

	else if (x==0)

	return ret;
};