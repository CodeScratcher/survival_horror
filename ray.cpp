#include "ray.hpp"
#include "raymath.h"
#include <iostream>

void shoot(World world, Vector2 src, Vector2 dest) {
    for (int i = 0; i < (int)RAY_DENSITY; i++) {
        Vector2 pos = Vector2Lerp(src, dest, (float)i / RAY_DENSITY);
        if (exists_and_true(world.walls, std::make_pair((int)pos.x / TILE_SIZE, (int)pos.y / TILE_SIZE))) {
            std::cout << "Wall collision \n";
        }
    }
}

