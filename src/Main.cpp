/*******************************************************************************************
 *
 *  Sample Header
 *
 ********************************************************************************************/

#include "raylib.h"
#include "Player.h"
#include "Mob.h"
#include <iostream>
#include <vector>

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
    Player player2(true);
    /*     Mob testZombie; */

    std::vector<Mob *> allEntities; // ? Its a list of pointers to Mob objects not Entities
    allEntities.push_back(&player);
    allEntities.push_back(&player2);
    /*     allEntities.push_back(&testZombie); */

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        player.Update(GetFrameTime(), GetMousePosition(), NULL, allEntities);  // TODO: Use and Implement GetMousePosition() and GetMouseButtonDown()
        player2.Update(GetFrameTime(), GetMousePosition(), NULL, allEntities); // TODO: Use and Implement GetMousePosition() and GetMouseButtonDown()
                                                                               /*         testZombie.Update(GetFrameTime(), player.GetPosition(), player.IsAlive(), allEntities); */
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

        player.Draw();
        player2.Draw();
        /*         testZombie.Draw(); */

        EndMode2D();

        DrawText(TextFormat("Player Velocity; x = %f, %f", player.GetVelocity().x, player.GetVelocity().y), 10, 10, 18, BLACK);
        DrawText(TextFormat("Player Position; x = %f, %f", player.GetPosition().x, player.GetPosition().y), 10, 30, 18, BLACK);
        DrawText(TextFormat("Player State: %s", player.GetState().c_str()), 10, 50, 16, BLACK);

        DrawText(TextFormat("Mob Velocity; x = %f, %f", player2.GetVelocity().x, player2.GetVelocity().y), 10, 70, 18, BLACK);
        DrawText(TextFormat("Mob Position; x = %f, %f", player2.GetPosition().x, player2.GetPosition().y), 10, 90, 18, BLACK);
        DrawText(TextFormat("Mob State: %s", player2.GetState().c_str()), 10, 110, 16, BLACK);

        /*         DrawText(TextFormat("Mob Velocity; x = %f, %f", testZombie.GetVelocity().x, testZombie.GetVelocity().y), 10, 70, 18, BLACK);
                DrawText(TextFormat("Mob Position; x = %f, %f", testZombie.GetPosition().x, testZombie.GetPosition().y), 10, 90, 18, BLACK);
                DrawText(TextFormat("Mob State: %s", testZombie.GetState().c_str()), 10, 110, 16, BLACK); */

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}