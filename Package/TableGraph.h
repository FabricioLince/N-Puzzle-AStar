#ifndef TABLEGRAPH_H
#define TABLEGRAPH_H

#include "Graph.h"
#include "TableNode.h"
#include <vector>
#include <ostream>

class Position
{
    public:
        int x;
        int y;
        Position(int x_=0, int y_=0)
        : x(x_), y(y_) {}
        const int distance(const Position& p) const
        {
            return std::abs(x-p.x) + std::abs(y-p.y);
        }
        const int distance(int x2, int y2) const
        {
            return std::abs(x-x2) + std::abs(y-y2);
        }
};
std::ostream& operator<< (std::ostream& out, const Position& pos);

class TableGraph : public GraphWithCostAndHeuristicInterface<TableNode>
{
    std::vector<Position> posTo;

    public:
        TableGraph(int size);

        typedef std::vector<Node> NodeList;
        NodeList getNeighborsFor(Node node);
        int costTo(Node from, Node to);
        int heuristic(Node from, Node to);
        int manhattanDistance(Node from);
};

std::ostream& operator<< (std::ostream& out, const TableGraph::NodeList& list);
#endif // TABLEGRAPH_H
