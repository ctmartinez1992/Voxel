#ifndef BLOCK_H
#define BLOCK_H

#include <GL/glew.h>
#include <GL/glfw.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../Util/MyMath.h"

enum class BlockMaterial {
	Air,
	Dirt,
	Stone,
	Water
};

enum class BlockType {
	Air,
	Solid,
	Liquid
};

class Block {
	/*************** Variables ***************/
private:
	glm::vec3					_position;
	BlockMaterial				_material;
	BlockType					_type;
	bool						_active;

	//Water variables
	float _mass;
	float _newMass;

	/*************** Methods ***************/
public:
	Block();
	Block(glm::vec3 position, BlockMaterial material, BlockType type, bool active);
	virtual ~Block();

	//Updates the Block (usually won't do a thing).
	void						update();

	//Renders the Block (usually won't do a thing).
	void						render();

	//Loads the block into the vector and gives position and color to it, it also decides what faces to render.
	int							load(GLfloat* data, bool blockAbove, bool blockBelow, bool blockLeft, bool blockRight, bool blockBehind, bool blockFront);

	//Returns a random color based on the material.
	glm::vec3					randomColor();
	
	void						setPosition(glm::vec3 position);
	glm::vec3					getPosition() const;
	void						setMaterial(BlockMaterial material);
	BlockMaterial				getMaterial() const;
	void						setType(BlockType type);
	BlockType					getType() const;
	void						setActive(bool active);
	bool						isActive() const;
	void						setMass(float mass);
	float						Block::getMass() const;
	void						setNewMass(float newMass);
	float						Block::getNewMass() const;
};

#endif