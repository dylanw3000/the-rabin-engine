#pragma once
#include "BehaviorNode.h"

class L_CollideCommon : public BaseNode<L_CollideCommon>
{
protected:
    virtual void on_update(float dt);
};