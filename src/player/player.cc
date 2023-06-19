#include "player.h"

Player::Player() : camera(45.0f, 1920, 1080, .1f, 1000.0f, glm::vec3(0.0f, 75.0f, 6.0f))
{
    active = true;
}

Player::~Player()
{
    
}

void Player::update()
{
    while(active)
        camera.update();
}

void Player::setActive(bool _active)
{
    active = _active;
}

bool Player::isActive() const
{
    return active;
}
