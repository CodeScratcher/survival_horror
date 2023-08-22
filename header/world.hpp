#include <map>
#include <utility>
#include <vector>
#include "enemy.hpp"
#pragma once
const int TILE_SIZE = 16;


class World {
public:
	std::map<std::pair<int, int>, bool> walls;
	
	std::vector<Enemy> enemies;
	
	World();
};

bool exists_and_true(std::map<std::pair<int, int>, bool> map, std::pair<int, int> key);
