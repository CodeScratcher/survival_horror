#include "raylib.h"
#include "player.hpp"

int main() {
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1280;
    int screenHeight = 720;
    InitWindow(screenWidth, screenHeight, "Survival Horror Game");
    
    Player player = Player();

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {   // Detect window close button or ESC key
        if (IsKeyDown(KEY_LEFT)) {
            player.x -= 5;
        }
        if (IsKeyDown(KEY_RIGHT)) {
            player.x += 5;
        }
        if (IsKeyDown(KEY_UP)) {
            player.y -= 5;
        }
        if (IsKeyDown(KEY_DOWN)) {
            player.y += 5;
        }

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        {
            ClearBackground(RAYWHITE);
            
            DrawRectangle(player.x, player.y, 100, 100, BLACK);
        }
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    return 0;
}
