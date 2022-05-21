#pragma once
#include "BehaviorNode.h"

class L_CollideTower : public BaseNode<L_CollideTower>
{
protected:
    virtual void on_update(float dt);
};