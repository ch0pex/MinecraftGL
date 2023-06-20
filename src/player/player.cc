#include "player.h"

Player::Player() : camera_(45.0f, 1920, 1080, .1f, 1000.0f, glm::vec3(0.0f, 75.0f, 6.0f)) {
    active_ = true;
}

Player::~Player() {

}

void Player::Update() {
    while (active_)
        camera_.Update();
}

void Player::SetActive(bool active) {
    active = active;
}

bool Player::IsActive() const {
    return active_;
}
