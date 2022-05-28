#include <pch.h>
#include "L_MoveToClosestVictim.h"
#include "Agent/BehaviorAgent.h"

// Chase down a "common"-type actor
void L_MoveToClosestVictim::on_enter()
{
    // set animation, speed, etc

    pursuitSpeed = agent->get_movement_speed();

    // find the agent that is the furthest from this one
    float shortestDistance = std::numeric_limits<float>().max();
    bool targetFound = false;

    // get a list of all current agents
    const auto &allAgents = agents->get_all_agents();

    // and our agent's position
    const auto &currPos = agent->get_position();

    for (Agent* a : allAgents)
    {
        BehaviorAgent* aa = static_cast<BehaviorAgent*>(a);
        // make sure it's not our agent
        if (aa->getUnitType() == UnitType::Common && a != agent)
        {
            const auto &agentPos = a->get_position();
            const float distance = Vec3::Distance(currPos, agentPos);

            if (distance < shortestDistance)
            {
                shortestDistance = distance;
                targetFound = true;
                target = a;
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
}

void L_MoveToClosestVictim::on_update(float dt)
{
    // agent->set_movement_speed(agent->get_movement_speed() + dt);
    float tmp = agent->get_movement_speed();
    pursuitSpeed += dt * 20.f;
    agent->set_movement_speed(pursuitSpeed);

    const auto result = agent->move_toward_agent(target, dt);
    
    agent->set_movement_speed(tmp);

    float dist = Vec3::DistanceSquared(agent->get_position(), target->get_position());

    if (result == true || dist <= Vec3::DistanceSquared({ 0,0,0 }, agent->get_scaling()/2.f))
    {
        on_success();
    }

    display_leaf_text();
}

