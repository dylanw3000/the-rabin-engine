#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_EaseInOut : public BaseNode<L_EaseInOut>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 startingPoint, targetPoint;
    float time, maxTime;
};