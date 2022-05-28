#include <pch.h>
#include "L_Float.h"

// Float up then down on a sinusoidal wave
void L_Float::on_enter()
{
    timer = 0.f;

	BehaviorNode::on_leaf_enter();
}

void L_Float::on_update(float dt)
{
    timer += dt;

    Vec3 pos = agent->get_position();
    pos.y = -cosf(timer) + 1.f;
    agent->set_position(pos);

    if (timer > 2.f * M_PI)
    {
        pos.y = 0.f;
        agent->set_position(pos);
        on_success();
    }

    display_leaf_text();
}
