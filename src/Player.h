#ifndef PLAYER_H
#define PLAYER_H

#include "Mob.h"
class Player : public Mob
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
    bool testFlag;

    Player(bool testFlag = false);
    virtual ~Player();

    void Update(float deltaTime, Vector2 targetPosition, bool isTargetAlive, std::vector<Mob *> allEntities) override;
    void Draw() const override;

    std::string GetState() const; //? Not sure why its not 'override'

private:
    PlayerState currentState;
    float dashAcceleration;
    float lastDashTimeSec;
    float dashCooldownSec;
    float dashDurationSec;
    Vector2 targetDashVelocity;

    void SetState(PlayerState newState);
    void UpdateCooldowns(float deltaTime) override;
    Vector2 HandleInput();
    void Dash(Vector2 inputDirection);
};

#endif // PLAYER_H