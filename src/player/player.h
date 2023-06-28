#pragma once

#include "../rendering/camera.h"
#include "player_states/player_state.h"
#include <unordered_map>
enum class GameStateType;

class Player {
public:
    Player();
    ~Player();

    Camera camera_;
    void Update();
    void ChangeState(PlayerStateType state);
    PlayerStateType GetState(); 

private:
    PlayerStateType currentState_;
    std::unordered_map<PlayerStateType, PlayerState*> states_;
    bool controlsEnabled_;
};
