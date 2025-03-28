#ifndef GOOSE_NESTING_H
#define GOOSE_NESTING_H
#include <string>
#include <memory>
#include <string>
#include <cstdlib>
#include <ctime>
#include "nonbuilding.h"
#include "Player.h"

class GooseNesting: public nonbuilding {
    public:
        GooseNesting(int ID, std::string name);
        static void nesting(std::shared_ptr<Player> p);
        ~GooseNesting();
};


#endif // GOOSE_NESTING_H
