#include <pch.h>
#include "Projects/ProjectTwo.h"
#include "P2_Pathfinding.h"

#pragma region Extra Credit
bool ProjectTwo::implemented_floyd_warshall()
{
    return false;
}

bool ProjectTwo::implemented_goal_bounding()
{
    return false;
}

bool ProjectTwo::implemented_jps_plus()
{
    return false;
}
#pragma endregion

bool AStarPather::initialize()
{
    // handle any one-time setup requirements you have

    /*
        If you want to do any map-preprocessing, you'll need to listen
        for the map change message.  It'll look something like this:

        Callback cb = std::bind(&AStarPather::your_function_name, this);
        Messenger::listen_for_message(Messages::MAP_CHANGE, cb);

        There are other alternatives to using std::bind, so feel free to mix it up.
        Callback is just a typedef for std::function<void(void)>, so any std::invoke'able
        object that std::function can wrap will suffice.
    */

    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            Node* n = &nodeList[x][y];
            GridPos pos(x, y);
            n->pos = pos;

            if (terrain->is_wall(pos)) {
                n->isWall = true;
            }
        }
    }

#if false
    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            Node* n = &nodeList[x][y];

            if (x == 0) {
                n->neighbors[neighborDirection::LEFT] = n->neighbors[neighborDirection::LEFTDOWN] = n->neighbors[neighborDirection::LEFTUP] = false;
            }

            if (x == GRID_SIZE - 1) {
                n->neighbors[neighborDirection::RIGHT] = n->neighbors[neighborDirection::RIGHTDOWN] = n->neighbors[neighborDirection::RIGHTUP] = false;
            }

            if (y == 0) {
                n->neighbors[neighborDirection::UP] = n->neighbors[neighborDirection::LEFTUP] = n->neighbors[neighborDirection::RIGHTUP] = false;
            }

            if (y == GRID_SIZE - 1) {
                n->neighbors[neighborDirection::DOWN] = n->neighbors[neighborDirection::LEFTDOWN] = n->neighbors[neighborDirection::RIGHTDOWN] = false;
            }

            if (n->neighbors[UP] && false) {}
        }
    }
#endif

    return true; // return false if any errors actually occur, to stop engine initialization
}

void AStarPather::shutdown()
{
    /*
        Free any dynamically allocated memory or any other general house-
        keeping you need to do during shutdown.
    */
}

PathResult AStarPather::compute_path(PathRequest &request)
{
    /*
        This is where you handle pathing requests, each request has several fields:

        start/goal - start and goal world positions
        path - where you will build the path upon completion, path should be
            start to goal, not goal to start
        heuristic - which heuristic calculation to use
        weight - the heuristic weight to be applied
        newRequest - whether this is the first request for this path, should generally
            be true, unless single step is on

        smoothing - whether to apply smoothing to the path
        rubberBanding - whether to apply rubber banding
        singleStep - whether to perform only a single A* step
        debugColoring - whether to color the grid based on the A* state:
            closed list nodes - yellow
            open list nodes - blue

            use terrain->set_color(row, col, Colors::YourColor);
            also it can be helpful to temporarily use other colors for specific states
            when you are testing your algorithms

        method - which algorithm to use: A*, Floyd-Warshall, JPS+, or goal bounding,
            will be A* generally, unless you implement extra credit features

        The return values are:
            PROCESSING - a path hasn't been found yet, should only be returned in
                single step mode until a path is found
            COMPLETE - a path to the goal was found and has been built in request.path
            IMPOSSIBLE - a path from start to goal does not exist, do not add start position to path
    */

    // WRITE YOUR CODE HERE
    if (request.newRequest) {
        GridPos start = terrain->get_grid_position(request.start);
        GridPos goal = terrain->get_grid_position(request.goal);

        if (terrain->is_wall(goal)) {
            return PathResult::IMPOSSIBLE;
        }

        // if (terrain.get(goal)->is_wall);

        terrain->set_color(start, Colors::Orange);
        terrain->set_color(goal, Colors::Orange);


    }
    
    // Just sample code, safe to delete
    GridPos start = terrain->get_grid_position(request.start);
    GridPos goal = terrain->get_grid_position(request.goal);
    terrain->set_color(start, Colors::Orange);
    terrain->set_color(goal, Colors::Orange);
    request.path.push_back(request.start);
    request.path.push_back(request.goal);
    return PathResult::COMPLETE;
}
