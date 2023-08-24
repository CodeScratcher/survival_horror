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
            if (CheckCollisionPointRec(pos, Rectangle {(float)enemy.x, (float)enemy.y, ENEMY_SIZE, ENEMY_SIZE})) {
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
    player.cooldown = 60;
}

bool visible(World world, Vector2 src, Vector2 dest, Vector2 mouse, Camera2D camera) {
    Vector2 direction1 = Vector2Subtract(dest, src);
    Vector2 direction2 = Vector2Subtract(mouse, src);

    direction1 = Vector2Normalize(direction1);
    direction2 = Vector2Normalize(direction2);

    float dotProduct = Vector2DotProduct(direction1, direction2);
    
    dotProduct = fmaxf(-1.0f, fminf(1.0f, dotProduct));

    float angleRad = acosf(dotProduct);

    // Convert radians to degrees
    float angleDeg = angleRad * (180.0f / PI);
    
    if (Vector2Distance(src, dest) > MIN_DISTANCE && angleDeg > MAX_ANGLE) return false;
    if (Vector2Distance(src, dest) > MAX_DISTANCE) return false;
    for (int i = 0; i < (int)RAY_DENSITY; i++) {
        Vector2 pos = GetScreenToWorld2D(Vector2Lerp(src, dest, (float)i / RAY_DENSITY), camera);
        if (exists_and_true(world.walls, std::make_pair((int)pos.x / TILE_SIZE, (int)pos.y / TILE_SIZE))) {
            return false;
        }
    }
    return true;
}


