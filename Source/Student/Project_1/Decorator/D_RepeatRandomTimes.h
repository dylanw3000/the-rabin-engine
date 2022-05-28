#pragma once
#include "BehaviorNode.h"

class D_RepeatRandomTimes : public BaseNode<D_RepeatRandomTimes>
{
private:
    int number;
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;
};