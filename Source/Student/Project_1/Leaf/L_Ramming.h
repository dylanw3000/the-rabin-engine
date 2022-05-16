#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_Ramming : public BaseNode<L_Ramming>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 moveAng;
    float ramSpeed;
};