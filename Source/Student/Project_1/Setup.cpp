#include <pch.h>
#include "Projects/ProjectOne.h"
#include "Agent/CameraAgent.h"

void ProjectOne::setup()
{
    // Create your inital agents
    agents->create_behavior_agent("ExampleAgent", BehaviorTreeTypes::Example, UnitType::Common);
    agents->create_behavior_agent("Initial_Boi", BehaviorTreeTypes::Initial, UnitType::Common);
    agents->create_behavior_agent("Easy", BehaviorTreeTypes::Ease, UnitType::Common);

    BehaviorAgent* predator = agents->create_behavior_agent("Predator", BehaviorTreeTypes::Predator, UnitType::Predator);
    predator->set_position(Vec3(100, 0, 0));
    predator->set_movement_speed(20.f);
    predator->set_scaling(2.f);

    BehaviorAgent* tower1 = agents->create_behavior_agent("Tower 1", BehaviorTreeTypes::Tower_Animation, UnitType::Tower);
    tower1->set_position(Vec3(10, 0, 90));
    tower1->set_pitch(-0.2f);
    tower1->set_scaling(3.f);

    BehaviorAgent* tower2 = agents->create_behavior_agent("Tower 1", BehaviorTreeTypes::Tower_Animation, UnitType::Tower);
    tower2->set_position(Vec3(90, 0, 10));
    tower2->set_yaw(M_PI/2);
    tower2->set_pitch(-0.2f);
    tower2->set_scaling(3.f);

    // you can technically load any map you want, even create your own map file,
    // but behavior agents won't actually avoid walls or anything special, unless you code that yourself
    // that's the realm of project 2 though
    terrain->goto_map(0);

    // you can also enable the pathing layer and set grid square colors as you see fit
    // works best with map 0, the completely blank map
    terrain->pathLayer.set_enabled(true);
    terrain->pathLayer.set_value(0, 0, Colors::Red);

    // camera position can be modified from this default as well
    auto camera = agents->get_camera_agent();
    camera->set_position(Vec3(-62.0f, 70.0f, terrain->mapSizeInWorld * 0.5f));
    camera->set_pitch(0.610865); // 35 degrees
}