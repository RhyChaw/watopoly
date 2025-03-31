#ifndef nonbuilding_H
#define nonbuilding_H
#include <string>
#include "Cell.h"
#include "propertyArray.h"

class Cell;

class nonbuilding: public Cell {
	public:
	    nonbuilding(int ID, std::string name);
};

#endif // NON_BUILDING_H
