/*******************************************************************************************
 *
 *
 *
 ********************************************************************************************/

#include "raylib.h"
#include "Player.h"
#include <iostream>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);

    Camera2D camera = {0};
    camera.target = {0.0f, 0.0f};
    camera.offset = {0.0f, 0.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    // camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };

    Player player;

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        player.Update(GetFrameTime());
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

        player.Draw();

        EndMode2D();

        DrawText(TextFormat("Player Velocity; x = %f, %f", player.GetVelocity().x, player.GetVelocity().y), 10, 10, 18, BLACK);
        DrawText(TextFormat("Player Position; x = %f, %f", player.GetPosition().x, player.GetPosition().y), 10, 30, 18, BLACK);
        DrawText(TextFormat("Player State: %s", player.GetState().c_str()), 10, 50, 16, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}