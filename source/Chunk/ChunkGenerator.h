#ifndef CHUNKGENERATOR_H
#define CHUNKGENERATOR_H

#include "../UtilGL/PerlinNoise.h"
#include "../Chunk/Chunk.h"

class ChunkGenerator {	
	/*************** Variables ***************/
private:
	//Singleton.
	static ChunkGenerator*			_instance;

	//Handles the random generation of terrain.
	PerlinNoise*					_perlin;

	//Height Map is the result of the terrain generation.
	int**							_heightMap;

	//Temperature is map can be used for biomes, etc.
	int**							_temperatureMap;

	/*************** Methods ***************/
public:
	ChunkGenerator();
	~ChunkGenerator();
	
	//Get a pointer to the Chunk Generator from anywhere (lazy but safe).
	static ChunkGenerator*			getInstance();

	//Randomly generates a chunk and builds it.
	void							generateChunk(Chunk* chunk);

	//2D height.
	int								getHeightAt(int x, int z);

	//3D height.
	int								getHeightAt(int x, int y, int z);
};

#endif