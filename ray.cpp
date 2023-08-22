#include "ray.hpp"
#include "raymath.h"
#include "enemy.hpp"
#include "player.hpp"
#include <iostream>

void shoot(Player& player, World& world, Vector2 src, Vector2 dest) {
    for (int i = 0; i < (int)RAY_DENSITY; i++) {
        Vector2 pos = Vector2Lerp(src, dest, (float)i / RAY_DENSITY);
        if (exists_and_true(world.walls, std::make_pair((int)pos.x / TILE_SIZE, (int)pos.y / TILE_SIZE))) {
            std::cout << "Wall collision \n";
            player.cooldown = 60;
            return;
        }
        for (int j = 0; j < world.enemies.size(); j++) {
            Enemy enemy = world.enemies.at(j);
            if (CheckCollisionPointRec(pos, Rectangle {enemy.x, enemy.y, ENEMY_SIZE, ENEMY_SIZE})) {
                world.enemies.at(j).hp -= 20;
                std::cout << "Enemy HP: " << enemy.hp << "\n";
                if (world.enemies.at(j).hp <= 0) {
                    world.enemies.erase(world.enemies.begin() + j);
                }
                player.cooldown = 60;
                return;
            }
        }
    }
}

