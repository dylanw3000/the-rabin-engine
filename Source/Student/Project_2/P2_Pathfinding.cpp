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

    return true; // return false if any errors actually occur, to stop engine initialization
}

void AStarPather::shutdown()
{
    /*
        Free any dynamically allocated memory or any other general house-
        keeping you need to do during shutdown.
    */
}

void AStarPather::gridInitialize(float weight, GridPos start) {
    int xx = start.row;
    int yy = start.col;

    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            map[x][y].position = GridPos(x, y);
            map[x][y].given = sqrtf(powf(float(xx) - x, 2) + powf(float(yy) - y, 2)) * weight;
            map[x][y].onList = ListType::Unused;
            map[x][y].wall = terrain->is_wall(x, y);

            map[x][y].neighbors.clear();
            map[x][y].diagonals.clear();
        }
    }

    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            Node* n = &map[x][y];
            bool xminus = true;
            bool xplus = true;
            bool yminus = true;
            bool yplus = true;

            if (x == 0 || map[x - 1][y].wall) xminus = false;
            if (y == 0 || map[x][y - 1].wall) yminus = false;
            if (x == GRID_SIZE - 1 || map[x + 1][y].wall) xplus = false;
            if (y == GRID_SIZE - 1 || map[x][y + 1].wall) yplus = false;

            if (xminus) n->neighbors.push_back(&map[x - 1][y]);
            if (yminus) n->neighbors.push_back(&map[x][y - 1]);
            if (xplus) n->neighbors.push_back(&map[x + 1][y]);
            if (yplus) n->neighbors.push_back(&map[x][y + 1]);

            if (xplus && yplus) n->diagonals.push_back(&map[x + 1][y + 1]);
            if (xplus && yminus) n->diagonals.push_back(&map[x + 1][y - 1]);
            if (xminus && yminus) n->diagonals.push_back(&map[x - 1][y - 1]);
            if (xminus && yplus) n->diagonals.push_back(&map[x - 1][y + 1]);
        }
    }
}

void AStarPather::PushNode(Node* n, float cost) {
    n->cost = cost;
    openList.push_back(n);
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

        terrain->set_color(start, Colors::Orange);
        terrain->set_color(goal, Colors::Orange);

        gridInitialize(request.settings.weight, start);

        openList.clear();
        PushNode(getNode(start), 0.f);

        // request.path.push_back(request.start);
        // request.path.push_back(request.goal);
    }

    while (openList.size() > 0) {
        Node* activeNode = nullptr;
        int activeIndex = -1;

        float minCost = 99999.f;
        for (int i = 0; i < openList.size(); i++) {
            Node* n = openList[i];
            if (n->given < minCost) {
                minCost = n->cost;
                activeNode = n;
                activeIndex = i;
            }
        }

        if (!activeNode) { return PathResult::IMPOSSIBLE; }

        request.path.push_back(terrain->get_world_position(activeNode->position));
        openList.erase(openList.begin() + activeIndex);

        if (request.settings.singleStep) { return PathResult::PROCESSING; }
    }

    request.path.push_back(request.goal);
    return PathResult::COMPLETE;
    

    
    // Just sample code, safe to delete
    GridPos start = terrain->get_grid_position(request.start);
    GridPos goal = terrain->get_grid_position(request.goal);
    terrain->set_color(start, Colors::Orange);
    terrain->set_color(goal, Colors::Orange);
    request.path.push_back(request.start);
    request.path.push_back(request.goal);
    return PathResult::COMPLETE;
}
