#include <pch.h>
#include "L_Knockback.h"
#include "Agent/BehaviorAgent.h"

void L_Knockback::on_enter()
{
    // set animation, speed, etc

    const auto allAgents = agents->get_all_agents();
    for (Agent* a : allAgents)
    {
        BehaviorAgent* aa = static_cast<BehaviorAgent*>(a);
        if (aa->getUnitType() == UnitType::Predator) {
            continue;
        }

        Vec3 delta = a->get_position() - agent->get_position();
        delta.Normalize();
        agent->set_knockback(delta);
        break;
    }

    startingPoint = agent->get_position();
    targetPoint = startingPoint + agent->get_knockback() * float(RNG::d10() + 20);
    targetPoint.x = std::clamp(targetPoint.x, 0.f, 100.f);
    targetPoint.z = std::clamp(targetPoint.z, 0.f, 100.f);
    //agent->look_at_point(targetPoint);

    time = 0.f;
    maxTime = RNG::range(1.f, 2.f);

	BehaviorNode::on_leaf_enter();
}

void L_Knockback::on_update(float dt)
{
    time += dt;

    if (time >= maxTime) {
        agent->path_interp(startingPoint, targetPoint, 1.f);
        on_success();
    }

    float a = 1.f - (time / maxTime);
    agent->path_interp(startingPoint, targetPoint, 1.f - a * a);
    display_leaf_text();
}
