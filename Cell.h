#ifndef SQUARE_H
#define SQUARE_H
#include <string>

class cell{
    int ID;
    std::string name;
  public:
    cell(int ID, std::string name);

    int getID();
    std::string getName();
    void setID();
    void setName();
};

#endif

