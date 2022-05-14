#include <pch.h>
#include "L_MigrateTowers.h"
#include "Agent/BehaviorAgent.h"

void L_MigrateTowers::on_enter()
{
    // set animation, speed, etc

    startPoint = agent->get_position();
    targetPoint = startPoint;

    const auto &allAgents = agents->get_all_agents();
    float longestDistance = std::numeric_limits<float>().min();
    bool targetFound = false;

    for (Agent* a : allAgents)
    {
        BehaviorAgent* aa = static_cast<BehaviorAgent*>(a);
        // make sure it's not our agent
        if (aa->getUnitType() == UnitType::Tower && a != agent)
        {
            Vec3 agentPos = a->get_position();
            agentPos.y = 0.f;
            const float distance = Vec3::Distance(startPoint, agentPos);

            if (distance > longestDistance)
            {
                longestDistance = distance;
                targetFound = true;
                targetPoint = agentPos;
            }
        }
    }

    if (targetFound == true)
    {
        BehaviorNode::on_leaf_enter();
    }
    else // couldn't find a viable agent
    {
        on_failure();
    }

    time = 0.f;
    maxTime = longestDistance / 10.f;

	BehaviorNode::on_leaf_enter();
}

void L_MigrateTowers::on_update(float dt)
{
    time += dt;

    if (time >= maxTime) {
        agent->set_position(targetPoint);
        on_success();
        return;
    }

    float a = (-cosf(time / maxTime * M_PI) + 1.f) / 2;
    agent->path_interp(startPoint, targetPoint, a);

    display_leaf_text();
}
