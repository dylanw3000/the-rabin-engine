#pragma once
#include "BehaviorNode.h"

class L_Float : public BaseNode<L_Float>
{
protected:
    float timer;

    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};