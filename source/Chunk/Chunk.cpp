#include "Chunk.h"

const float	Chunk::MaxSpeed = 1.0;
const float	Chunk::MaxMass = 1.0;
const float	Chunk::MinMass = 0.1;
const float Chunk::MaxCompress = 0.001f;
const float	Chunk::MinFlow = 0.0001;

Chunk::Chunk(Program* program, glm::vec3 position) : _vbo(0), _vao(0), _wvbo(0), _wvao(0), _position(position), _loaded(false), _generated(false),
				 _chunkTotalSize(CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE),	//Amount of blocks in a chunk
				 _renderBlockSize(6*2*3),										//6 faces * 2 triangles per face * 3 points for each triangle
				 _renderSize(0),												//All the block triangles that are going to be rendered
				 _renderWaterSize(0),											//All the water triangles that are going to be rendered
				 _vboQuadSize((3+3+3)*2*3),										//The amount of points in a quad * (3 GLfloats for position + 3 GLfloats for color + 3 GLfloats for normals)
				 _vboBlockSize((3+3+3)*_renderBlockSize),						//The amount of points in a block * (3 GLfloats for position + 3 GLfloats for colo + 3 GLfloats for normalsr)
				 _vboSize((sizeof(GLfloat)*_vboBlockSize)*_chunkTotalSize)		//vbo of a block * the size of a GLfloat * the amount of blocks in a chunk
{	
	_program = program;
	_position.x *= CHUNK_SIZE;
	_position.y *= CHUNK_SIZE;
	_position.z *= CHUNK_SIZE;

	_blocks = new Block**[CHUNK_SIZE];
	for(int i=0; i<CHUNK_SIZE; i++) {
		_blocks[i] = new Block*[CHUNK_SIZE];
		for(int j=0; j<CHUNK_SIZE; j++) {
			_blocks[i][j] = new Block[CHUNK_SIZE];
		}
	}

	start = std::chrono::steady_clock::now();
	
	glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
	glGenVertexArrays(1, &_wvao);
    glGenBuffers(1, &_wvbo);
}

Chunk::~Chunk() {
    for (int i=0; i<CHUNK_SIZE; ++i) {
        for (int j=0; j<CHUNK_SIZE; ++j) {
            delete [] _blocks[i][j];
        }
        delete [] _blocks[i];
    }
    delete [] _blocks;
}

void Chunk::buildChunk() {
    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	
	GLfloat* data = new GLfloat[_vboBlockSize];
	GLfloat* vertexData = new GLfloat[_vboBlockSize * _chunkTotalSize];
	Block* tmpBlock;
	double vertexDataSize = 0;
	int currentBlockVertexDataSize = 0;
	int vertexDataCurrentPosition = 0;
	
	for(int x = 0; x < CHUNK_SIZE; x++) {
		for(int y = 0; y < CHUNK_SIZE; y++) {
			for(int z = 0; z < CHUNK_SIZE; z++) {
				tmpBlock = &_blocks[x][y][z];
				if (tmpBlock->getType() == BlockType::Liquid || tmpBlock->getMaterial() == BlockMaterial::Water) {
					continue;
				}

				if (!tmpBlock->isActive()) {
					continue;
				}

				bool negX = false;
				if(x > 0) {
					negX = _blocks[x-1][y][z].isActive();
				}

				bool posX = false;
				if(x < CHUNK_SIZE-1) {
					posX = _blocks[x+1][y][z].isActive();
				}

				bool negY = false;
				if(y > 0) {
					negY = _blocks[x][y-1][z].isActive();
				}

				bool posY = false;
				if(y < CHUNK_SIZE-1) {
					posY = _blocks[x][y+1][z].isActive();
				}

				bool negZ = false;
				if(z > 0) {
					negZ = _blocks[x][y][z-1].isActive();
				}

				bool posZ = false;
				if(z < CHUNK_SIZE-1) {
					posZ = _blocks[x][y][z+1].isActive();
				}

				if (posX && negX && posY && negY && posZ && negZ) {
					continue;
				} else {
					currentBlockVertexDataSize = tmpBlock->load(data, !posY, !negY, !negX, !posX, !negZ, !posZ);
				}
				
				for(int i=vertexDataCurrentPosition, j=0; i<(vertexDataCurrentPosition+currentBlockVertexDataSize), j<currentBlockVertexDataSize; i++, j++) {
					vertexData[i] = data[j];
				}
				
				_renderSize += (currentBlockVertexDataSize / 2) / 3;
				vertexDataCurrentPosition += currentBlockVertexDataSize;
				vertexDataSize += currentBlockVertexDataSize * 4;
			}
		}
	}

	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, vertexData, GL_STATIC_DRAW);
	glEnableVertexAttribArray(_program->attrib("vert"));
    glVertexAttribPointer(_program->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 9*sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(_program->attrib("vertColor"));
    glVertexAttribPointer(_program->attrib("vertColor"), 3, GL_FLOAT, GL_TRUE, 9*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(_program->attrib("vertNormal"));
    glVertexAttribPointer(_program->attrib("vertNormal"), 3, GL_FLOAT, GL_FALSE, 9*sizeof(GLfloat), (const GLvoid*)(6 * sizeof(GLfloat)));
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete[] data;
	delete[] vertexData;

	_loaded = true;
}

void Chunk::buildWater() {
    glBindVertexArray(_wvao);
    glBindBuffer(GL_ARRAY_BUFFER, _wvbo);
	
	GLfloat* data = new GLfloat[_vboBlockSize];
	GLfloat* vertexData = new GLfloat[_vboBlockSize * _waterList.size()];
	double vertexDataSize = 0;
	int currentBlockVertexDataSize = 0;
	int vertexDataCurrentPosition = 0;
	
	std::vector<Block*>::iterator iterator;
    for(iterator = _waterList.begin(); iterator != _waterList.end(); iterator++) {
		Block* block = *iterator;
		
		currentBlockVertexDataSize = block->load(data, true, true, true, true, true, true);
		for(int i=vertexDataCurrentPosition, j=0; i<(vertexDataCurrentPosition+currentBlockVertexDataSize), j<currentBlockVertexDataSize; i++, j++) {
			vertexData[i] = data[j];
		}
				
		_renderWaterSize += (currentBlockVertexDataSize / 2) / 3;
		vertexDataCurrentPosition += currentBlockVertexDataSize;
		vertexDataSize += currentBlockVertexDataSize * 4;
	}

	glBufferData(GL_ARRAY_BUFFER, vertexDataSize, NULL, GL_DYNAMIC_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertexDataSize, vertexData);
	glEnableVertexAttribArray(_program->attrib("vert"));
    glVertexAttribPointer(_program->attrib("vert"), 3, GL_FLOAT, GL_FALSE, 9*sizeof(GLfloat), NULL);
    glEnableVertexAttribArray(_program->attrib("vertColor"));
    glVertexAttribPointer(_program->attrib("vertColor"), 3, GL_FLOAT, GL_TRUE, 9*sizeof(GLfloat), (const GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(_program->attrib("vertNormal"));
    glVertexAttribPointer(_program->attrib("vertNormal"), 3, GL_FLOAT, GL_FALSE, 9*sizeof(GLfloat), (const GLvoid*)(6 * sizeof(GLfloat)));
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

	delete[] data;
	delete[] vertexData;
}

void Chunk::updateWater() {
	float flow = 0;
	float remaining_mass;
   
	//Calculate and apply flow for each block.
	for (int x(1); x!=CHUNK_SIZE-1; ++x) {
		for(int y(1); y!=CHUNK_SIZE-1; ++y) {
			for(int z(1); z!=CHUNK_SIZE-1; ++z) {
				//Only for water (liquid).
				if (_blocks[x][y][z].getType() == BlockType::Liquid && _blocks[x][y][z].getMaterial() == BlockMaterial::Water) {
					Block* thisBlock = &_blocks[x][y][z];

					//Custom push-only flow.
					flow = 0;
					remaining_mass = thisBlock->getMass();
					if (remaining_mass <= 0) {
						continue;
					}
        
					//The block below this one
					if (_blocks[x][y-1][z].getType() != BlockType::Solid) {
						flow = getStableState(remaining_mass + _blocks[x][y-1][z].getMass()) - _blocks[x][y-1][z].getMass();
						if (flow > MinFlow) {
							//Leads to smoother flow.
							flow *= 0.5;
						}

						flow = MyMath::constrain(flow, 0.0, MyMath::min(MaxSpeed, remaining_mass));
						thisBlock->setNewMass(thisBlock->getNewMass() - flow);
						_blocks[x][y-1][z].setNewMass(_blocks[x][y-1][z].getNewMass() + flow);  
						remaining_mass -= flow;
					}
        
					if ( remaining_mass <= 0 ) {
						continue;
					}
        
					//The block left of this one.
					if (_blocks[x-1][y][z].getType() != BlockType::Solid && _blocks[x][y-1][z].getType() == BlockType::Solid) {
						//Equalize the amount of water in this block and it's neighbour
						flow = (thisBlock->getMass() - _blocks[x-1][y][z].getNewMass()) / 4;
						if (flow > MinFlow) {
							flow *= 0.5;
						}

						flow = MyMath::constrain(flow, 0.0, remaining_mass);
						thisBlock->setNewMass(thisBlock->getNewMass() - flow);
						_blocks[x-1][y][z].setNewMass(_blocks[x-1][y][z].getNewMass() + flow);  
						remaining_mass -= flow;
					}
        
					if (remaining_mass <= 0) {
						continue;
					}
 
					//The block right of this one.
					if (_blocks[x+1][y][z].getType() != BlockType::Solid && _blocks[x][y-1][z].getType() == BlockType::Solid) {
						//Equalize the amount of water in this block and it's neighbour
						flow = (thisBlock->getMass() - _blocks[x+1][y][z].getNewMass()) / 4;
						if (flow > MinFlow) {
							flow *= 0.5;
						}
						
						flow = MyMath::constrain(flow, 0.0, remaining_mass);
						thisBlock->setNewMass(thisBlock->getNewMass() - flow);
						_blocks[x+1][y][z].setNewMass(_blocks[x+1][y][z].getNewMass() + flow);  
						remaining_mass -= flow;
					}
        
					if ( remaining_mass <= 0 ) {
						continue;
					}
        
					//The block in front of this one.
					if (_blocks[x][y][z-1].getType() != BlockType::Solid && _blocks[x][y-1][z].getType() == BlockType::Solid) {
						//Equalize the amount of water in this block and it's neighbour
						flow = (thisBlock->getMass() - _blocks[x][y][z-1].getNewMass()) / 4;
						if (flow > MinFlow) {
							flow *= 0.5;
						}

						flow = MyMath::constrain(flow, 0.0, remaining_mass);
						thisBlock->setNewMass(thisBlock->getNewMass() - flow);
						_blocks[x][y][z-1].setNewMass(_blocks[x][y][z-1].getNewMass() + flow);  
						remaining_mass -= flow;
					}
        
					if (remaining_mass <= 0) {
						continue;
					}
 
					//The block behind of this one.
					if (_blocks[x][y][z+1].getType() != BlockType::Solid && _blocks[x][y-1][z].getType() == BlockType::Solid) {
						//Equalize the amount of water in this block and it's neighbour
						flow = (thisBlock->getMass() - _blocks[x][y][z+1].getNewMass()) / 4;
						if (flow > MinFlow) {
							flow *= 0.5;
						}
						
						flow = MyMath::constrain(flow, 0.0, remaining_mass);
						thisBlock->setNewMass(thisBlock->getNewMass() - flow);
						_blocks[x][y][z+1].setNewMass(_blocks[x][y][z+1].getNewMass() + flow);  
						remaining_mass -= flow;
					}
        
					if ( remaining_mass <= 0 ) {
						continue;
					}
        
					////The block above of this one, only compressed water flows upwards.
					//if (_blocks[x][y+1][z].getType() != BlockType::Solid) {
					//	flow = remaining_mass - getStableState(remaining_mass + _blocks[x][y+1][z].getMass());
					//	if (flow > MinFlow) {
					//		flow *= 0.5;
					//	}

					//	flow = MyMath::constrain(flow, 0.0, MyMath::min(MaxSpeed, remaining_mass));
					//	thisBlock->setNewMass(thisBlock->getNewMass() - flow);
					//	_blocks[x][y+1][z].setNewMass(_blocks[x][y+1][z].getNewMass() + flow);  
					//	remaining_mass -= flow;
					//}
				} 
			}
		}
	}

	//Copy the new mass values to the mass array
	for (int x(0); x!=CHUNK_SIZE; ++x) {
		for(int y(0); y!=CHUNK_SIZE; ++y) {
			for(int z(0); z!=CHUNK_SIZE; ++z) {
				if(_blocks[x][y][z].getType() == BlockType::Solid) {
					continue;
				}

				//Flag/unflag water blocks
				if (_blocks[x][y][z].getMass() > MinMass) {
					_blocks[x][y][z].setType(BlockType::Liquid);
					_blocks[x][y][z].setMaterial(BlockMaterial::Water);
					_blocks[x][y][z].setActive(true);
					_waterList.push_back(&_blocks[x][y][z]);
					
					std::sort(_waterList.begin(), _waterList.end());
					_waterList.erase(std::unique(_waterList.begin(), _waterList.end()), _waterList.end());
				}

				_blocks[x][y][z].setMass(_blocks[x][y][z].getNewMass());

				if (_blocks[x][y][z].getMass() <= 0.0) {
					_blocks[x][y][z].setType(BlockType::Air);
					_blocks[x][y][z].setMaterial(BlockMaterial::Air);
					_blocks[x][y][z].setActive(false);
					_blocks[x][y][z].setMass(0.01);
					_blocks[x][y][z].setNewMass(0.01);
					_waterList.erase(std::remove(_waterList.begin(), _waterList.end(), &_blocks[x][y][z]), _waterList.end());
				}
			}
		}
	}

	buildWater();
}

void Chunk::update() {
	end = std::chrono::steady_clock::now();
	std::chrono::steady_clock::duration time_span = start - end;
	double nseconds = double(time_span.count()) * std::chrono::steady_clock::period::num / std::chrono::steady_clock::period::den;

	if ((nseconds*-1) > 0.05) {
		start = std::chrono::steady_clock::now();
		updateWater();
		std::cout << _waterList.size() << "-";
	}
}

void Chunk::render() {
	_program->setUniform("model", glm::mat4());
	
    glBindVertexArray(_vao);
		glDrawArrays(GL_TRIANGLES, 0, _renderSize);
    glBindVertexArray(0);

    glBindVertexArray(_wvao);
		glDrawArrays(GL_TRIANGLES, 0, _renderWaterSize);
    glBindVertexArray(0);
}

float Chunk::getStableState(float totalMass) {
	if (totalMass <= 1) {
		return 1;
	} else if (totalMass < (2 * MaxMass + MaxCompress)) {
		return (MaxMass*MaxMass + totalMass * MaxCompress) / (MaxMass + MaxCompress);
	} else {
		return (totalMass + MaxCompress) / 2;
	}
}

void Chunk::setPosition(const glm::vec3 position) {
	_position = position;
}

glm::vec3 Chunk::getPosition() const {
	return _position;
}

void Chunk::setLoaded(const bool loaded) {
	_loaded = loaded;
}

bool Chunk::isLoaded() const {
	return _loaded;
}

void Chunk::setGenerated(const bool generated) {
	_generated = generated;
}

bool Chunk::isGenerated() const {
	return _generated;
}