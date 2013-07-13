#include "SolidBlock.h"

SolidBlock::SolidBlock() {
}

SolidBlock::SolidBlock(glm::vec3 position, BlockMaterial material, bool active) : 
	Block(position, material, BlockType::Solid, active) 
{
}

SolidBlock::~SolidBlock() {
}

int SolidBlock::loadBlock(GLfloat* data,
							   bool blockAbove, bool blockBelow, 
							   bool blockLeft, bool blockRight, 
							   bool blockBehind, bool blockFront) {
	return this->load(data, _position, randomColor(_material), blockBelow, blockAbove, blockLeft, blockRight, blockFront, blockBehind);
}

void SolidBlock::update() {
	this->update();
}

void SolidBlock::render() {
	this->render();
}

glm::vec3 SolidBlock::randomColor(BlockMaterial material) {
	switch(material) {
		//73411E
		case BlockMaterial::Dirt:
			return MyMath::randomColor(115.0, 65.0, 30.0, 2, 2, 2);
		
		//808080
		case BlockMaterial::Stone:
			return MyMath::randomColor(128.0, 128.0, 128.0, 3);

		default:
			return glm::vec3(0, 0, 0);
	}
}