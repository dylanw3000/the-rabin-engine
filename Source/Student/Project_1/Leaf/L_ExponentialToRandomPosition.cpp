#include <pch.h>
#include "L_ExponentialToRandomPosition.h"
#include "Agent/BehaviorAgent.h"

void L_ExponentialToRandomPosition::on_enter()
{
    // set animation, speed, etc

    startingPoint = agent->get_position();
    targetPoint = RNG::world_position();
    //agent->look_at_point(targetPoint);

    time = 0.f;
    maxTime = RNG::range(1.f, 1.f);

	BehaviorNode::on_leaf_enter();
}

void L_ExponentialToRandomPosition::on_update(float dt)
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
