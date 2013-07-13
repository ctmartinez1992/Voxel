#ifndef WATER_H
#define WATER_H

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Block.h"

class Water : public Block {
	/*************** Variables ***************/
private:
	float						_mass;
	float						_newMass;

	/*************** Methods ***************/
public:
	Water();
	Water(glm::vec3 position, bool active);
	~Water();

	//Updates the Block (usually won't do a thing).
	void						update();

	//Renders the Block (usually won't do a thing).
	void						render();
	
	//Loads the block into the vector, calls the upper class function.
	int							loadBlock(GLfloat* data, bool blockAbove, bool blockBelow, bool blockLeft, bool blockRight, bool blockBehind, bool blockFront);

	//Generates a random color given a material.
	static glm::vec3			randomWaterColor();
	
	void setMasses(float mass, float newMass);
	float getMass() const;
	float getNewMass() const;
};

#endif