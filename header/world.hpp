#include <map>
#include <utility>
#pragma once
const int TILE_SIZE = 16;

class World {
public:
	std::map<std::pair<int, int>, bool> walls;
	
	World();
};
