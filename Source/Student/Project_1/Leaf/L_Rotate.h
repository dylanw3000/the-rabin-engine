#pragma once
#include "BehaviorNode.h"

class L_Rotate : public BaseNode<L_Rotate>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    float timer;
};