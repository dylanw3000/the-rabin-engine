#pragma once
#include "BehaviorNode.h"

class L_MoveToClosestVictim : public BaseNode<L_MoveToClosestVictim>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Agent* target;
    float pursuitSpeed;
};