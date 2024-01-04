#include "Player.h"

Player::Player() : currentState(PlayerState::Idle)
{
    isAlive = true;
    health = 100;
    acceleration = 200.0f;
    maxSpeed = 200.0f; // The actual maximum speed for regular player movement
    position = {0.0f, 0.0f};
    velocity = {0.0f, 0.0f};
    hitBox = {position.x, position.y, 40.0f, 40.0f};

    lastDashTimeSec = 0.0f;
    dashCooldownSec = 2.5f;
    dashDurationSec = 1.25f;
    targetDashVelocity = {0.0f, 0.0f};
}

void Player::Update(float deltaTime) // TODO: Implement State Machine
{
    UpdateCooldowns(deltaTime);
    // *std::cout << "Last dash time: " << lastDashTimeSec << std::endl;
    Vector2 inputDirection = HandleInput();

    if (inputDirection.x == 0.0f && inputDirection.y == 0.0f) //! THIS FEELS NAIVE
    {
        SetState(PlayerState::Idle);
    }
    else
    {
        SetState(PlayerState::Walking);
    }

    switch (currentState) // *While in state, do this*
    {
    case PlayerState::Idle:
        /* code */
        break;

    case PlayerState::Walking:
        Vector2 targetVelocity = Vector2Scale(inputDirection, maxSpeed); // Get the target velocity based on the input direction and maximum speed
        ApplyMovement(targetVelocity, deltaTime);
        break;

    case PlayerState::Dashing:
        if (lastDashTimeSec < dashDurationSec) // If the dash duration is not yet over
        {
            lastDashTimeSec += deltaTime; // Update the dash duration
            ApplyMovement(targetDashVelocity, deltaTime);
        }
        else
        {
            SetState(PlayerState::Idle); //? Should it be to Idle or Walking or something else?
        }

        /*     default:
                break; */
    }

    ApplyFriction(deltaTime);                                           // Apply friction to make movement less slippery
    position = Vector2Add(position, Vector2Scale(velocity, deltaTime)); // Update the position based on velocity
    UpdateHitBox();                                                     // Update the hitbox position to match the player's position
}

void Player::Draw() const
{
    DrawRectangleRec(hitBox, GRAY); // Draw the player's hitbox
}

void Player::CheckHealth()
{
    if (health <= 0)
    {
        isAlive = false;
    }
}

std::string Player::GetState() const
{
    switch (currentState)
    {
    case PlayerState::Idle:
        return "Idle";
        break;

    case PlayerState::Walking:
        return "Walking";
        break;

    case PlayerState::Dashing:
        return "Dashing";
        break;

    case PlayerState::Attacking:
        return "Attacking";
        break;

    case PlayerState::Dead:
        return "Dead";
        break;

    default:
        return "Unknown";
        break;
    }
}

int Player::GetHealth() const
{
    return health; // Return the player's current health
}

Vector2 Player::GetPosition() const
{
    return position; // Return the player's current position
}

Vector2 Player::GetVelocity() const
{
    return velocity; // Return the player's current velocity
}

Vector2 Player::GetHitBoxSize() const
{
    return {hitBox.width, hitBox.height}; // Return the player's hitbox size
}

void Player::SetState(PlayerState newState)
{
    currentState = newState; // Set the player's current state
    // *Additional logic for state trnsition, if needed*
}

void Player::UpdateCooldowns(float deltaTime)
{
    if (lastDashTimeSec < dashCooldownSec) // If the dash cooldown is not yet over
    {
        lastDashTimeSec += deltaTime; // Update the dash cooldown}
    }
}

Vector2 Player::HandleInput()
{
    // TODO: Re-Implement dash like in the previous code:
    /*     Vector2 inputVelocity = {0.0f, 0.0f};

        if (!isDashing)
        {
            if (IsKeyDown(KEY_W))
                inputVelocity.y -= 1.0f;
            if (IsKeyDown(KEY_S))
                inputVelocity.y += 1.0f;
            if (IsKeyDown(KEY_A))
                inputVelocity.x -= 1.0f;
            if (IsKeyDown(KEY_D))
                inputVelocity.x += 1.0f;

        if (IsKeyDown(KEY_SPACE) && lastDashTimeSec >= dashCooldownSec)
        {
            Dash();
        }
        else
        {
            velocity = inputVelocity; // Set the player's velocity only if not dashing
        } */

    Vector2 inputDirection = {0.0f, 0.0f};

    if (IsKeyDown(KEY_W))
        inputDirection.y -= 1.0f;
    if (IsKeyDown(KEY_S))
        inputDirection.y += 1.0f;
    if (IsKeyDown(KEY_A))
        inputDirection.x -= 1.0f;
    if (IsKeyDown(KEY_D))
        inputDirection.x += 1.0f;

    if (Vector2Length(inputDirection) > 0)
    {
        inputDirection = Vector2Normalize(inputDirection);

        if (IsKeyDown(KEY_SPACE) && lastDashTimeSec >= dashCooldownSec)
        {
            Dash(inputDirection);
        }

        return inputDirection;
    }
    else
    {
        return {0.0f, 0.0f};
    }
}

void Player::ApplyMovement(Vector2 targetVelocity, float deltaTime)
{
    velocity.x = Approach(velocity.x, targetVelocity.x, (acceleration * deltaTime) * 10.0f); // Apply acceleration to the X velocity
    velocity.y = Approach(velocity.y, targetVelocity.y, (acceleration * deltaTime) * 10.0f); // Apply acceleration to the Y velocity
}

void Player::ApplyFriction(float deltaTime)
{
    float frictionFactor = 69.69f;                                                 // Friction factor (adjustable)
    velocity.x = Approach(velocity.x, 0.0f, (frictionFactor * deltaTime) * 10.0f); // Apply friction to the X velocity
    velocity.y = Approach(velocity.y, 0.0f, (frictionFactor * deltaTime) * 10.0f); // Apply friction to the Y velocity
}

void Player::Dash(Vector2 inputDirection) // TODO: Fix the dash and currently there is friction being applied while dashing
{
    SetState(PlayerState::Dashing); // Set the player's state to dashing
    lastDashTimeSec = 0.0f;         // Reset the dash cooldown

    float dashSpeed = 1000.0f;                                    // The speed of the dash
    targetDashVelocity = Vector2Scale(inputDirection, dashSpeed); // Set the dash velocity to the input direction multiplied by the dash speed
}

float Player::Approach(float current, float target, float maxDelta)
{
    float delta = target - current; // Get the difference between the current and target values
    if (delta > maxDelta)           // If the difference is greater than the maximum delta
        delta = maxDelta;           // Set the difference to the maximum delta
    if (delta < -maxDelta)          // If the difference is less than the negative maximum delta
        delta = -maxDelta;          // Set the difference to the negative maximum delta
    return current + delta;         // Return the current value plus the difference
}

void Player::UpdateHitBox()
{
    hitBox.x = position.x; // Update the hitbox's X position
    hitBox.y = position.y; // Update the hitbox's Y position
}
