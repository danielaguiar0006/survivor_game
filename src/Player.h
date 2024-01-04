#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "raymath.h"
#include <iostream>

class Player
{
public:
    enum class PlayerState //? Should this be public?
    {
        Idle,
        Walking,
        Dashing,
        Attacking,
        Dead
    };

    Player();
    //? virtual ~Player();

    void Update(float deltaTime);
    void Draw() const;

    void CheckHealth(); //? Should this be private?

    std::string GetState() const;
    int GetHealth() const;
    Vector2 GetPosition() const;
    Vector2 GetVelocity() const;
    Vector2 GetHitBoxSize() const;

private:
    PlayerState currentState;
    bool isAlive;
    int health;
    float acceleration;
    float maxSpeed;
    Vector2 position;
    Vector2 velocity;
    Rectangle hitBox;

    float lastDashTimeSec;
    float dashCooldownSec;
    float dashDurationSec;
    Vector2 targetDashVelocity;

    void SetState(PlayerState newState);
    void UpdateCooldowns(float deltaTime);
    Vector2 HandleInput();
    void ApplyMovement(Vector2 inputDirection, float deltaTime);
    void ApplyFriction(float deltaTime);
    void Dash(Vector2 inputDirection);
    float Approach(float current, float target, float maxDelta);
    void UpdateHitBox();
};

#endif // PLAYER_H