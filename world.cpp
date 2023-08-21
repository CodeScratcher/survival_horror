#include "world.hpp"
World::World() {
	walls = std::map<std::pair<int, int>, bool>();
}
