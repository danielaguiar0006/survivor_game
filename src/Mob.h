#ifndef MOB_H
#define MOB_H

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <vector>

class Mob
{
public:
    enum class MobState
    {
        Idle,
        Walking,
        Attacking,
        Dead
    };

    Mob();
    virtual ~Mob();

    virtual void Update(float deltaTime, Vector2 targetPosition, bool isTargetAlive, std::vector<Mob *> allEntities);
    virtual void Draw() const;

    std::string GetState() const;
    bool IsAlive() const;
    int GetHealth() const;
    Vector2 GetPosition() const;
    Vector2 GetVelocity() const;
    Rectangle GetHitBox() const;
    Vector2 GetHitBoxSize() const; // ? After introducing GetHitBox() this may no longer be needed

protected:
    MobState currentState;
    bool isAlive;
    int health;
    bool isHostile; // ? Should this be a State
    float aggroRange;
    float attackRange;
    float walkAcceleration;
    float maxSpeed;
    Vector2 position;
    Vector2 velocity;
    float hitBoxWidth;
    float hitBoxHeight;
    Rectangle hitBox;

    virtual void SetState(MobState newState);
    void CheckHealth();
    virtual void UpdateCooldowns(float deltaTime);
    void ApplyMovement(Vector2 inputDirection, float acceleration, float deltaTime);
    void ApplyFriction(float deltaTime);
    float Approach(float current, float target, float maxDelta);
    bool IsWithinRange(Vector2 targetPosition, float range) const;
    void UpdateHitBox();
    void CheckCollision(Vector2 oldPosition, std::vector<Mob *> allEntities);
};

#endif // MOB_H