#pragma once
#include "BehaviorNode.h"
#include "Misc/NiceTypes.h"

class L_MigrateTowers : public BaseNode<L_MigrateTowers>
{
protected:
    virtual void on_enter() override;
    virtual void on_update(float dt) override;

private:
    Vec3 startPoint, targetPoint;
    float time, maxTime;
};