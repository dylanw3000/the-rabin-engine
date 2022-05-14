#include <pch.h>
#include "L_Rotate.h"

void L_Rotate::on_enter()
{
    timer = 0.f;

	BehaviorNode::on_leaf_enter();
}

void L_Rotate::on_update(float dt)
{
    timer += dt;
    agent->set_yaw(agent->get_yaw() + dt * 0.2f);

    display_leaf_text();

    // if (dt >= 2.f * M_PI) {
        on_success();
    // }
}
