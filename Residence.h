#ifndef RESIDENCE_H
#define RESIDENCE_H

#include "Building.h"
#include <string>

class Residence : public Building {
private:
    static const int RENT_RATES[4]; // Rent based on number of residences owned

public:
    Residence(std::string name);
    ~Residence();

    // Methods
    int calculateRent() const;
    void currentOn(Player* player) override;
    int getOwnerResidenceCount() const;
};

#endif // RESIDENCE_H
