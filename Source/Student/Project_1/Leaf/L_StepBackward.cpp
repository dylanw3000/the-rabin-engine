#include <pch.h>
#include "L_StepBackward.h"
#include "Agent/BehaviorAgent.h"

// Stagger backwards based on your yaw
// Special exceptions are granted if this would go outside of [0,100]
void L_StepBackward::on_enter()
{
    // set animation, speed, etc

    faceAng = agent->get_yaw();
    float stepDist = 10.f;

    targetPoint = Vec3(std::clamp(agent->get_position().x - sin(faceAng) * stepDist, 0.f, 100.f), 0.f, std::clamp(agent->get_position().z - cos(faceAng) * stepDist, 0.f, 100.f));

	BehaviorNode::on_leaf_enter();
}

void L_StepBackward::on_update(float dt)
{
    const auto result = agent->move_toward_point(targetPoint, dt);
    agent->set_yaw(faceAng);

    if (result == true)
    {
        on_success();
    }

    display_leaf_text();
}
