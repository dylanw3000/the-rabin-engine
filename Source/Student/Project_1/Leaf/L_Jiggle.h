#pragma once
#include "BehaviorNode.h"

class L_Jiggle : public BaseNode<L_Jiggle>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    float timer;
};