#pragma once
#include "BehaviorNode.h"

class L_CollidePredator : public BaseNode<L_CollidePredator>
{
protected:
    virtual void on_update(float dt);
};