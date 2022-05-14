#pragma once
#include "BehaviorNode.h"

class C_EternalSequencer : public BaseNode<C_EternalSequencer>
{
protected:
    virtual void on_update(float dt) override;
};