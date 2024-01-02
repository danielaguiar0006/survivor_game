#include "Player.h"

Player::Player() {
    health = 100;
    maxSpeed = 200.0f; // The actual maximum speed for player movement
    position = { 0.0f, 0.0f };
    velocity = { 0.0f, 0.0f };
    hitBox = { position.x, position.y, 40.0f, 40.0f };
}

void Player::Update(float deltaTime) {
    HandleInput();
    ApplyFriction(); // Apply friction to make movement less slippery
    position = Vector2Add(position, Vector2Scale(velocity, deltaTime)); // Update the position based on velocity
    UpdateHitBox(); // Update the hitbox position to match the player's position
}

void Player::Draw() const {
    DrawRectangleRec(hitBox, GRAY); // Draw the player's hitbox
}

void Player::HandleInput() {
    Vector2 inputVelocity = {0.0f, 0.0f};

    if (IsKeyDown(KEY_W)) inputVelocity.y -= 1.0f;
    if (IsKeyDown(KEY_S)) inputVelocity.y += 1.0f;
    if (IsKeyDown(KEY_A)) inputVelocity.x -= 1.0f;
    if (IsKeyDown(KEY_D)) inputVelocity.x += 1.0f;

    NormalizeAndCapInputVelocity(inputVelocity);

    if (IsKeyDown(KEY_SPACE)) {
        Dash();
    } else {
        velocity = inputVelocity; // Set the player's velocity only if not dashing
    }
}

void Player::Dash() {
    std::cout << "Dashing!" << std::endl;
    float dashSpeed = 1000.0f; // The speed of the dash
    Vector2 dashDirection = {0.0f, 0.0f};

    if (IsKeyDown(KEY_W)) dashDirection.y -= 1.0f;
    if (IsKeyDown(KEY_S)) dashDirection.y += 1.0f;
    if (IsKeyDown(KEY_A)) dashDirection.x -= 1.0f;
    if (IsKeyDown(KEY_D)) dashDirection.x += 1.0f;

    if (Vector2Length(dashDirection) > 0) {
        dashDirection = Vector2Normalize(dashDirection);
        velocity = Vector2Scale(dashDirection, dashSpeed); // Directly set the dash velocity
    }
}


void Player::AddVelocity(Vector2 deltaV) {
    velocity = Vector2Add(velocity, deltaV); // Add the delta velocity to the current velocity
}

void Player::NormalizeAndCapInputVelocity(Vector2 &inputVelocity) {
    if (Vector2Length(inputVelocity) > 0) {
        inputVelocity = Vector2Normalize(inputVelocity); // Normalize the input velocity
        inputVelocity = Vector2Scale(inputVelocity, maxSpeed); // Scale the normalized velocity to max speed
    }
}

Vector2 Player::GetPosition() const {
    return position; // Return the player's current position
}

Vector2 Player::GetVelocity() const {
    return velocity; // Return the player's current velocity
}

void Player::UpdateHitBox() {
    hitBox.x = position.x; // Update the hitbox's X position
    hitBox.y = position.y; // Update the hitbox's Y position
}

void Player::ApplyFriction() {
    float frictionFactor = 0.9f; // Friction factor (adjustable)
    velocity = Vector2Scale(velocity, frictionFactor); // Apply friction to the current velocity
}