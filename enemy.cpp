#include <iostream>
#include "world.hpp"
#include "player.hpp"
#include "raylib.h"

Enemy::Enemy(int x, int y) {
    this->x = x;
    this->y = y;
    this->hp = 100;
}

void Enemy::update(Player& player, World world) {
    if (player.x < x) {
        x -= 1;
        if (collides(world)) {
            x = (x + TILE_SIZE) / TILE_SIZE * TILE_SIZE;
        }
    }
    if (player.x > x) {
        x += 1;
        if (collides(world)) {
            x = x / TILE_SIZE * TILE_SIZE;
        }
    }
    if (player.y < y) {
        y -= 1;
        if (collides(world)) {
            y = (y + TILE_SIZE) / TILE_SIZE * TILE_SIZE;
        }
    }
    if (player.y > y) {
        y += 1;
        if (collides(world)) {
            y = y / TILE_SIZE * TILE_SIZE;
        }
    }
    
    if (CheckCollisionRecs(Rectangle {player.x, player.y, SIZE, SIZE}, Rectangle {x, y, ENEMY_SIZE, ENEMY_SIZE}) && player.iframes < 0) {
        player.hp -= 5;
        player.iframes = 5;
        std::cout << player.hp << " HP \n";
    }
}

bool Enemy::collides(World world) {
	std::map<std::pair<int, int>, bool> walls = world.walls;
	return exists_and_true(walls, std::make_pair(x / TILE_SIZE, y / TILE_SIZE)) ||
		exists_and_true(walls, std::make_pair((x + ENEMY_SIZE - 1) / TILE_SIZE, y / TILE_SIZE)) ||
		exists_and_true(walls, std::make_pair(x / TILE_SIZE, (y + ENEMY_SIZE - 1) / TILE_SIZE)) ||
		exists_and_true(walls, std::make_pair((x + ENEMY_SIZE - 1) / TILE_SIZE, (y + ENEMY_SIZE - 1) / TILE_SIZE));
}
