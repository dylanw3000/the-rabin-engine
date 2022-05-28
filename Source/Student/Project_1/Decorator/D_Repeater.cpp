#include <pch.h>
#include "D_Repeater.h"

void D_Repeater::on_update(float dt)
{
    BehaviorNode *child = children.front();

    child->tick(dt);

    if (child->succeeded() == true)
    {
        on_success();
    }
    else if (child->failed() == true)
    {
        on_failure();
    }

}

void D_Repeater::on_exit()
{
    // we want the node and child to repeat, so go back to ready
    set_status(NodeStatus::READY);
}

