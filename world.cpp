#include "world.hpp"

World::World() {
	walls = std::map<std::pair<int, int>, bool>();
}

bool exists_and_true(std::map<std::pair<int, int>, bool> map, std::pair<int, int> key) {
	return map.count(key) && map.at(key);
}
