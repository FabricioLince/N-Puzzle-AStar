
#include <iostream>
#include "Package/TableNode.h"
#include "Package/TableGraph.h"
#include "Package/PathFinder/AStar.h"

int main()
{
    int tableSize = 3;
    TableNode t1(tableSize);
    t1.shuffle(100);
    TableNode goal(tableSize);

    std::cout << "from:\n" << t1 << "\n";
    std::cout << "to:\n" << goal << "\n";

    TableGraph graph(tableSize);
    TableGraph::NodeList path;

    AStar::search(graph, t1, goal, path);

    std::cout << path << "\n";
    std::cout << path.size()-1 << " steps\n"; // -1 coz the first step is the starting node

    return 0;
}
