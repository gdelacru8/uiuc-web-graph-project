#include "graph.hpp"
#include <iostream>

int main() 
{
    Graph graph("nodes.txt");
    graph.bfsTraversal("illinois.edu");
    graph.brandes();
    graph.graphToPNG();
    return 0;
}