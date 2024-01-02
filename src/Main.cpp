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
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Camera2D camera = { 0 };
    camera.target = { 0.0f, 0.0f };
    camera.offset = { 0.0f, 0.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
    //camera.offset = { screenWidth / 2.0f, screenHeight / 2.0f };

    Player player; // Create an instance of the Player class
    //camera.target = player.GetPosition();

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //std::cout << "Player position: " << player.GetPosition().x << ", " << player.GetPosition().y << std::endl;
        std::cout << "Player velocity: " << player.GetVelocity().x << ", " << player.GetVelocity().y << std::endl;    
        player.Update(GetFrameTime()); // Update the player instance
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode2D(camera);
                player.Draw(); // Draw the player instance
                DrawRectangle(0, 0, 10, 10, RED);
            EndMode2D();

            //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}