#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include <iostream>
#include <vector>
#include <time.h>

#include "Chunk.h"
#include "ChunkGenerator.h"

class ChunkManager {
	/*************** Variables ***************/
public:
	//Amount of chucks that are loaded each frame.
	static const int				ASYNC_NUM_CHUNKS_PER_FRAME = 1;

	//List with all the chuncks ever.
	std::vector<Chunk*>				_chunkList;

	//List with all the chunks that need to be loaded.
	std::vector<Chunk*>				_chunkLoadList;

	//std::vector<Chunk>				chunkUnloadList;

	//std::vector<Chunk>				chunkSetupList;

	//std::vector<Chunk>				chunkVisibleList;

	//List with all the chunks that need to be rendered.
	std::vector<Chunk*>				_chunkRenderList;

	//Handles the generation of the chunk.
	ChunkGenerator*					_generator;

	/*************** Methods ***************/
public:
	ChunkManager();
	~ChunkManager();
	
	//Pushes the chunk into the lists.
	void							pushChunk(Chunk* chunk);

	//Updates all the lists.
	void							update();

	//Renders _chunkRenderList.
	void							render();

	//Updates the load list.
	void							updateLoadList();

	//Updates the render list.
	void							updateRenderList();
};

#endif