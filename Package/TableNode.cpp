#include "TableNode.h"
#include "defines.h"
#include <vector>
#include <string>
#include <ostream>



const bool TableNode::operator<(const TableNode& other) const
{
    if (size < other.getSize()) return true;
    repeat(i, size*size)
    {
        if (tileList.at(i) < other.at(i)) return true;
        else if (tileList.at(i) > other.at(i)) return false;
    }
    return false;
}
const bool TableNode::operator==(const TableNode& other) const
{
    if (size != other.getSize()) return false;
    repeat(i, size*size)
    {
        if (tileList.at(i) != other.at(i)) return false;
    }
    return true;
}
const bool TableNode::operator!=(const TableNode& other) const
{
    return !(this->operator==(other));
}

TableNode::TableNode(int size_, std::string init)
:size(size_)
{
    if (init.size() == 0)
    {
        repeat(i, size*size-1)
        {
            init += (char)(i+'1');
        }
        init += "0";
    }
    else
    {
        TableNode::ValidateInitString(size, init);
    }

    //std::cout << "init with " << init << "\n";

    repeat(i, size*size)
    {
        int number = (int)(init.at(i)-'0');
        tileList.push_back(number);
    }
}
void TableNode::ValidateInitString(int size, std::string init)
{
    std::string err;
    if ((int)init.size() != size*size)
    {
        char temp[128];
        sprintf(temp, "init with wrong string size: %d, should be %d", init.size(), size*size);
        err += temp;
    }
    std::vector<int> missing;
    std::vector<int> repeated;
    std::vector<char> numberCheck(size*size, false);
    repeat(i, init.size())
    {
        int number = (int)(init.at(i)-'0');
        if (numberCheck.at(number) == true)
        {
            repeated.push_back(number);
        }
        numberCheck.at(number) = true;
    }
    repeat(i, numberCheck.size())
    {
        if (numberCheck.at(i) == false)
        {
            missing.push_back(i);
        }
    }

    if (missing.size() > 0)
    {
        if (err.size() > 0) err += "\n";
        err += "missing numbers on init:";
        repeat(j, missing.size())
        {
            err += " ";
            err += '0' + missing.at(j);
        }
    }
    if (repeated.size() > 0)
    {
        if (err.size() > 0) err += "\n";
        err += "repeated numbers on init:";
        repeat(j, repeated.size())
        {
            err += " ";
            err += '0' + repeated.at(j);
        }
    }
    if (err.size() > 0) throw err.c_str();
}
const int TableNode::at(int x, int y) const
{
    return tileList.at(x+(y*size));
}
int& TableNode::at(int x, int y)
{
    return tileList.at(x+(y*size));
}
int TableNode::blankPos()
{
    repeat(i, size*size)
    {
        if (tileList.at(i) == 0) return i;
    }
    return -1;
}

void TableNode::shuffle(int times)
{
    repeat(i, times)
    {
        if (!moveDir(rand()%4)) --i;
    }
}

#define GET_XY() int blank = blankPos(); int x = I_TO_X(blank, size); int y = I_TO_Y(blank, size);
bool TableNode::moveRight()
{
    GET_XY();
    if (x == size-1) return false;

    std::swap(at(x, y), at(x+1, y));
    return true;
}
bool TableNode::moveLeft()
{
    GET_XY();
    if (x == 0) return false;

    std::swap(at(x, y), at(x-1, y));
    return true;
}
bool TableNode::moveUp()
{
    GET_XY();
    if (y == 0) return false;

    std::swap(at(x, y), at(x, y-1));
    return true;
}
bool TableNode::moveDown()
{
    GET_XY();
    if (y == size-1) return false;

    std::swap(at(x, y), at(x, y+1));
    return true;
}
#undef GET_XY
bool TableNode::moveDir(int dir)
{
    switch (dir)
    {
        case 0: return moveDown();
        case 1: return moveLeft();
        case 2: return moveRight();
        case 3: return moveUp();
    }
    return false;
}

std::ostream& operator<< (std::ostream& out, const TableNode& table)
{
    int c = 1;
    if (table.getSize() >= 4) c = 2;
    repeat(y, table.getSize())
    {
        repeat(x, table.getSize())
        {
            int value = table.at(x, y);
            if (value == 0) out << "_ ";
            else out << value << " ";
            if (c == 2 && value < 10) out << " ";
        }
        out << "\n";
    }

    return out;
}
