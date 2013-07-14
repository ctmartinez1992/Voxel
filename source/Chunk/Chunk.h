#ifndef CHUNK_H
#define CHUNK_H

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Block/Block.h"
#include "../../OGLRender/Program.h"
#include "../IO/InputHandler.h"

#include <algorithm>
#include <chrono>
#include <vector>

class ChunkManager;

class Chunk {
	/*************** Variables ***************/
private:
	//The vertexes used to render the chunk.
	GLuint						_vao;
	GLuint						_vbo;

	//The vertexes used to render the water.
	GLuint						_wvao;
	GLuint						_wvbo;

	//Some size metrics, check the constructor for explanation.
	int							_chunkTotalSize;
	int							_renderBlockSize;

	int							_renderSize;
	int							_renderWaterSize;

	int							_vboQuadSize;
	int							_vboBlockSize;
	int							_vboSize;

	//Position (Upper Left Nearest Corner).
	glm::vec3					_position;

	//Flag that checks if the chunk was loaded or not.
	bool						_loaded;

	//Flag that checks if the chunk was generated or not.
	bool						_generated;

	ChunkManager*				_chunkManager;
	
	std::chrono::steady_clock::time_point start;
	std::chrono::steady_clock::time_point end;
	
public:
	//The size of a chunk.
	static const int			CHUNK_SIZE = 16;
	
	//Max units of water moved out of one block to another, per timestep.
	static const float			MaxSpeed;
	
	//The normal, un-pressurized mass of a full water cell.
	static const float			MaxMass;
	
	//Ignore cells that are almost dry
	static const float			MinMass;

	//How much excess water a cell can store, compared to the cell above it.
	static const float			MaxCompress;

	//Smooth the Flow.
	static const float			MinFlow;

	//CHUNK_SIZE per CHUNK_SIZE per CHUNK_SIZE of Blocks
	Block***					_blocks;
	
	//Quick access to water in the chunk.
	std::vector<Block*>			_waterList;

	//Handles the OpenGL stuff so that we can render the chunk.
	Program*					_program;

	/*************** Methods ***************/
private:
	float						getStableState(float totalMass);

public:
	Chunk(Program* _program, glm::vec3 position);
	~Chunk();

	//Updates everything.
	void						update();

	//Updates only the water blocks.
	void						updateWater();

	//Renders everything.
	void						render();

	//Builds the chunk (every single block) and puts them to the shaders.
	void						buildChunk();

	//Builds the water and puts them to the shaders.
	void						buildWater();

	void						setPosition(const glm::vec3 position);
	glm::vec3					getPosition() const;
	void						setLoaded(const bool loaded);
	bool						isLoaded() const;
	void						setGenerated(const bool generated);
	bool						isGenerated() const;
};

#endif