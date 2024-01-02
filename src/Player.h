#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "raymath.h"
#include <iostream>

class Player {
public:
    Player();
    //? virtual ~Player();

    void Update(float deltaTime);
    void Draw() const;
    
    void AddVelocity(Vector2 deltaV);
    
    void CheckHealth();

    int GetHealth() const;
    bool IsAlive() const;
    Vector2 GetPosition() const;
    Vector2 GetVelocity() const;
    Vector2 GetHitBoxSize() const;
private:
    int health;
    bool isAlive;
    float maxSpeed;
    Vector2 position;
    Vector2 velocity;
    Rectangle hitBox;

    void HandleInput();
    void UpdateHitBox();
    void NormalizeAndCapInputVelocity(Vector2 &inputVelocity);
    void ApplyFriction();
    void Dash();
};

#endif // PLAYER_H