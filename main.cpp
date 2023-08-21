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
    camera.target = (Vector2){player.x, player.y};
    camera.offset = (Vector2){screenWidth/2.0f, screenHeight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 2.0f;
    
    world.walls.insert({std::make_pair(3, 5), true});
    
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
  
        
        camera.target = (Vector2){player.x, player.y};
		
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			Vector2 pos = GetScreenToWorld2D(GetMousePosition(), camera);
			shoot(world, Vector2 {player.x + SIZE / 2, player.y + SIZE / 2}, pos);
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
			}
			EndMode2D();

        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    return 0;
}
