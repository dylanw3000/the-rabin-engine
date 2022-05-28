#pragma once
#include "Misc/PathfindingDetails.hpp"

#define GRID_SIZE 40

class AStarPather
{
public:
    /* 
        The class should be default constructible, so you may need to define a constructor.
        If needed, you can modify the framework where the class is constructed in the
        initialize functions of ProjectTwo and ProjectThree.
    */

    /* ************************************************** */
    // DO NOT MODIFY THESE SIGNATURES
    bool initialize();
    void shutdown();
    PathResult compute_path(PathRequest &request);
    /* ************************************************** */

    /*
        You should create whatever functions, variables, or classes you need.
        It doesn't all need to be in this header and cpp, structure it whatever way
        makes sense to you.
    */

    enum nodeState {
        UNUSED,
        OPEN,
        CLOSED
    };

    enum neighborDirection {
        RIGHT,
        RIGHTDOWN,
        DOWN,
        LEFTDOWN,
        LEFT,
        LEFTUP,
        UP,
        RIGHTUP
    };

    struct Node {
        Vec2 parent;
        nodeState state = UNUSED;
        GridPos pos;
        float dist;
        bool isWall = false;
        bool neighbors[8];

        bool operator<(const Node n) const {
            return dist < n.dist;
        }

        bool operator>(const Node n) const {
            return dist > n.dist;
        }
    };

    Node nodeList[40][40];

    std::priority_queue<Node*, std::vector<Node*>, std::greater<Node> > activeList;

};