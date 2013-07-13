#ifndef WORLD_H
#define WORLD_H

#include "../Chunk/ChunkManager.h"
#include "../PlayerFPS/Player.h"

class World {
	/*************** Variables ***************/
private:
	//The name of this world.
	char							_name[100];

public:
	//Handles all the chunks in the world, what needs to be loaded/generated/rendered/etc.
	ChunkManager*					_chunkManager;

	//The player is in the house.
	Player*							_player;

	/*************** Methods ***************/
public:
	World();
	World(char* name);
	~World();
	
	//Generates the world given the program.
	void							generateWorld(Program* program);

	//Updates based on the time that passed since the last tick.
	void							update(float secondsElapsed);

	//Renders everything.
	void							render();
};

#endif