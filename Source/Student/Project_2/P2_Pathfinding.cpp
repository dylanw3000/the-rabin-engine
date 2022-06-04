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

int GRID_SIZE = MAP_SIZE;
void AStarPather::gridInitialize(float weight, PathRequest request) {
    GridPos goal = terrain->get_grid_position(request.goal);
    int xx = goal.row;
    int yy = goal.col;

    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            map[x][y].position = GridPos(x, y);
            map[x][y].onList = ListType::Unused;
            map[x][y].wall = terrain->is_wall(x, y);
            map[x][y].parent = nullptr;

            map[x][y].neighbors.clear();
            map[x][y].diagonals.clear();

            // map[x][y].given = sqrtf(float((xx - x) * (xx - x) + (yy - y) * (yy - y))) * weight;
            float xDiff = fabsf(float(xx) - x);
            float yDiff = fabsf(float(yy) - y);
            switch (request.settings.heuristic) {
                case Heuristic::MANHATTAN:
                    map[x][y].given = xDiff + yDiff;
                    break;
                case Heuristic::CHEBYSHEV:
                    map[x][y].given = std::max(xDiff, yDiff);
                    break;
                case Heuristic::EUCLIDEAN:
                    map[x][y].given = sqrtf(xDiff * xDiff + yDiff * yDiff);
                    break;
                case Heuristic::OCTILE:
                default:
                    map[x][y].given = std::min(xDiff, yDiff) * sqrtf(2.f) + std::max(xDiff, yDiff) - std::min(xDiff, yDiff);
            }
            map[x][y].given *= weight;
        }
    }

    for (int x = 0; x < GRID_SIZE; x++) {
        for (int y = 0; y < GRID_SIZE; y++) {
            Node* n = &map[x][y];
            if (n->wall) continue;

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

            if (xplus && yplus && !map[x + 1][y + 1].wall) n->diagonals.push_back(&map[x + 1][y + 1]);
            if (xplus && yminus && !map[x + 1][y - 1].wall) n->diagonals.push_back(&map[x + 1][y - 1]);
            if (xminus && yminus && !map[x - 1][y - 1].wall) n->diagonals.push_back(&map[x - 1][y - 1]);
            if (xminus && yplus && !map[x - 1][y + 1].wall) n->diagonals.push_back(&map[x - 1][y + 1]);
        }
    }
}

void AStarPather::PushNode(Node* n, float cost, Node* prev, PathRequest request) {
    n->cost = cost;
    n->onList = ListType::Open;
    n->parent = prev;
    if (prev) {
        n->xParent = prev->position.row;
        n->yParent = prev->position.col;
    }
    openList.push_back(n);

    terrain->set_color(n->position, Colors::Blue);
    if (n->position == terrain->get_grid_position(request.start) || n->position == terrain->get_grid_position(request.goal)) {
        terrain->set_color(n->position, Colors::Orange);
    }
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

        if(terrain->is_wall(start) || terrain->is_wall(goal)) { return PathResult::IMPOSSIBLE; }

        GRID_SIZE = terrain->get_map_width();
        gridInitialize(request.settings.weight, request);

        openList.clear();
        PushNode(getNode(start), 0.f, nullptr, request);

        terrain->set_color(start, Colors::Orange);
        terrain->set_color(goal, Colors::Orange);

        if (terrain->is_wall(start)) {
            request.path.push_back(request.start);
            request.path.push_back(request.goal);
            return PathResult::COMPLETE;
        }
    }

    while (openList.size() > 0) {
        Node* activeNode = nullptr;
        int activeIndex = -1;

        float minCost = 99999.f;
        for (int i = 0; i < openList.size(); i++) {
            Node* n = openList[i];
            if (n->cost+n->given < minCost) {
                minCost = n->cost + n->given;
                activeNode = n;
                activeIndex = i;
            }
        }

        // if (!activeNode) { return PathResult::IMPOSSIBLE; }

        // request.path.push_back(terrain->get_world_position(activeNode->position));
        openList.erase(openList.begin() + activeIndex);
        activeNode->onList = ListType::Closed;
        terrain->set_color(activeNode->position, Colors::Yellow);

        if (activeNode->position == terrain->get_grid_position(request.start) || activeNode->position == terrain->get_grid_position(request.goal)) {
            terrain->set_color(activeNode->position, Colors::Orange);
        }

        if (activeNode->position == terrain->get_grid_position(request.goal)) { // path complete
            Node* n = activeNode;
            GridPos start = terrain->get_grid_position(request.start);
            GridPos goal = terrain->get_grid_position(request.goal);

            path.clear();
            path.push_back(terrain->get_world_position(n->position));

            if (request.settings.rubberBanding) {
                int xmin, ymin, xmax, ymax;
                
                while (n->position != start) {
                    Node* n1 = n->parent;
                    if (n1 == nullptr) break;
                    Node* n2 = n1->parent;
                    if (n2 == nullptr) break;
                    
                    xmin = std::min(n->position.row, std::min(n1->position.row, n2->position.row));
                    xmax = std::max(n->position.row, std::max(n1->position.row, n2->position.row));

                    ymin = std::min(n->position.col, std::min(n1->position.col, n2->position.col));
                    ymax = std::max(n->position.col, std::max(n1->position.col, n2->position.col));

                    bool valid = true;
                    for (int x = xmin; x <= xmax; x++) {
                        for (int y = ymin; y <= ymax; y++) {
                            if (map[x][y].wall) {
                                valid = false;
                                break;
                            }
                        }
                        if (!valid) break;
                    }

                    if (valid) {
                        n->parent = n2;
                    }
                    else {
                        n = n1;
                    }
                }
            }

            n = activeNode;
            if (request.settings.smoothing) {
                std::vector<Vec3> positions;
                float maxDist = 1.5f * Vec3::Distance(terrain->get_world_position(map[0][0].position), terrain->get_world_position(map[0][1].position));

                positions.push_back(Pos(n));
                while (n->parent != nullptr) {
                    Vec3 v1 = Pos(n);
                    Vec3 v2 = Pos(n->parent);
                    
                    Vec3 path = v2 - v1;
                    int multiple = 1;

                    while (path.Length() > maxDist) {
                        path /= 2.f;
                        multiple *= 2;
                    }

                    for (int i = 0; i < multiple; i++) {
                        positions.push_back(v1 + path * float(i));
                    }

                    n = n->parent;
                }

                std::reverse(positions.begin(), positions.end());

                request.path.push_back(positions[0]);
                for (int i = 0; i < positions.size() - 2; i++) {
                    Vec3 v1;
                    if (i == 0) {
                        v1 = positions[0];
                    }
                    else {
                        v1 = positions[i - 1];
                    }
                    Vec3 v2 = positions[i];
                    Vec3 v3 = positions[i + 1];
                    Vec3 v4;
                    if (i == positions.size() - 2) {
                        v4 = positions[i + 1];
                    }
                    else {
                        v4 = positions[i + 2];
                    }

                    request.path.push_back(Vec3::CatmullRom(v1, v2, v3, v4, 0.25f));
                    request.path.push_back(Vec3::CatmullRom(v1, v2, v3, v4, 0.5f));
                    request.path.push_back(Vec3::CatmullRom(v1, v2, v3, v4, 0.75f));
                    request.path.push_back(v3);
                }
            }
            else {
                while (n->position != start) {
                    n = n->parent;
                    path.push_back(Pos(n));
                }
            }

            /*
            std::vector<Vec3> rubberPath;
            Vec3 v1, v2, v3, v4;
            int xmin, ymin, xmax, ymax;
            if (request.settings.rubberBanding) {
                for (int i = 0; i < path.size()-2; i++) {
                    xmin = std::min(path[i].x,)
                    xmin = xmax = path[i].x;
                    ymin = ymax = path[i].y;
                }
            }
            */

            while (path.size() > 0) {
                request.path.push_back(path[path.size() - 1]);
                path.pop_back();
            }

            return PathResult::COMPLETE;
        }

        for (auto n : activeNode->neighbors) {
            float dist = activeNode->cost + 1.f;
            if (n->onList == ListType::Unused) {
                PushNode(n, dist, activeNode, request);
            }
            else if (n->onList == ListType::Open && dist < n->cost) {
                n->cost = dist;
                n->xParent = activeNode->position.row;
                n->yParent = activeNode->position.col;
                n->parent = activeNode;
            }
            else if (n->onList == ListType::Closed && dist < n->cost) {
                PushNode(n, dist, activeNode, request);
            }
        }

        for (auto n : activeNode->diagonals) {
            float dist = activeNode->cost + sqrtf(2.f);
            if (n->onList == ListType::Unused) {
                PushNode(n, dist, activeNode, request);
            }
            else if (n->onList == ListType::Open && n->cost > dist) {
                n->cost = dist;
                n->xParent = activeNode->position.row;
                n->yParent = activeNode->position.col;
                n->parent = activeNode;
            }
            else if (n->onList == ListType::Closed && n->cost > dist) {
                PushNode(n, dist, activeNode, request);
            }
        }

        if (request.settings.singleStep) { return PathResult::PROCESSING; }
    }

    return PathResult::IMPOSSIBLE;
    

    
#if false
    // Just sample code, safe to delete
    GridPos start = terrain->get_grid_position(request.start);
    GridPos goal = terrain->get_grid_position(request.goal);
    terrain->set_color(start, Colors::Orange);
    terrain->set_color(goal, Colors::Orange);
    request.path.push_back(request.start);
    request.path.push_back(request.goal);
    return PathResult::COMPLETE;
#endif
}
