#include <pch.h>
#include "D_RepeatRandomTimes.h"

// repeat 1d4 times
void D_RepeatRandomTimes::on_enter()
{
    number = RNG::d4();
    BehaviorNode::on_enter();
}

void D_RepeatRandomTimes::on_update(float dt)
{
    BehaviorNode *child = children.front();

    child->tick(dt);

    if (child->succeeded() == true)
    {
        number--;
        if (number <= 0) {
            on_success();
        }
        else {
            child->set_status(NodeStatus::READY);
        }
    }
    else if (child->failed() == true)
    {
        on_failure();
    }

}

