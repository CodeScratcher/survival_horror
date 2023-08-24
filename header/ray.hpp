#pragma once
#include "raylib.h"
#include "world.hpp"
const float RAY_DENSITY = 20.0f;
const float MAX_ANGLE = 10.0f;
const float MAX_DISTANCE = 300.0f;
const float MIN_DISTANCE = 64.0f;
void shoot(Player& player, World& world, Vector2 src, Vector2 dest);
bool visible(World world, Vector2 src, Vector2 dest, Vector2 mouse, Camera2D camera);
