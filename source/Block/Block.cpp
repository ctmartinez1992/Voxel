#include "Block.h"

Block::Block() {
}

Block::Block(glm::vec3 position, BlockMaterial material, BlockType type, bool active) : 
	_position(position),
	_material(material),
	_type(type),
	_active(active) 
{
	if (type == BlockType::Liquid && material == BlockMaterial::Water) {
		_mass = 1;
		_newMass = 1;
	}
}

Block::~Block() {
}

int Block::load(GLfloat* data, 
				bool blockAbove, bool blockBelow, 
				bool blockLeft, bool blockRight, 
			    bool blockBehind, bool blockFront)
{
	float px = _position.x + 0.5f;
	float nx = _position.x - 0.5f;
	float py = _position.y + 0.5f;
	float ny = _position.y - 0.5f;
	float pz = _position.z + 0.5f;
	float nz = _position.z - 0.5f;

	if (getType() == BlockType::Liquid || getMaterial() == BlockMaterial::Water) {
		py -= 1 - _mass;
	}

	float cx = _color.x;
	float cy = _color.y;
	float cz = _color.z;

	int arrayPosition = 0;

	//X - Y - Z - R - G - B
	//Bot
	if (blockBelow) {
		data[arrayPosition] = nx;			data[arrayPosition+1] = ny;			data[arrayPosition+2] = nz;			data[arrayPosition+3] = cx;			data[arrayPosition+4] = cy;			data[arrayPosition+5] = cz;			data[arrayPosition+6] = 0;			data[arrayPosition+7] = -1;			data[arrayPosition+8] = 0;
		data[arrayPosition+9] = px;			data[arrayPosition+10] = ny;		data[arrayPosition+11] = nz;		data[arrayPosition+12] = cx;		data[arrayPosition+13] = cy;		data[arrayPosition+14] = cz;		data[arrayPosition+15] = 0;			data[arrayPosition+16] = -1;		data[arrayPosition+17] = 0;
		data[arrayPosition+18] = nx;		data[arrayPosition+19] = ny;		data[arrayPosition+20] = pz;		data[arrayPosition+21] = cx;		data[arrayPosition+22] = cy;		data[arrayPosition+23] = cz;		data[arrayPosition+24] = 0;			data[arrayPosition+25] = -1;		data[arrayPosition+26] = 0;
		data[arrayPosition+27] = px;		data[arrayPosition+28] = ny;		data[arrayPosition+29] = nz;		data[arrayPosition+30] = cx;		data[arrayPosition+31] = cy;		data[arrayPosition+32] = cz;		data[arrayPosition+33] = 0;			data[arrayPosition+34] = -1;		data[arrayPosition+35] = 0;
		data[arrayPosition+36] = px;		data[arrayPosition+37] = ny;		data[arrayPosition+38] = pz;		data[arrayPosition+39] = cx;		data[arrayPosition+40] = cy;		data[arrayPosition+41] = cz;		data[arrayPosition+42] = 0;			data[arrayPosition+43] = -1;		data[arrayPosition+44] = 0;
		data[arrayPosition+45] = nx;		data[arrayPosition+46] = ny;		data[arrayPosition+47] = pz;		data[arrayPosition+48] = cx;		data[arrayPosition+49] = cy;		data[arrayPosition+50] = cz;		data[arrayPosition+51] = 0;			data[arrayPosition+52] = -1;		data[arrayPosition+53] = 0;

		arrayPosition += 54;
	}

    //Top
	if (blockAbove) {
		data[arrayPosition] = nx;			data[arrayPosition+1] = py;			data[arrayPosition+2] = nz;			data[arrayPosition+3] = cx;			data[arrayPosition+4] = cy;			data[arrayPosition+5] = cz;			data[arrayPosition+6] = 0;			data[arrayPosition+7] = 1;			data[arrayPosition+8] = 0;
		data[arrayPosition+9] = nx;			data[arrayPosition+10] = py;		data[arrayPosition+11] = pz;		data[arrayPosition+12] = cx;		data[arrayPosition+13] = cy;		data[arrayPosition+14] = cz;		data[arrayPosition+15] = 0;			data[arrayPosition+16] = 1;			data[arrayPosition+17] = 0;
		data[arrayPosition+18] = px;		data[arrayPosition+19] = py;		data[arrayPosition+20] = nz;		data[arrayPosition+21] = cx;		data[arrayPosition+22] = cy;		data[arrayPosition+23] = cz;		data[arrayPosition+24] = 0;			data[arrayPosition+25] = 1;			data[arrayPosition+26] = 0;
		data[arrayPosition+27] = px;		data[arrayPosition+28] = py;		data[arrayPosition+29] = nz;		data[arrayPosition+30] = cx;		data[arrayPosition+31] = cy;		data[arrayPosition+32] = cz;		data[arrayPosition+33] = 0;			data[arrayPosition+34] = 1;			data[arrayPosition+35] = 0;
		data[arrayPosition+36] = nx;		data[arrayPosition+37] = py;		data[arrayPosition+38] = pz;		data[arrayPosition+39] = cx;		data[arrayPosition+40] = cy;		data[arrayPosition+41] = cz;		data[arrayPosition+42] = 0;			data[arrayPosition+43] = 1;			data[arrayPosition+44] = 0;
		data[arrayPosition+45] = px;		data[arrayPosition+46] = py;		data[arrayPosition+47] = pz;		data[arrayPosition+48] = cx;		data[arrayPosition+49] = cy;		data[arrayPosition+50] = cz;		data[arrayPosition+51] = 0;			data[arrayPosition+52] = 1;			data[arrayPosition+53] = 0;
		
		arrayPosition += 54;
	}

    //Front
	if (blockFront) {
		data[arrayPosition] = nx;			data[arrayPosition+1] = ny;			data[arrayPosition+2] = pz;			data[arrayPosition+3] = cx;			data[arrayPosition+4] = cy;			data[arrayPosition+5] = cz;			data[arrayPosition+6] = 0;			data[arrayPosition+7] = 0;			data[arrayPosition+8] = 1;
		data[arrayPosition+9] = px;			data[arrayPosition+10] = ny;		data[arrayPosition+11] = pz;		data[arrayPosition+12] = cx;		data[arrayPosition+13] = cy;		data[arrayPosition+14] = cz;		data[arrayPosition+15] = 0;			data[arrayPosition+16] = 0;			data[arrayPosition+17] = 1;
		data[arrayPosition+18] = nx;		data[arrayPosition+19] = py;		data[arrayPosition+20] = pz;		data[arrayPosition+21] = cx;		data[arrayPosition+22] = cy;		data[arrayPosition+23] = cz;		data[arrayPosition+24] = 0;			data[arrayPosition+25] = 0;			data[arrayPosition+26] = 1;
		data[arrayPosition+27] = px;		data[arrayPosition+28] = ny;		data[arrayPosition+29] = pz;		data[arrayPosition+30] = cx;		data[arrayPosition+31] = cy;		data[arrayPosition+32] = cz;		data[arrayPosition+33] = 0;			data[arrayPosition+34] = 0;			data[arrayPosition+35] = 1;
		data[arrayPosition+36] = px;		data[arrayPosition+37] = py;		data[arrayPosition+38] = pz;		data[arrayPosition+39] = cx;		data[arrayPosition+40] = cy;		data[arrayPosition+41] = cz;		data[arrayPosition+42] = 0;			data[arrayPosition+43] = 0;			data[arrayPosition+44] = 1;
		data[arrayPosition+45] = nx;		data[arrayPosition+46] = py;		data[arrayPosition+47] = pz;		data[arrayPosition+48] = cx;		data[arrayPosition+49] = cy;		data[arrayPosition+50] = cz;		data[arrayPosition+51] = 0;			data[arrayPosition+52] = 0;			data[arrayPosition+53] = 1;

		arrayPosition += 54;
	}

    //Back
	if (blockBehind) {
		data[arrayPosition] = nx;			data[arrayPosition+1] = ny;			data[arrayPosition+2] = nz;			data[arrayPosition+3] = cx;			data[arrayPosition+4] = cy;			data[arrayPosition+5] = cz;			data[arrayPosition+6] = 0;			data[arrayPosition+7] = 0;			data[arrayPosition+8] = -1;
		data[arrayPosition+9] = nx;			data[arrayPosition+10] = py;		data[arrayPosition+11] = nz;		data[arrayPosition+12] = cx;		data[arrayPosition+13] = cy;		data[arrayPosition+14] = cz;		data[arrayPosition+15] = 0;			data[arrayPosition+16] = 0;			data[arrayPosition+17] = -1;
		data[arrayPosition+18] = px;		data[arrayPosition+19] = ny;		data[arrayPosition+20] = nz;		data[arrayPosition+21] = cx;		data[arrayPosition+22] = cy;		data[arrayPosition+23] = cz;		data[arrayPosition+24] = 0;			data[arrayPosition+25] = 0;			data[arrayPosition+26] = -1;
		data[arrayPosition+27] = px;		data[arrayPosition+28] = ny;		data[arrayPosition+29] = nz;		data[arrayPosition+30] = cx;		data[arrayPosition+31] = cy;		data[arrayPosition+32] = cz;		data[arrayPosition+33] = 0;			data[arrayPosition+34] = 0;			data[arrayPosition+35] = -1;
		data[arrayPosition+36] = nx;		data[arrayPosition+37] = py;		data[arrayPosition+38] = nz;		data[arrayPosition+39] = cx;		data[arrayPosition+40] = cy;		data[arrayPosition+41] = cz;		data[arrayPosition+42] = 0;			data[arrayPosition+43] = 0;			data[arrayPosition+44] = -1;
		data[arrayPosition+45] = px;		data[arrayPosition+46] = py;		data[arrayPosition+47] = nz;		data[arrayPosition+48] = cx;		data[arrayPosition+49] = cy;		data[arrayPosition+50] = cz;		data[arrayPosition+51] = 0;			data[arrayPosition+52] = 0;			data[arrayPosition+53] = -1;
		
		arrayPosition += 54;
	}

    //Left
	if (blockLeft) {
		data[arrayPosition] = nx;			data[arrayPosition+1] = ny;			data[arrayPosition+2] = pz;			data[arrayPosition+3] = cx;			data[arrayPosition+4] = cy;			data[arrayPosition+5] = cz;			data[arrayPosition+6] = -1;			data[arrayPosition+7] = 0;			data[arrayPosition+8] = 0;
		data[arrayPosition+9] = nx;			data[arrayPosition+10] = py;		data[arrayPosition+11] = nz;		data[arrayPosition+12] = cx;		data[arrayPosition+13] = cy;		data[arrayPosition+14] = cz;		data[arrayPosition+15] = -1;		data[arrayPosition+16] = 0;			data[arrayPosition+17] = 0;
		data[arrayPosition+18] = nx;		data[arrayPosition+19] = ny;		data[arrayPosition+20] = nz;		data[arrayPosition+21] = cx;		data[arrayPosition+22] = cy;		data[arrayPosition+23] = cz;		data[arrayPosition+24] = -1;		data[arrayPosition+25] = 0;			data[arrayPosition+26] = 0;
		data[arrayPosition+27] = nx;		data[arrayPosition+28] = ny;		data[arrayPosition+29] = pz;		data[arrayPosition+30] = cx;		data[arrayPosition+31] = cy;		data[arrayPosition+32] = cz;		data[arrayPosition+33] = -1;		data[arrayPosition+34] = 0;			data[arrayPosition+35] = 0;
		data[arrayPosition+36] = nx;		data[arrayPosition+37] = py;		data[arrayPosition+38] = pz;		data[arrayPosition+39] = cx;		data[arrayPosition+40] = cy;		data[arrayPosition+41] = cz;		data[arrayPosition+42] = -1;		data[arrayPosition+43] = 0;			data[arrayPosition+44] = 0;
		data[arrayPosition+45] = nx;		data[arrayPosition+46] = py;		data[arrayPosition+47] = nz;		data[arrayPosition+48] = cx;		data[arrayPosition+49] = cy;		data[arrayPosition+50] = cz;		data[arrayPosition+51] = -1;		data[arrayPosition+52] = 0;			data[arrayPosition+53] = 0;

		arrayPosition += 54;
	}

    //Right
	if (blockRight) {
		data[arrayPosition] = px;			data[arrayPosition+1] = ny;			data[arrayPosition+2] = pz;			data[arrayPosition+3] = cx;			data[arrayPosition+4] = cy;			data[arrayPosition+5] = cz;			data[arrayPosition+6] = 1;			data[arrayPosition+7] = 0;			data[arrayPosition+8] = 0;
		data[arrayPosition+9] = px;			data[arrayPosition+10] = py;		data[arrayPosition+11] = nz;		data[arrayPosition+12] = cx;		data[arrayPosition+13] = cy;		data[arrayPosition+14] = cz;		data[arrayPosition+15] = 1;			data[arrayPosition+16] = 0;			data[arrayPosition+17] = 0;
		data[arrayPosition+18] = px;		data[arrayPosition+19] = ny;		data[arrayPosition+20] = nz;		data[arrayPosition+21] = cx;		data[arrayPosition+22] = cy;		data[arrayPosition+23] = cz;		data[arrayPosition+24] = 1;			data[arrayPosition+25] = 0;			data[arrayPosition+26] = 0;
		data[arrayPosition+27] = px;		data[arrayPosition+28] = ny;		data[arrayPosition+29] = pz;		data[arrayPosition+30] = cx;		data[arrayPosition+31] = cy;		data[arrayPosition+32] = cz;		data[arrayPosition+33] = 1;			data[arrayPosition+34] = 0;			data[arrayPosition+35] = 0;
		data[arrayPosition+36] = px;		data[arrayPosition+37] = py;		data[arrayPosition+38] = pz;		data[arrayPosition+39] = cx;		data[arrayPosition+40] = cy;		data[arrayPosition+41] = cz;		data[arrayPosition+42] = 1;			data[arrayPosition+43] = 0;			data[arrayPosition+44] = 0;
		data[arrayPosition+45] = px;		data[arrayPosition+46] = py;		data[arrayPosition+47] = nz;		data[arrayPosition+48] = cx;		data[arrayPosition+49] = cy;		data[arrayPosition+50] = cz;		data[arrayPosition+51] = 1;			data[arrayPosition+52] = 0;			data[arrayPosition+53] = 0;

		arrayPosition += 54;
	}

	return arrayPosition;
}

void Block::update() {
}

void Block::render() {
}

glm::vec3 Block::randomColor() {
	switch(_material) {
		//73411E
		case BlockMaterial::Dirt:
			return MyMath::randomColor(115.0, 65.0, 30.0, 2, 2, 2);
		
		//808080
		case BlockMaterial::Stone:
			return MyMath::randomColor(128.0, 128.0, 128.0, 3);

		//0505FA
		case BlockMaterial::Water:
			return MyMath::randomColor(5.0, 5.0, 250.0, 1);

		default:
			return glm::vec3(0, 0, 0);
	}
}

void Block::setPosition(glm::vec3 position) {
	_position = position;
}

glm::vec3 Block::getPosition() const {
	return _position;
}

void Block::setMaterial(BlockMaterial material) {
	_material = material;
	_color = randomColor();
}

BlockMaterial Block::getMaterial() const {
	return _material;
}

void Block::setType(BlockType type) {
	_type = type;
}

BlockType Block::getType() const {
	return _type;
}

void Block::setActive(bool active) {
	_active = active;
}

bool Block::isActive() const {
	return _active;
}

void Block::setMass(float mass) {
	_mass = mass;
}

void Block::setNewMass(float newMass) {
	_newMass = newMass;
}

float Block::getMass() const {
	return _mass;
}
	
float Block::getNewMass() const {
	return _newMass;
}