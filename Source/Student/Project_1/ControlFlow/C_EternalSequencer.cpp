#include <pch.h>
#include "C_EternalSequencer.h"

void C_EternalSequencer::on_update(float dt)
{
    // run all children
    // if any child fails, the node fails
    // if all children succeed, the node succeeds

    bool allSuccess = true;

    for (auto && child : children)
    {
        child->tick(dt);

        if (child->is_running() == false) {
            if (child->succeeded() == false) {
                on_failure();
            }
            child->set_status(NodeStatus::READY);
        }
        // child->tick(dt);
    }

}
