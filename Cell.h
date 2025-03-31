#ifndef CELL_H
#define CELL_H
#include <string>

class Cell {
    int ID;
    std::string name;
  public:
    Cell(int ID, std::string name);

    int getID();
    std::string getName();
    void setID(int id);
    void setName(std::string name);
};

#endif // CELL_H
