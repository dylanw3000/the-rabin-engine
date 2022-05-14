#include <pch.h>
#include "L_EaseInOut.h"
#include "Agent/BehaviorAgent.h"

void L_EaseInOut::on_enter()
{
    // set animation, speed, etc

    startPoint = agent->get_position();
    targetPoint = RNG::world_position();

    time = 0.f;
    maxTime = 2.f;

	BehaviorNode::on_leaf_enter();
}

void L_EaseInOut::on_update(float dt)
{
    time += dt;

    if (time >= maxTime) {
        agent->path_interp(startPoint, targetPoint, 1.f);
        on_success();
    }

    float a = (-cosf(time / maxTime * M_PI) + 1.f) / 2;
    agent->path_interp(startPoint, targetPoint, a);
    display_leaf_text();
}
