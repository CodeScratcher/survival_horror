#include <vector>
#include "item.hpp"
#include "raylib-cpp.hpp"


class Player {
public:
    int hp, stress;
    int x, y;

    std::vector<Item> inventory;

    Player();
};