#ifndef nonbuilding_H
#define nonbuilding_H
#include <string>
#include "Cell.h"

class Cell;

class nonbuilding: public Cell {
	public:
	    nonbuilding(int ID, std::string name);
};

#endif
