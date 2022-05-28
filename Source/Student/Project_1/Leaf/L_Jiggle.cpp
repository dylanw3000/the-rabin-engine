#include <pch.h>
#include "L_Jiggle.h"

// Do the wiggle
void L_Jiggle::on_enter()
{
    timer = 0.f;

	BehaviorNode::on_leaf_enter();
}

void L_Jiggle::on_update(float dt)
{
    timer += dt;

    float maxTime = 2.5f;
    agent->set_roll(cos(timer / maxTime * 12 * M_PI) * (1.f - (timer / maxTime)));

    if (timer > maxTime)
    {
        agent->set_roll(0.f);
        on_success();
    }

    display_leaf_text();
}
