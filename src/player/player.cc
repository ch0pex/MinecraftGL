#include "player.h"
#include <ostream>

Player::Player() : 
	camera_(45.0f, 1920, 1080, .1f, 1000.0f, glm::vec3(0.0f, 75.0f, 6.0f)),
	currentState_(PlayerStateType::kGround),
	controlsEnabled_(true)
{

}

Player::~Player() 
{

}

void Player::Update() 
{
    while (controlsEnabled_)
        camera_.Update();
}

void Player::ChangeState(PlayerStateType state) 
{
	currentState_ = state;
}

PlayerStateType Player::GetState() 
{
	return currentState_;
}

