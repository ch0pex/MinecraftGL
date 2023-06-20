#pragma once

#include "../rendering/camera.h"

enum class GameStateType;

class Player {
public:
    Player();
    ~Player();

    Camera camera_;
    void Update();

    void SetActive(bool active);
    bool IsActive() const;

private:
    bool active_;

};
