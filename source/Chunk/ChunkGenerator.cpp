#include "ChunkGenerator.h"

ChunkGenerator* ChunkGenerator::_instance = 0;

ChunkGenerator::ChunkGenerator() {
	assert(!_instance);
	_instance = this;
	
	_heightMap = new int*[Chunk::CHUNK_SIZE];
	for(int i=0; i<Chunk::CHUNK_SIZE; ++i) {
		_heightMap[i] = new int[Chunk::CHUNK_SIZE];
	}

	_temperatureMap = new int*[Chunk::CHUNK_SIZE];
	for(int i=0; i<Chunk::CHUNK_SIZE; ++i) {
		_temperatureMap[i] = new int[Chunk::CHUNK_SIZE];
	}

	_perlin = new PerlinNoise();
}

ChunkGenerator::~ChunkGenerator() {
	for (int i=0; i<Chunk::CHUNK_SIZE; ++i) {
        delete [] _heightMap[i];
    }
    delete [] _heightMap;
	
	for (int i=0; i<Chunk::CHUNK_SIZE; ++i) {
        delete [] _temperatureMap[i];
    }
    delete [] _temperatureMap;

	delete _perlin;

	_instance = 0;
}

ChunkGenerator* ChunkGenerator::getInstance() {
   if (!_instance) {
      _instance = new ChunkGenerator;
   }
   return _instance;
}
    
void ChunkGenerator::generateChunk(Chunk* chunk) {
	for (int x = 0; x < Chunk::CHUNK_SIZE; ++x) {
        for (int y = 0; y < Chunk::CHUNK_SIZE; ++y) {
			for (int z = 0; z < Chunk::CHUNK_SIZE; ++z) {
				_heightMap[x][z] = getHeightAt(x + chunk->getPosition().x, y + chunk->getPosition().y, z + chunk->getPosition().z) - chunk->getPosition().y;
                /*if (chunk != NULL) {
					if (y < _heightMap[x][z]) {
						chunk->_blocks[x][y][z].setActive(true);
					} else {
						chunk->_blocks[x][y][z].setActive(false);
					}
				}*/
				
				chunk->_blocks[x][y][z].setPosition(glm::vec3((x+chunk->getPosition().x), (y+chunk->getPosition().y), (z+chunk->getPosition().z)));
				if (y>3) {
					chunk->_blocks[x][y][z].setActive(false);
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Air);
					chunk->_blocks[x][y][z].setType(BlockType::Air);
					chunk->_blocks[x][y][z].setMass(0.01);
					chunk->_blocks[x][y][z].setNewMass(0.01);
				} else {
					chunk->_blocks[x][y][z].setActive(true);
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Dirt);
					chunk->_blocks[x][y][z].setType(BlockType::Solid);
					chunk->_blocks[x][y][z].setMass(0.0);
					chunk->_blocks[x][y][z].setNewMass(0.0);
				}

				if (x==8 && y==10 && z==8) {
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Water);
					chunk->_blocks[x][y][z].setType(BlockType::Liquid);
					chunk->_blocks[x][y][z].setMass(1);
					chunk->_blocks[x][y][z].setNewMass(1);
					chunk->_blocks[x][y][z].setActive(true);
					chunk->_waterList.push_back(&chunk->_blocks[x][y][z]);
				}

				if (x==6 && y==10 && z==6) {
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Water);
					chunk->_blocks[x][y][z].setType(BlockType::Liquid);
					chunk->_blocks[x][y][z].setMass(1);
					chunk->_blocks[x][y][z].setNewMass(1);
					chunk->_blocks[x][y][z].setActive(true);
					chunk->_waterList.push_back(&chunk->_blocks[x][y][z]);
				}
				
				if (x==6 && y==4 && z==6) {
					chunk->_blocks[x][y][z].setActive(true);
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Dirt);
					chunk->_blocks[x][y][z].setType(BlockType::Solid);
					chunk->_blocks[x][y][z].setMass(0.0);
					chunk->_blocks[x][y][z].setNewMass(0.0);
				}
				if (x==7 && y==4 && z==6) {
					chunk->_blocks[x][y][z].setActive(true);
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Dirt);
					chunk->_blocks[x][y][z].setType(BlockType::Solid);
					chunk->_blocks[x][y][z].setMass(0.0);
					chunk->_blocks[x][y][z].setNewMass(0.0);
				}
				if (x==8 && y==4 && z==6) {
					chunk->_blocks[x][y][z].setActive(true);
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Dirt);
					chunk->_blocks[x][y][z].setType(BlockType::Solid);
					chunk->_blocks[x][y][z].setMass(0.0);
					chunk->_blocks[x][y][z].setNewMass(0.0);
				}
				if (x==9 && y==4 && z==6) {
					chunk->_blocks[x][y][z].setActive(true);
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Dirt);
					chunk->_blocks[x][y][z].setType(BlockType::Solid);
					chunk->_blocks[x][y][z].setMass(0.0);
					chunk->_blocks[x][y][z].setNewMass(0.0);
				}
				if (x==10 && y==4 && z==6) {
					chunk->_blocks[x][y][z].setActive(true);
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Dirt);
					chunk->_blocks[x][y][z].setType(BlockType::Solid);
					chunk->_blocks[x][y][z].setMass(0.0);
					chunk->_blocks[x][y][z].setNewMass(0.0);
				}
				if (x==6 && y==4 && z==7) {
					chunk->_blocks[x][y][z].setActive(true);
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Dirt);
					chunk->_blocks[x][y][z].setType(BlockType::Solid);
					chunk->_blocks[x][y][z].setMass(0.0);
					chunk->_blocks[x][y][z].setNewMass(0.0);
				}
				if (x==6 && y==4 && z==8) {
					chunk->_blocks[x][y][z].setActive(true);
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Dirt);
					chunk->_blocks[x][y][z].setType(BlockType::Solid);
					chunk->_blocks[x][y][z].setMass(0.0);
					chunk->_blocks[x][y][z].setNewMass(0.0);
				}
				if (x==6 && y==4 && z==9) {
					chunk->_blocks[x][y][z].setActive(true);
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Dirt);
					chunk->_blocks[x][y][z].setType(BlockType::Solid);
					chunk->_blocks[x][y][z].setMass(0.0);
					chunk->_blocks[x][y][z].setNewMass(0.0);
				}
				if (x==6 && y==4 && z==10) {
					chunk->_blocks[x][y][z].setActive(true);
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Dirt);
					chunk->_blocks[x][y][z].setType(BlockType::Solid);
					chunk->_blocks[x][y][z].setMass(0.0);
					chunk->_blocks[x][y][z].setNewMass(0.0);
				}
				if (x==10 && y==4 && z==6) {
					chunk->_blocks[x][y][z].setActive(true);
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Dirt);
					chunk->_blocks[x][y][z].setType(BlockType::Solid);
					chunk->_blocks[x][y][z].setMass(0.0);
					chunk->_blocks[x][y][z].setNewMass(0.0);
				}
				if (x==10 && y==4 && z==7) {
					chunk->_blocks[x][y][z].setActive(true);
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Dirt);
					chunk->_blocks[x][y][z].setType(BlockType::Solid);
					chunk->_blocks[x][y][z].setMass(0.0);
					chunk->_blocks[x][y][z].setNewMass(0.0);
				}
				if (x==10 && y==4 && z==8) {
					chunk->_blocks[x][y][z].setActive(true);
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Dirt);
					chunk->_blocks[x][y][z].setType(BlockType::Solid);
					chunk->_blocks[x][y][z].setMass(0.0);
					chunk->_blocks[x][y][z].setNewMass(0.0);
				}
				if (x==10 && y==4 && z==9) {
					chunk->_blocks[x][y][z].setActive(true);
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Dirt);
					chunk->_blocks[x][y][z].setType(BlockType::Solid);
					chunk->_blocks[x][y][z].setMass(0.0);
					chunk->_blocks[x][y][z].setNewMass(0.0);
				}
				if (x==10 && y==4 && z==10) {
					chunk->_blocks[x][y][z].setActive(true);
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Dirt);
					chunk->_blocks[x][y][z].setType(BlockType::Solid);
					chunk->_blocks[x][y][z].setMass(0.0);
					chunk->_blocks[x][y][z].setNewMass(0.0);
				}
				if (x==9 && y==4 && z==10) {
					chunk->_blocks[x][y][z].setActive(true);
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Dirt);
					chunk->_blocks[x][y][z].setType(BlockType::Solid);
					chunk->_blocks[x][y][z].setMass(0.0);
					chunk->_blocks[x][y][z].setNewMass(0.0);
				}
				if (x==8 && y==4 && z==10) {
					chunk->_blocks[x][y][z].setActive(true);
					chunk->_blocks[x][y][z].setMaterial(BlockMaterial::Dirt);
					chunk->_blocks[x][y][z].setType(BlockType::Solid);
					chunk->_blocks[x][y][z].setMass(0.0);
					chunk->_blocks[x][y][z].setNewMass(0.0);
				}
            }
        }
	}

	chunk->buildChunk();
	chunk->buildWater();

	if (chunk != NULL) {
		chunk->setGenerated(true);
	}
}
    
int ChunkGenerator::getHeightAt(int x, int z) {
    float height1 = 30.0f * _perlin->noise(x * 0.01f, z * 0.01f);
	float height2 = 40.0f * _perlin->noise(x * 0.04f, z * 0.04f) * _perlin->noise(x * 0.002f, z * 0.002f);
	float height3 = 4.0f * _perlin->noise(x * 0.08f, z * 0.08f);
        
	return (int) abs(20 + height1 + height2 + height3);
}
    
int ChunkGenerator::getHeightAt(int x, int y, int z) {
    float height1 = 30.0f * _perlin->noise(x * 0.01f, y * 0.01f, z * 0.01f);
	float height2 = 40.0f * _perlin->noise(x * 0.04f, y * 0.04f, z * 0.04f) * _perlin->noise(x * 0.002f, y * 0.002f, z * 0.002f);
	float height3 = 4.0f * _perlin->noise(x * 0.08f, y * 0.08f, z * 0.08f);
        
	return (int) abs(-20 + height1 + height2 + height3);
}


