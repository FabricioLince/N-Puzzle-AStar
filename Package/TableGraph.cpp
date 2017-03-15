#include "TableGraph.h"

#include "TableNode.h"
#include "defines.h"
#include <vector>


TableGraph::TableGraph(int size)
{
    TableNode endTable(size);

    repeat(i, size*size) posTo.push_back(Position());
    repeat(i, size*size)
    {
        posTo.at(endTable.at(i)) = Position(I_TO_X(i, size), I_TO_Y(i, size));
    }
}
TableGraph::NodeList TableGraph::getNeighborsFor(Node node)
{
    NodeList n;
    Node origin(node);

    repeat(i, 4)
    {
        bool r = node.moveDir(i);
        if (r)
        {
            n.push_back(node);
            node = origin;
        }
    }

    return n;
}
int TableGraph::costTo(Node from, Node to)
{
    return 1;
}
int TableGraph::manhattanDistance(Node from)
{
    int h = 0;
    int size = from.getSize();
    repeat(pos, size*size)
    {
        int value = from.at(pos);
        if (value == 0) continue;
        int pos_x = I_TO_X(pos, size);
        int pos_y = I_TO_Y(pos, size);
        h += posTo.at(value).distance(pos_x, pos_y);
    }
    return h;
}
int TableGraph::heuristic(Node from, Node to)
{
    return manhattanDistance(from);
}

std::ostream& operator<< (std::ostream& out, const Position& pos)
{
    return out << "(" << pos.x << "x" << pos.y << ")";
}

std::ostream& operator<< (std::ostream& out, const TableGraph::NodeList& list)
{
    repeat(i, list.size())
    {
        out << list.at(i) << "\n";
    }
    return out;
}

