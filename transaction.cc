#include "transaction.h"
#include <sstream>

int Transactions::getPropertyCost(const std::string &property_name) {
    for (int i = 0; i < 28; ++i) {
        if (property_name == OWNABLE[i][0]) {
            int cost;
            std::stringstream ss(OWNABLE[i][3]);
            ss >> cost;
            return cost;
        }
    }
    return -1; // Return -1 if property not found
}

bool Transactions::isGym(std::string squareName){
    for (int i = 22; i < 24; i++){
        if (OWNABLE[i][0] == squareName) {
            return true;
        }
    }
    return false;
}

bool Transactions::checkFund(std::shared_ptr<Player> p1, int amt) {
    if (p1->getCash() < amt) {
        std::cout << "The player " << p1->getName() << " doesn't have enough funds to use" << std::endl;
        return false;
    }
    return true;
}

bool Transactions::isResidence(std::string squareName){
    for (int i = 24; i < 28; i++){
        if (OWNABLE[i][0] == squareName){
	    return true;
	}
    }
    return false;
}


bool Transactions::isAcademic(std::string squareName){
    for (int i = 0; i < 22; i++){
        if (OWNABLE[i][0] == squareName){
	    return true;
	}
    }
    return false;
}

void Transactions::transferProperty(std::shared_ptr<Building> building, std::shared_ptr<Player> from, std::shared_ptr<Player> to) {
    from->removeProp(building);
    to->addProp(building);
    std::cout << "Transferred " << building->getName() << " from " << from->getName() << " to " << to->getName() << std::endl;
}

bool Transactions::isOwned(std::string nameSquare) {
    int sizeOwnedList = ownedProperties.size();
    for (int i = 0; i < sizeOwnedList; i++) {
        if (ownedProperties[i]->getName() == nameSquare) {
            return true;
        }
    }
    return false;
}

void Transactions::trade(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, double money, std::shared_ptr<Building> build) {
    if (p1->getCash() < money) {
        std::cout << "The player " << p1->getName() << " doesnt got money" << std::endl;
        return;
    }
    if (!(p2->ownThisProp(build->getName()))) {
        std::cout << "The player " << p2->getName() << " doesn't own this property" << std::endl;
        return;
    }

   
    if (build->getImprLevel() != 0) {
        std::cout << "there are improvments on this property." << std::endl;
        return;
    }

    string choice;
    cout << p2->getName() << ", do you accept this trade offer? (yes/no): ";
    cin >> choice;
    if (choice == "accept" || choice == "y" || choice == "yes") {
    
        for (int i = 0; i < 22; i++) {
            if (OWNABLE[i][0] == build->getName()) {
                auto acad = std::dynamic_pointer_cast<Academic>(build);
                if (acad->getOwned()) {
                    acad->setOwned(false);
                }
            }
        }

        // the transaction occur if all checking pass
        p1->pay(money);
        transferProperty(build, p1, p2);

        // update Monopoly blocks of both players
        p1->updateMonopolyBlock();
        p2->updateMonopolyBlock();

        // set correct paylevel and tuition
        if (isGym(build->getName())){
            p2->changePropertyCount(0, -1, 0);
            p1->changePropertyCount(0, 1, 0);
            build->setGymLevel(p2->getOwnedGyms() - 1);
        } else if (isResidence(build->getName())){
            p2->changePropertyCount(-1, 0, 0);
            p1->changePropertyCount(1, 0, 0);
            build->setResLevel(p2->getOwnedResidences() - 1);
        } else if (isAcademic(build->getName())){
            p2->changePropertyCount(0, 0, -1);
            p1->changePropertyCount(0, 0, 1);
            if (p1->checkIfInMonopolyBlock(build->getName())){
                auto acad = std::dynamic_pointer_cast<Academic>(build);
                acad->setOwned(true);
            }
        }
        std::cout << "The transaction is completed!" << std::endl;
    } else {
        std::cout << "The transaction was rejected!" << std::endl;
    }
}

void Transactions::trade(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<Building> building1, std::shared_ptr<Building> building2) {
    if (!(p2->ownThisProp(building2->getName()))) {
        std::cout << "The player " << p2->getName() << " doesn't own this property" << std::endl;
        return;
    }

    if (!(p1->ownThisProp(building1->getName()))) {
        std::cout << "The player " << p1->getName() << " doesn't own this property" << std::endl;
        return;
    }
   
    if (building1->getImprLevel() != 0) {
        std::cout << "there are improvments on this property." << std::endl;
        return;
    }

    if (building2->getImprLevel() != 0) {
        std::cout << "there are improvments on this property." << std::endl;
        return;
    }

    string choice;
    cout << p2->getName() << ", do you accept this trade offer? (yes/no): ";
    cin >> choice;
    if (choice == "accept" || choice == "y" || choice == "yes") {

        for (int i = 0; i < 22; i++) {
            if (OWNABLE[i][0] == building1->getName()) {
                auto acad = std::dynamic_pointer_cast<Academic>(building1);
                if (acad->getOwned()) {
                    acad->setOwned(false);
                }
            }
        }

        for (int i = 0; i < 22; i++) {
            if (OWNABLE[i][0] == building2->getName()) {
                auto acad = std::dynamic_pointer_cast<Academic>(building2);
                if (acad->getOwned()) {
                    acad->setOwned(false);
                }
            }
        }

        transferProperty(building1, p1, p2);
        transferProperty(building2, p2, p1);
        
        // update Monopoly blocks of both players
        p1->updateMonopolyBlock();
        p2->updateMonopolyBlock();

        if (isGym(building2->getName())){
            p2->changePropertyCount(0, -1, 0);
            p1->changePropertyCount(0, 1, 0);
            building2->setGymLevel(p2->getOwnedGyms() - 1);
        } else if (isResidence(building2->getName())){
            p2->changePropertyCount(-1, 0, 0);
            p1->changePropertyCount(1, 0, 0);
            building2->setResLevel(p2->getOwnedResidences() - 1);
        } else if (isAcademic(building2->getName())){
            p2->changePropertyCount(0, 0, -1);
            p1->changePropertyCount(0, 0, 1);
            if (p2->checkIfInMonopolyBlock(building2->getName())){
                auto acad = std::dynamic_pointer_cast<Academic>(building2);
                acad->setOwned(true);
            }
        }

        if (isGym(building1->getName())){
            p1->changePropertyCount(0, -1, 0);
            p2->changePropertyCount(0, 1, 0);
            building1->setGymLevel(p1->getOwnedGyms() - 1);
        } else if (isResidence(building2->getName())){
            p1->changePropertyCount(-1, 0, 0);
            p2->changePropertyCount(1, 0, 0);
            building1->setResLevel(p1->getOwnedResidences() - 1);
        } else if (isAcademic(building1->getName())){
            p1->changePropertyCount(0, 0, 1);
            p2->changePropertyCount(0, 0, -1);
            if (p1->checkIfInMonopolyBlock(building1->getName())){
                auto acad = std::dynamic_pointer_cast<Academic>(building1);
                acad->setOwned(true);
            }
        }
        std::cout << "The transaction is completed!" << std::endl;
    } else {
        std::cout << "The transaction was rejected!" << std::endl;
    }
}

void Transactions::trade(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<Building> building, double money) {
    Transactions::trade(p2, p1, money, building); 
}

void Transactions::trade(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, double money1, double money2) {
    std::cout << "This trade doesn't involve any property exchange. Cant do this" << endl;
}

void Transactions::payRent(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, int rent) {
    if(!checkFund(p1, rent)) {
        return;
    }

    p1->pay(rent);
    p2->changeCash(rent);
    std::cout << "The transaction is completed!" << std::endl;
}

void Transactions::payBank(std::shared_ptr<Player> p1, int rent) {
    if(!checkFund(p1, rent)) {
        std::cout << "doesnt have money" << std::endl;

        return;
    }

    p1->pay(rent);
    std::cout << "The transaction is completed!" << std::endl;
}

void Transactions::buyBuilding(std::string property_name, std::shared_ptr<Player> owner) {
    int indexResult = 0;
    for (int i = 0; i < 40; i++) {
        if (property_name == OWNABLE[i][0]) {
            indexResult = i;
            break;
        }
    }
    int buycost = 0;
    for (int i = 0; i < 28; i++){
        if (OWNABLE[i][0] == property_name) {
            buycost = OWNABLE[i][2];
        }
    }
    char owner_symbol = owner->getSymbol();
    if(!checkFund(owner, buycost)) {
        return;
    }

    std::shared_ptr<Building> build;
    if (isGym(property_name)){
        owner->changePropertyCount(0, 1, 0);
        auto production = std::make_shared<Gym>(indexResult, property_name, buycost, owner_symbol);	
        build = std::dynamic_pointer_cast<Building>(production);
    }
    else if (isResidence(property_name)){
        owner->changePropertyCount(1, 0, 0);
	    auto production = std::make_shared<Residence>(indexResult, property_name, buycost, owner_symbol);
        build = std::dynamic_pointer_cast<Building>(production);
    }
    else if (isAcademic(property_name)){
        owner->changePropertyCount(0, 0, 1);
	    auto production = std::make_shared<Academic>(indexResult, property_name, buycost, owner_symbol);
        build = std::dynamic_pointer_cast<Building>(production);
    }

    owner->addProp(build);
    owner->updateMonopolyBlock();
    ownedProperties.push_back(build);
    owner->pay(buycost);

    if (isGym(property_name)){
	    build->setGymLevel(owner->getOwnedGyms() - 1);
    } else if (isResidence(property_name)){
	    build->setResLevel(owner->getOwnedResidences() - 1);
    } else if (isAcademic(property_name)){
        if (owner->checkIfInMonopolyBlock(property_name)){
	        auto acad = std::dynamic_pointer_cast<Academic>(build);
            acad->setOwned(true);
	    }
    }
    std::cout << "The transaction is completed!" << std::endl;
}

void Transactions::sellBuilding(std::string property_name, std::shared_ptr<Player> owner) {
    int indexResult = 0;
    for (int i = 0; i < 40; i++) {
        if (property_name == OWNABLE[i]) {
            indexResult = i;
            break;
        }
    }
    int buycost = 0;
    for (int i = 0; i < 28; i++){
        if (OWNABLE[i][0] == property_name) {
            buycost = OWNABLE[i][2];
        }
    }
    char owner_symbol = owner->getSymbol();
    if(!checkFund(owner, buycost)) {
        return;
    }
    std::shared_ptr<Building> build;
    if (isGym(property_name)){
        owner->changePropertyCount(0, -1, 0);
        auto production = std::make_shared<Gym>(indexResult, property_name, buycost, owner_symbol);	
        build = std::dynamic_pointer_cast<Building>(production);

    }
    else if (isResidence(property_name)){
        owner->changePropertyCount(-1, 0, 0);
	    auto production = std::make_shared<Residence>(indexResult, property_name, buycost, owner_symbol);
        build = std::dynamic_pointer_cast<Building>(production);

    }
    else if (isAcademic(property_name)){
        owner->changePropertyCount(0, 0, -1);
	    auto production = std::make_shared<Academic>(indexResult, property_name, buycost, owner_symbol);
        build = std::dynamic_pointer_cast<Building>(production);

    }
    owner->removeProp(build);
    owner->updateMonopolyBlock();
    auto it = std::find(ownedProperties.begin(), ownedProperties.end(), build);
    if (it != ownedProperties.end()) {
        ownedProperties.erase(it);
    }
    owner->changeCash(buycost);
    
    if (isGym(property_name)){
	    build->setGymLevel(owner->getOwnedGyms() - 1);
    } else if (isResidence(property_name)){
	    build->setResLevel(owner->getOwnedResidences() - 1);
    } else if (isAcademic(property_name)){
        if (owner->checkIfInMonopolyBlock(property_name)){
	        auto acad = std::dynamic_pointer_cast<Academic>(build);
            acad->setOwned(true);
	    }
    }
    std::cout << "The transaction is completed!" << std::endl;
}

void Transactions::buyImprovement(std::shared_ptr<Building> property_name, std::shared_ptr<Player> owner) {
    if (!(owner->ownThisProp(property_name->getName()))) {
        std::cout << "The player " << owner->getName() << " doesn't own this property" << std::endl;
        return;
    }
    int cost = getPropertyCost(property_name->getName());
    if(!checkFund(owner, cost)) {
        return;
    }
    if (isGym(property_name->getName())){
        std::cout << "You can't improve a gym!" << std::endl;
        return;
    }
    if (isResidence(property_name->getName())){
        std::cout << "You can't improve a Residence!" << std::endl;
        return;
    }
    auto acad = std::dynamic_pointer_cast<Academic>(property_name);
    if (!acad->getOwned()){
	    std::cout << "You can't improve this academic building because you don't have a monopoly!" << std::endl;
        return;
    }
    if (acad->getImprLevel() >= 5) {
        std::cout << "you cant do anymore imroves max limit reached" << std::endl;
        return;
    }
    owner->pay(cost);
    property_name->setImprLevel(property_name->getImprLevel() + 1);
    std::cout << "The transaction is completed!" << std::endl;
}

void Transactions::sellImprovement(std::shared_ptr<Building> property_name, std::shared_ptr<Player> owner) {
    if (property_name->getName() == "PAC" || property_name->getName() == "CIF" || 
        property_name->getName() == "MKV" || property_name->getName() == "UWP" || 
        property_name->getName() == "V1" || property_name->getName() == "REV") {
        std::cout << "this is not a academic building" << std::endl;
        return;
    } 

    if (!(owner->ownThisProp(property_name->getName()))) {
        std::cout << "The player " << owner->getName() << " doesn't own this property" << std::endl;
        return;
    }
    if (property_name->getImprLevel() <= 0) {
        std::cout << "there is no improvement to sell" << std::endl;
        return;
    }
    int cost = getPropertyCost(property_name->getName());
    owner->changeCash(cost * 0.5);
    property_name->setImprLevel(property_name->getImprLevel() - 1);
    std::cout << "The transaction is completed!" << std::endl;
}

void Transactions::mortgage(std::shared_ptr<Building> property_name, std::shared_ptr<Player> owner) {
    if (!(owner->ownThisProp(property_name->getName()))) {
        std::cout << "The player " << owner->getName() << " doesn't own this property" << std::endl;
        return;
    }

    if(property_name->getMortStatus()) {
        std::cout << "you cannot mortgage a mortgaged property" << std::endl;
        return;
    }

    int cost = 0;
    for (int i = 0; i < 28; i++) {
        if (OWNABLE[i][0] == property_name) {
            std::stringstream ss(OWNABLE[i][2]);
            ss >> cost;
        }
    }
    cost = cost * 0.5;

    owner->changeCash(cost);
    property_name->setMortStatus(true);
    owner->updateMonopolyBlock();

    if (isAcademic(property_name->getName())){
	    std::shared_ptr<Academic> acad = std::dynamic_pointer_cast<Academic>(property_name);
        if (acad->getOwned()){
	        acad->setOwned(false);
	    }
    } 
    std::cout << "The transaction is completed!" << std::endl;
}

void Transactions::unmortgage(std::shared_ptr<Building> property_name, std::shared_ptr<Player> owner) {
    if (!(owner->ownThisProp(property_name->getName()))) {
        std::cout << "The player " << owner->getName() << " doesn't own this property" << std::endl;
        return;
    }

    if(!property_name->getMortStatus()) {
        std::cout << "you cannot unmortgage an umortgaged property" << std::endl;
        return;
    }

    int cost = 0;
    for (int i = 0; i < 28; i++) {
        if (OWNABLE[i][0] == property_name) {
            std::stringstream ss(OWNABLE[i][2]);
            ss >> cost;
        }
    }
    cost = cost * 0.6;
    if (!checkFund(owner, cost)) return;

    owner->pay(cost);
    property_name->setMortStatus(false);
    owner->updateMonopolyBlock();

    if (isAcademic(property_name->getName())){
	    std::shared_ptr<Academic> acad = std::dynamic_pointer_cast<Academic>(property_name);
        if (acad->getOwned()){
	        acad->setOwned(true);
	    }
    } 
    std::cout << "The transaction is completed!" << std::endl;
}

std::shared_ptr<Building> Transactions::listProp(std::string property_name) {
    std::shared_ptr<Building> result;
    int size = ownedProperties.size();

    for (int i = 0; i < size; i++) {
        if (ownedProperties[i]->getName() == property_name) {
            return ownedList[i];
        }
    }

    return result;
}

void Transactions::addPropByAuction(std::string build, std::shared_ptr<Player> p, int amount) {
    int indexResult = 0;

    for (int i = 0; i < 40; i++) {
        if (build == BOARD[i]) {
            indexResult = i;
            break;
        }
    }
    char owner = p->getSymbol();
    int buycost = 0;
    for (int i = 0; i < 28; i++){
        if (OWNABLE[i][0] == build) {
            buycost = OWNABLE[i][2];
        }
    }
    std::shared_ptr<Building> ownable;
    if (isGym(build)){
        auto production = std::make_shared<Gym>(indexResult, build, buycost, owner);
        ownable = std::dynamic_pointer_cast<Building>(production);
    }
    else if (isResidence(build)){
        auto production = std::make_shared<Residence>(indexResult, build, buycost, owner);
        ownable = std::dynamic_pointer_cast<Building>(production);
    }
    else if (isAcademic(build)){
        auto production = std::make_shared<Academic>(indexResult, build, buycost, owner);
        ownable = std::dynamic_pointer_cast<Building>(production);
    }

    p->addProp(ownable);
    p->updateMonopolyBlock();
    ownedProperties.push_back(ownable);
    p->pay(amount);

    if (isGym(build)){
        ownable->setGymLevel(p->getOwnedGyms() - 1);
    } else if (isResidence(build)){
        ownable->setResLevel(p->getOwnedResidences() - 1);
    } else if (isAcademic(build)){
        auto acad = std::dynamic_pointer_cast<Academic>(ownable);
        if (p->checkIfInMonopolyBlock(build)){
            acad->setOwned(true);
        }
    }
    std::cout << "The transaction is completed!" << std::endl;
}
