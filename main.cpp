#include "raylib.h"
#include "player.hpp"
#include "world.hpp"
#include "ray.hpp"
#include <iostream>

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1280;
    int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Survival Horror Game");
    
    Player player = Player();
    World world = World();
    
    Camera2D camera = { 0 };
    camera.target = (Vector2){(float)player.x + SIZE / 2, (float)player.y + SIZE / 2};
    camera.offset = (Vector2){screenWidth/2.0f, screenHeight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 4.0f;
    
    world.walls.insert({std::make_pair(3, 5), true});
    world.walls.insert({std::make_pair(4, 5), true});
    world.walls.insert({std::make_pair(3, 4), true});
    
    world.enemies.push_back(Enemy(64, 64));
    
    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        if (IsKeyDown(KEY_LEFT)) {
            player.x -= 5;
            if (player.collides(world)) {
				player.x = (player.x + TILE_SIZE) / TILE_SIZE * TILE_SIZE;
			}
        }
        if (IsKeyDown(KEY_RIGHT)) {
            player.x += 5;
            if (player.collides(world)) {
				player.x = player.x / TILE_SIZE * TILE_SIZE;
			}
        }
        if (IsKeyDown(KEY_UP)) {
            player.y -= 5;
            if (player.collides(world)) {
				player.y = (player.y + TILE_SIZE) / TILE_SIZE * TILE_SIZE;
			}
        }
        if (IsKeyDown(KEY_DOWN)) {
            player.y += 5;
            if (player.collides(world)) {
				player.y = player.y / TILE_SIZE * TILE_SIZE;
			}
        }
  
        for (Enemy& i : world.enemies) {
			i.update(player, world);
		}
        camera.target = (Vector2){(float)player.x + SIZE / 2, (float)player.y + SIZE / 2};
		
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && player.cooldown < 0) {
			Vector2 pos = GetScreenToWorld2D(GetMousePosition(), camera);
			shoot(player, world, Vector2 {(float)player.x + SIZE / 2, (float)player.y + SIZE / 2}, pos);
		}
		
		std::cout << player.cooldown << "\n";
		player.iframes -= 1;
		player.cooldown -= 1;

        Vector2 playerScreen = GetWorldToScreen2D(Vector2 {(float)player.x + SIZE / 2, (float)player.y + SIZE / 2}, camera);
        
		
		for (Enemy enemy : world.enemies) {
            Vector2 enemyScreen = GetWorldToScreen2D(Vector2 {(float)enemy.x + ENEMY_SIZE / 2, (float)enemy.y + ENEMY_SIZE / 2}, camera);
            if (visible(world, playerScreen, enemyScreen, camera)) {
                player.stress -= 5.0f / 60.0f;
                std::cout << "STRESS: " << player.stress << "\n";
            }
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        {
			BeginMode2D(camera);
			{
				ClearBackground(RAYWHITE);
				
				DrawRectangle(player.x, player.y, SIZE, SIZE, BLACK);
				
				for (const auto &walls : world.walls) {
					if (walls.second) {
						std::pair<int, int> coords = walls.first;
						DrawRectangle(coords.first * TILE_SIZE, coords.second * TILE_SIZE, TILE_SIZE, TILE_SIZE, RED);
					}
				}
				
				for (Enemy i : world.enemies) {
					DrawRectangle(i.x, i.y, SIZE, SIZE, GREEN);
				}
			}
			EndMode2D();
            
            for (int x = playerScreen.x - MAX_DISTANCE; x < playerScreen.x + MAX_DISTANCE; x += 8) {
                for (int y = playerScreen.y - MAX_DISTANCE; y < playerScreen.y + MAX_DISTANCE; y += 8) {
                    if (!visible(world, 
                            playerScreen, 
                            Vector2 {(float)x, (float)y}, 
                            camera)) {
                        DrawRectangle(x, y, 8, 8, BLACK);
                    }
                }
            }
            DrawRectangle(0, 0, screenWidth, playerScreen.y - MAX_DISTANCE, BLACK);
            DrawRectangle(0, playerScreen.y + MAX_DISTANCE, screenWidth, screenHeight, BLACK);
            DrawRectangle(0, 0, playerScreen.x - MAX_DISTANCE, screenHeight, BLACK);
            DrawRectangle(playerScreen.x + MAX_DISTANCE, 0, screenWidth, screenHeight, BLACK);
            
            DrawRectangle(0, 0, 300, 50, RAYWHITE);
            DrawRectangle(0, 0, player.hp * 3, 50, GREEN);

            DrawRectangle(0, 75, 300, 50, RAYWHITE);
            DrawRectangle(0, 75, (int)player.stress * 3, 50, BLUE);
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    return 0;
}
