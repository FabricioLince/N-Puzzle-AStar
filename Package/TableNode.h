#ifndef TABLENODE_H
#define TABLENODE_H

#include <vector>
#include <string>
#include <ostream>

class TableNode
{
    std::vector<int> tileList;
    int size;
    static void ValidateInitString(int size, std::string init);
    public:
        TableNode(int size=3, std::string init = std::string());
        const int getSize() const {return size;}
        const int at(int x, int y) const;
        int& at(int x, int y);
        const int at(int index) const {return tileList.at(index);};

        bool moveRight();
        bool moveLeft();
        bool moveUp();
        bool moveDown();
        bool moveDir(int dir);
        int blankPos();

        void shuffle(int times=20);

        const bool operator< (const TableNode& other) const;
        const bool operator==(const TableNode& other) const;
        const bool operator!=(const TableNode& other) const;
};
std::ostream& operator<< (std::ostream& out, const TableNode& table);

#endif // TABLENODE_H
