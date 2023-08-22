#pragma once

class Player;   
class World;
const int ENEMY_SIZE = 16;

class Enemy {
public:
    int hp;
    int x;
    int y;
    
    Enemy(int x, int y);
    void update(Player& player, World world);
    bool collides(World world);
};
