#include "World.h"

World::World() {
	sprintf(_name, "Default");
	_chunkManager = new ChunkManager();
	_player = new Player(glm::vec3(0, 30, 0));
}

World::World(char* name) {
	sprintf(_name, name);
	_chunkManager = new ChunkManager();
	_player = new Player(glm::vec3(0, 0, 0));
}

World::~World() {
	delete _chunkManager;
	delete _player;
}

void World::generateWorld(Program* program) {	
	for (int x(0); x!=3; ++x) {
		for (int y(0); y!=1; ++y) {
			for (int z(0); z!=3; ++z) {
				_chunkManager->pushChunk(new Chunk(program, glm::vec3(x, y, z), _chunkManager));
			}
		}
	}
}

void World::update(float secondsElapsed) {
	_chunkManager->update();
	_player->update(secondsElapsed);
}

void World::render() {
	_chunkManager->render();
	_player->render();
}