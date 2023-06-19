#pragma once
#include "../rendering/Camera.h"

enum class GameStateType;

class Player
{
public:
    Player();
    ~Player();
    
    Camera camera;
    void update();

    void setActive(bool _active);
    bool isActive() const;
    
private:
    bool active;
    
};
