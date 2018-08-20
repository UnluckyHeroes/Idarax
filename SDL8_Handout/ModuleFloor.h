#ifndef __MODULEFLOOR_H__
#define __MODULEFLOOR_H__

#include "Module.h"
#include "Room.h"

class ModuleFloor :public Module {

public:
	/*5x5 matrix that will contain the rooms
	*/
	Room* room_matrix[5][5];

	ModuleFloor();
	~ModuleFloor();

	bool Start();
	update_status Update();
	bool CleanUp();

private:
	//This function will create the floor
	void Generate_floor();
	
	/*It returns a value that will tell us if  a room of the matrix
	has an other room adjacent to it*/
	bool Adjacent_room(int x, int y);
};
#endif __MODULEFLOOR_H__
#pragma once
