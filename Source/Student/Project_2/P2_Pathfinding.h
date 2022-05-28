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

    
    enum ListType : int {
        Unused,
        Open,
        Closed
    };

    struct Node {
        GridPos position;
        int xParent, yParent; // Parent
        float cost; // Total cost
        float given; // Given cost
        ListType onList = Unused; // On open/closed list?
        bool wall;

        std::vector<Node*> neighbors;
        std::vector<Node*> diagonals;
    };

    Node map[GRID_SIZE][GRID_SIZE];
    std::vector<Node*> openList;

    void gridInitialize(float weight, GridPos start);
    Node* getNode(GridPos pos) { return &map[pos.row][pos.col]; }
    void PushNode(Node* n, float cost);
    
};