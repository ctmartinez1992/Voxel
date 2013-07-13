#include "Chunk.h"

Chunk::Chunk(Program* program, glm::vec3 position) : _vbo(0), _vao(0), _position(position), _loaded(false), _generated(false),
				 _chunkTotalSize(CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE),	//Amount of blocks in a chunk
				 _renderBlockSize(6*2*3),										//6 faces * 2 triangles per face * 3 points for each triangle
				 _renderSize(0),												//All the triangles that are going to be rendered
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
	glGenVertexArrays(1, &_vao);
    glBindVertexArray(_vao);
    glGenBuffers(1, &_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	
	GLfloat* data = new GLfloat[_vboBlockSize];
	GLfloat* vertexData = new GLfloat[_vboBlockSize*_chunkTotalSize];
	Block* tmpBlock;
	double vertexDataSize = 0;
	int currentBlockVertexDataSize = 0;
	int vertexDataCurrentPosition = 0;
	
	for(int x = 0; x < CHUNK_SIZE; x++) {
		for(int y = 0; y < CHUNK_SIZE; y++) {
			for(int z = 0; z < CHUNK_SIZE; z++) {
				tmpBlock = &_blocks[x][y][z];

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

	delete[] data;
	delete[] vertexData;

	_loaded = true;
}

void Chunk::updateWater() {
	float flow = 0;
	float remaining_mass;
   
	//Calculate and apply flow for each block.
	for (int x(1); x!=CHUNK_SIZE; ++x) {
		for(int y(1); y!=CHUNK_SIZE; ++y) {
			for(int z(1); z!=CHUNK_SIZE; ++z) {
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
					if ((_blocks[x][y-1][z].getType() != BlockType::Solid)) {
						flow = getStableState(remaining_mass + _blocks[x][y][z].getMass()) - _blocks[x][y][z].getMass();
						if (flow > MinFlow) {
							//Leads to smoother flow.
							flow *= 0.5;
						}
						//TOU AQUI A FAZER O MIN NO MYMATH
						flow = MyMath::constrain(flow, 0, min(MaxSpeed, remaining_mass));
          
         new_mass[x][y] -= flow;
         new_mass[x][y-1] += flow;  
         remaining_mass -= flow;
       }
        
       if ( remaining_mass <= 0 ) continue;
        
       //Left
       if ( blocks[x-1][y] != GROUND ){
         //Equalize the amount of water in this block and it's neighbour
         flow = (mass[x][y] - mass[x-1][y])/4;
         if ( flow > MinFlow ){ flow *= 0.5; }
         flow = constrain(flow, 0, remaining_mass);
           
         new_mass[x][y] -= flow;
         new_mass[x-1][y] += flow;
         remaining_mass -= flow;
       }
        
       if ( remaining_mass <= 0 ) continue;
 
       //Right
       if ( blocks[x+1][y] != GROUND ){
         //Equalize the amount of water in this block and it's neighbour
         flow = (mass[x][y] - mass[x+1][y])/4;
         if ( flow > MinFlow ){ flow *= 0.5; }
         flow = constrain(flow, 0, remaining_mass);
           
         new_mass[x][y] -= flow;
         new_mass[x+1][y] += flow;
         remaining_mass -= flow;
       }
        
       if ( remaining_mass <= 0 ) continue;
        
       //Up. Only compressed water flows upwards.
       if ( blocks[x][y+1] != GROUND ){
         flow = remaining_mass - getStableState( remaining_mass + mass[x][y+1] );
         if ( flow > MinFlow ){ flow *= 0.5; }
         flow = constrain( flow, 0, min(MaxSpeed, remaining_mass) );
          
         new_mass[x][y] -= flow;
         new_mass[x][y+1] += flow;  
         remaining_mass -= flow;
       }
 
				} 
     }
  }
		}
   
  //Copy the new mass values to the mass array
  for (int x = 0; x < map_width + 2; x++){
    for (int y = 0; y < map_height + 2; y++){
      mass[x][y] = new_mass[x][y];
    }
  }
   
  for (int x = 1; x <= map_width; x++){
     for(int y = 1; y <= map_height; y++){
       //Skip ground blocks
       if(blocks[x][y] == GROUND) continue;
       //Flag/unflag water blocks
       if (mass[x][y] > MinMass){
         blocks[x][y] = WATER;
       } else {
         blocks[x][y] = AIR;
       }
     }
  }
   
  //Remove any water that has left the map
  for (int x =0; x < map_width+2; x++){
    mass[x][0] = 0;
    mass[x][map_height+1] = 0;
  }
  for (int y = 1; y < map_height+1; y++){
    mass[0][y] = 0;
    mass[map_width+1][y] = 0;
  }
 
}

void Chunk::update() {
	updateWater();
}

void Chunk::render() {
	_program->setUniform("model", glm::mat4());

    glBindVertexArray(_vao);
		glDrawArrays(GL_TRIANGLES, 0, _renderSize);
    glBindVertexArray(0);
}

float Chunk::getStableState (float totalMass) {
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