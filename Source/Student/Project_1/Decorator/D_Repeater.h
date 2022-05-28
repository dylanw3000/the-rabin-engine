#pragma once
#include "BehaviorNode.h"

class D_Repeater : public BaseNode<D_Repeater>
{
protected:
    virtual void on_update(float dt) override;
    virtual void on_exit() override;
};