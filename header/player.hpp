#pragma once
#include <vector>
#include "item.hpp"
#include "world.hpp"
#include "raylib-cpp.hpp"

const int SIZE = 16;

class Player {
public:
    int hp;
    float stress;
    int x, y;
    int iframes, cooldown;

    std::vector<Item> inventory;

    Player();
    bool collides(World world);
};
