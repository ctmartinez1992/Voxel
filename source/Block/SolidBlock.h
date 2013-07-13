#ifndef SOLIDBLOCK_H
#define SOLIDBLOCK_H

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Block.h"

class SolidBlock : public Block {
	/*************** Variables ***************/

	/*************** Methods ***************/
public:
	SolidBlock();
	SolidBlock(glm::vec3 position, BlockMaterial material, bool active);
	~SolidBlock();

	//Updates the Block (usually won't do a thing).
	void						update();

	//Renders the Block (usually won't do a thing).
	void						render();
	
	//Loads the block into the vector, calls the upper class function.
	int							loadBlock(GLfloat* data, bool blockAbove, bool blockBelow, bool blockLeft, bool blockRight, bool blockBehind, bool blockFront);

	//Generates a random color given a material.
	static glm::vec3			randomColor(BlockMaterial material);
};

#endif