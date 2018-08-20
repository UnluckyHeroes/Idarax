#ifndef __ROOM_H__
#define __ROOM_H__

class Room {
public:

	//This flags will tell us if there are rooms around
	bool room_above, room_below, room_right, room_left;

	//Explored flag turns true if the player has been on the room
	bool explored;

	//Completed room turns true if the player kills all the enemies of the room
	bool completed;


private:

	void draw_room() {};
	void spawn_enemies() {};
	
};
#endif _ROOM_H__
#pragma once
