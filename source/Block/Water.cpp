#include "Water.h"

Water::Water() {
}

Water::Water(glm::vec3 position, bool active) : _mass(1), _newMass(1),
	Block(position, BlockMaterial::Water, BlockType::Liquid, active)
{

}

Water::~Water() {
}

int Water::loadWaterBlock(GLfloat* data,
							   bool blockAbove, bool blockBelow, 
							   bool blockLeft, bool blockRight, 
							   bool blockBehind, bool blockFront) {
	return this->load(data, _position, randomWaterColor(), blockBelow, blockAbove, blockLeft, blockRight, blockFront, blockBehind);
}

void Water::update() {
	this->update();
}

void Water::render() {
	this->render();
}

glm::vec3 Water::randomWaterColor() {
	return MyMath::randomColor(5.0, 5.0, 250.0, 0, 0, 2);
}
	
void Water::setMasses(float mass, float newMass) {
	_mass = mass;
	_newMass = newMass;
}

float Water::getMass() const {
	return _mass;
}
	
float Water::getNewMass() const {
	return _newMass;
}