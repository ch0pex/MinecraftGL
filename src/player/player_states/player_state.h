#pragma once 

enum class PlayerStateType {
	kGround,
	kAir,
	kDead,
};

class PlayerState {
public:
    virtual ~PlayerState() {}
    virtual void update() = 0;
};
