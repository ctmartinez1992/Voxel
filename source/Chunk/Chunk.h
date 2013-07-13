#ifndef CHUNK_H
#define CHUNK_H

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../Block/Block.h"
#include "../../OGLRender/Program.h"

class Chunk {
	/*************** Variables ***************/
private:
	//The vertexes used to render the chunk.
	GLuint						_vao;
	GLuint						_vbo;

	//Some size metrics, check the constructor for explanation.
	int							_chunkTotalSize;
	int							_renderBlockSize;
	int							_renderSize;
	int							_vboQuadSize;
	int							_vboBlockSize;
	int							_vboSize;

	//Position (Upper Left Nearest Corner).
	glm::vec3					_position;

	//Flag that checks if the chunk was loaded or not.
	bool						_loaded;

	//Flag that checks if the chunk was generated or not.
	bool						_generated;

public:
	//The size of a chunk.
	static const int			CHUNK_SIZE = 16;
	
	//The normal, un-pressurized mass of a full water cell.
	const float					MaxMass = 1.0;

	//How much excess water a cell can store, compared to the cell above it.
	const float					MaxCompress = 0.02;

	//Ignore cells that are almost dry
	const float					MinMass = 0.0001;

	//Smooth the Flow.
	const float					MinFlow = 0.01;

	//CHUNK_SIZE per CHUNK_SIZE per CHUNK_SIZE of Blocks
	Block***					_blocks;

	//Handles the OpenGL stuff so that we can render the chunk.
	Program*					_program;

	/*************** Methods ***************/
private:
	float						getStableState(float totalMass);

public:
	Chunk(Program* _program, glm::vec3 position);
	~Chunk();

	//Updates the Chunk.
	void						update();

	//Updates only the water blocks.
	void						updateWater();

	//Renders the Chunk.
	void						render();

	//Builds the chunk (every single block) and puts them to the shaders.
	void						buildChunk();
	
	void						setPosition(const glm::vec3 position);
	glm::vec3					getPosition() const;
	void						setLoaded(const bool loaded);
	bool						isLoaded() const;
	void						setGenerated(const bool generated);
	bool						isGenerated() const;
};

#endif