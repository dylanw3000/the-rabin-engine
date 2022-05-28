#include <pch.h>
#include "L_Ramming.h"
#include "Agent/BehaviorAgent.h"

// Choose a direction and run, gaining progressively more speed until you would leave the [0,100] legal area
void L_Ramming::on_enter()
{
    // set animation, speed, etc

    ramSpeed = 0.f;
    moveAng = RNG::unit_vector_3D();
    moveAng.y = 0.f;
    moveAng.Normalize();
    agent->set_yaw(atan2(moveAng.x, moveAng.z));

	BehaviorNode::on_leaf_enter();
}

void L_Ramming::on_update(float dt)
{
    ramSpeed += dt * 50.f;

    Vec3 pos = agent->get_position();
    pos += moveAng * ramSpeed * dt;

    bool done = false;

    if (pos.x < 0.f) {
        pos.x = 0.f;
        done = true;
    }
    if (pos.z < 0.f) {
        pos.z = 0.f;
        done = true;
    }
    if (pos.x > 100.f) {
        pos.x = 100.f;
        done = true;
    }
    if (pos.z > 100.f) {
        pos.z = 100.f;
        done = true;
    }

    agent->set_position(pos);

    if (done) {
        on_success();
    }

    display_leaf_text();
}
