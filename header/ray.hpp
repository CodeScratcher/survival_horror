#pragma once
#include "raylib.h"
#include "world.hpp"
const float RAY_DENSITY = 50.0f;
void shoot(Player& player, World& world, Vector2 src, Vector2 dest);
