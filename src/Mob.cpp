#include "Mob.h"

Mob::Mob() : currentState(MobState::Idle)
{
    isAlive = true;
    health = 100;
    isHostile = true; // Default aggro state
    aggroRange = 400.0f;
    attackRange = 50.0f;
    walkAcceleration = 200.0f;
    maxSpeed = 200.0f; // The actual maximum speed for regular mob movement
    position = {0.0f, 0.0f};
    velocity = {0.0f, 0.0f};
    hitBoxWidth = 40.0f;
    hitBoxHeight = 40.0f;
    hitBox = {position.x - (hitBox.width / 2), position.y - (hitBox.height / 2), hitBoxWidth, hitBoxWidth}; // Origin of the hitbox is the center of the hitbox
}

Mob::~Mob() // TODO: Add a destructor
{
    // Cleanup code here
    // Example: If Player had dynamically allocated memory or loaded textures
    // delete myPointer;
    // UnloadTexture(myTexture);
}

void Mob::Update(float deltaTime, Vector2 targetPosition, bool isTargetAlive)
{
    UpdateCooldowns(deltaTime);

    switch (currentState)
    {
    case MobState::Idle:
        if (isTargetAlive && IsWithinRange(targetPosition, aggroRange))
        {
            SetState(MobState::Walking);
        }
        break;

    case MobState::Walking:
        if (!isTargetAlive)
        {
            SetState(MobState::Idle);
            break;
        }

        if (IsWithinRange(targetPosition, attackRange))
        {
            SetState(MobState::Attacking);
            break;
        }
        else
        {
            Vector2 targetVelocity = Vector2Scale(Vector2Normalize(Vector2Subtract(targetPosition, position)), maxSpeed); // Get the target velocity based on the input direction and maximum speed
            if (Vector2Length(targetVelocity) >= Vector2Length(velocity))                                                 // To prevent friction and walking acceleration prematurly slowing down the player
            {
                ApplyMovement(targetVelocity, walkAcceleration, deltaTime);
            }
        }
        break;
    case MobState::Attacking:
        if (!isTargetAlive)
        {
            SetState(MobState::Idle);
            break;
        }
        if (!IsWithinRange(targetPosition, attackRange)) // TODO: Add a check for if the target is within attack range ie: attackRange
        {
            SetState(MobState::Walking);
            break;
        }
        break;

        // TODO: Add remaining states
        /*     default:
                break; */
    }

    ApplyFriction(deltaTime);                                           // Apply friction to make movement less slippery
    position = Vector2Add(position, Vector2Scale(velocity, deltaTime)); // Update the position based on velocity
    UpdateHitBox();                                                     // Update the hitbox position to match the player's position
}

void Mob::Draw() const
{
    if (isHostile)
        DrawRectangleRec(hitBox, RED); // Draw the player's hitbox
    else
        DrawRectangleRec(hitBox, GREEN); // Draw the player's hitbox

    DrawRectangleLinesEx(hitBox, 1, BLACK);

    DrawCircleV(position, aggroRange, Fade(RED, 0.1f));
    DrawCircleV(position, attackRange, Fade(RED, 0.1f));
}

std::string Mob::GetState() const
{
    switch (currentState)
    {
    case MobState::Idle:
        return "Idle";

    case MobState::Walking:
        return "Walking";

    case MobState::Attacking:
        return "Attacking";

    case MobState::Dead:
        return "Dead";

    default:
        return "Unknown";
    }
}

bool Mob::IsAlive() const
{
    return isAlive; // Return whether or not the player is alive
}

int Mob::GetHealth() const
{
    return health; // Return the player's current health
}

Vector2 Mob::GetPosition() const
{
    return position; // Return the player's current position
}

Vector2 Mob::GetVelocity() const
{
    return velocity; // Return the player's current velocity
}

Vector2 Mob::GetHitBoxSize() const
{
    return {hitBox.width, hitBox.height}; // Return the player's hitbox size
}

void Mob::SetState(MobState newState)
{
    currentState = newState; // Set the player's current state
    // *Additional logic for state trnsition, if needed*
}

void Mob::CheckHealth()
{
    if (health <= 0)
    {
        isAlive = false;
    }
}

void Mob::UpdateCooldowns(float deltaTime)
{
    // Attack cooldowns
}

void Mob::ApplyMovement(Vector2 targetVelocity, float acceleration, float deltaTime)
{
    velocity.x = Approach(velocity.x, targetVelocity.x, (acceleration * deltaTime) * 10.0f); // Apply acceleration to the X velocity
    velocity.y = Approach(velocity.y, targetVelocity.y, (acceleration * deltaTime) * 10.0f); // Apply acceleration to the Y velocity
}

void Mob::ApplyFriction(float deltaTime)
{
    float frictionAdjustment = 100.0f;                                                 // Friction Adjustment (adjustable)
    velocity.x = Approach(velocity.x, 0.0f, (frictionAdjustment * deltaTime) * 10.0f); // Apply friction to the X velocity
    velocity.y = Approach(velocity.y, 0.0f, (frictionAdjustment * deltaTime) * 10.0f); // Apply friction to the Y velocity
}

float Mob::Approach(float current, float target, float maxDelta)
{
    float delta = target - current; // Get the difference between the current and target values
    if (delta > maxDelta)           // If the difference is greater than the maximum delta
        delta = maxDelta;           // Set the difference to the maximum delta
    if (delta < -maxDelta)          // If the difference is less than the negative maximum delta
        delta = -maxDelta;          // Set the difference to the negative maximum delta
    return current + delta;         // Return the current value plus the difference
}

bool Mob::IsWithinRange(Vector2 targetPosition, float range) const
{
    float distanceToTarget = Vector2Distance(position, targetPosition);
    if (distanceToTarget <= range)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Mob::UpdateHitBox()
{
    hitBox.x = position.x - (hitBox.width / 2);  // Update the hitbox's X position
    hitBox.y = position.y - (hitBox.height / 2); // Update the hitbox's Y position
}
