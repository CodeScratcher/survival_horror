#include "player.hpp"


Player::Player() {
    x = 0;
    y = 0;
    hp = 100;
    stress = 100;
    iframes = 5;
    cooldown = 0;
}


bool Player::collides(World world) {
	std::map<std::pair<int, int>, bool> walls = world.walls;
	return exists_and_true(walls, std::make_pair(x / TILE_SIZE, y / TILE_SIZE)) ||
		exists_and_true(walls, std::make_pair((x + SIZE - 1) / TILE_SIZE, y / TILE_SIZE)) ||
		exists_and_true(walls, std::make_pair(x / TILE_SIZE, (y + SIZE - 1) / TILE_SIZE)) ||
		exists_and_true(walls, std::make_pair((x + SIZE - 1) / TILE_SIZE, (y + SIZE - 1) / TILE_SIZE));
}
