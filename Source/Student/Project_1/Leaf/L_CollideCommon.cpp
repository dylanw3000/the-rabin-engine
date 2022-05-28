#include <pch.h>
#include "L_CollideCommon.h"
#include "../Agent/BehaviorAgent.h"

// Check for collision with all "common"-type actors
// When you collide, knock them back
void L_CollideCommon::on_update(float dt)
{
    const auto allAgents = agents->get_all_agents();

    Vec3 myPos = agent->get_position();
    Vec3 myScale = agent->get_scaling();
    float myRadius = myScale.x * myScale.x + myScale.z * myScale.z;

    for (Agent* a : allAgents)
    {
        BehaviorAgent* aa = static_cast<BehaviorAgent*>(a);
        if (aa->getUnitType() != UnitType::Common || a == agent) {
            continue;
        }

        Vec3 pos = a->get_position();
        Vec3 scale = a->get_scaling();

        Vec3 delta = pos - myPos;
        if (delta.x * delta.x + delta.z * delta.z <= myRadius + (scale.x * scale.x + scale.z * scale.z)) {
            Vec3 ang = pos - myPos;
            ang.Normalize();
            aa->set_knockback(ang);
        }
    }

    on_success();
    display_leaf_text();
}
