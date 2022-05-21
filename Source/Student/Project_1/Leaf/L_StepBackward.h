#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_StepBackward : public BaseNode<L_StepBackward>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    float faceAng;
    Vec3 targetPoint;
};