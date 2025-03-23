#ifndef OSAP_H
#define OSAP_H
#include <string>
#include <memory>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Player.h"
#include "nonbuilding.h"

class OSAP : public nonbuilding {
private:
    static const int COLLECT_AMOUNT = 200;

public:
    OSAP(int ID, std::string name);
    ~OSAP();
    void collectOSAP(std::shared_ptr<Player> p);
};

#endif // OSAP_H

