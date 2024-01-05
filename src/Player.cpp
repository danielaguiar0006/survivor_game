#include "Player.h"

Player::Player() : Mob(), currentState(PlayerState::Idle)
{
    isAlive = true;
    health = 100;
    isHostile = NULL;
    aggroRange = NULL;
    attackRange = 50.0f;
    walkAcceleration = 200.0f;
    maxSpeed = 200.0f; // The actual maximum speed for regular player movement
    position = {0.0f, 0.0f};
    velocity = {0.0f, 0.0f};
    hitBoxWidth = 40.0f;
    hitBoxHeight = 40.0f;
    hitBox = {position.x - (hitBox.width / 2), position.y - (hitBox.height / 2), hitBoxWidth, hitBoxWidth}; // Origin of the hitbox is the center of the hitbox

    lastDashTimeSec = 0.0f;
    dashCooldownSec = 1.0f;
    dashDurationSec = 0.25f;
    dashAcceleration = 600.0f;
    targetDashVelocity = {0.0f, 0.0f};
}

Player::~Player() // TODO: Add a destructor
{
    // Cleanup code here
    // Example: If Player had dynamically allocated memory or loaded textures
    // delete myPointer;
    // UnloadTexture(myTexture);
}

void Player::Update(float deltaTime, Vector2 targetPosition, bool isTargetAlive) // ? No use for tergetPosition and isTargetAlive
{
    UpdateCooldowns(deltaTime);

    Vector2 inputDirection = HandleInput();

    switch (currentState) // *While in state, do this*
    {
    case PlayerState::Idle:
        if (inputDirection.x != 0.0f || inputDirection.y != 0.0f)
        {
            SetState(PlayerState::Walking);
        }
        break;

    case PlayerState::Walking:
        if (inputDirection.x == 0.0f && inputDirection.y == 0.0f)
        {
            SetState(PlayerState::Idle);
            break;
        }

        Vector2 targetVelocity = Vector2Scale(inputDirection, maxSpeed); // Get the target velocity based on the input direction and maximum speed
        if (Vector2Length(targetVelocity) >= Vector2Length(velocity))    // To prevent friction and walking acceleration prematurly slowing down the player
        {
            ApplyMovement(targetVelocity, walkAcceleration, deltaTime);
        }
        break;

    case PlayerState::Dashing:
        if (lastDashTimeSec < dashDurationSec) // If the dash duration is not yet over
        {
            ApplyMovement(targetDashVelocity, dashAcceleration, deltaTime);
        }
        else
        {
            SetState(PlayerState::Idle); //? Should it be to Idle or Walking or something else?
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

void Player::Draw() const
{
    DrawRectangleRec(hitBox, GRAY); // Draw the player's hitbox
}

std::string Player::GetState() const
{
    switch (currentState)
    {
    case PlayerState::Idle:
        return "Idle";

    case PlayerState::Walking:
        return "Walking";

    case PlayerState::Dashing:
        return "Dashing";

    case PlayerState::Attacking:
        return "Attacking";

    case PlayerState::Dead:
        return "Dead";

    default:
        return "Unknown";
    }
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

void Player::Dash(Vector2 inputDirection)
{
    SetState(PlayerState::Dashing); // Set the player's state to dashing
    lastDashTimeSec = 0.0f;         // Reset the dash cooldown

    float dashSpeed = 600.0f;                                     // The speed of the dash
    targetDashVelocity = Vector2Scale(inputDirection, dashSpeed); // Set the dash velocity to the input direction multiplied by the dash speed
}
