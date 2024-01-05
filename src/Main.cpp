/*******************************************************************************************
 *
 *  Sample Header
 *
 ********************************************************************************************/

#include "raylib.h"
#include "Player.h"
#include "Mob.h"
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
    Mob testZombie;

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        player.Update(GetFrameTime(), GetMousePosition(), NULL); // TODO: Use and Implement GetMousePosition() and GetMouseButtonDown()
        testZombie.Update(GetFrameTime(), player.GetPosition(), player.IsAlive());
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

        player.Draw();
        testZombie.Draw();

        EndMode2D();

        DrawText(TextFormat("Player Velocity; x = %f, %f", player.GetVelocity().x, player.GetVelocity().y), 10, 10, 18, BLACK);
        DrawText(TextFormat("Player Position; x = %f, %f", player.GetPosition().x, player.GetPosition().y), 10, 30, 18, BLACK);
        DrawText(TextFormat("Player State: %s", player.GetState().c_str()), 10, 50, 16, BLACK);

        DrawText(TextFormat("Mob Velocity; x = %f, %f", testZombie.GetVelocity().x, testZombie.GetVelocity().y), 10, 70, 18, BLACK);
        DrawText(TextFormat("Mob Position; x = %f, %f", testZombie.GetPosition().x, testZombie.GetPosition().y), 10, 90, 18, BLACK);
        DrawText(TextFormat("Mob State: %s", testZombie.GetState().c_str()), 10, 110, 16, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}