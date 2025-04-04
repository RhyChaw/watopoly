#include "transaction.h"
#include "propertyArray.h"
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
    return -1; 
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
        std::cout << "The player " << p1->getName() << " doesn't have enough funds to use." << std::endl;
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
    std::cout << "Transferred " << building->getName() << " from " << from->getName() << " to " << to->getName() << "." << std::endl;
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

void Transactions::trade3(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, double money, std::shared_ptr<Building> build) {
    if (p1->getCash() < money) {
        std::cout << "The player " << p1->getName() << " doesn't have enough money." << std::endl;
        return;
    }
    if (!(p2->ownThisProp(build->getName()))) {
        std::cout << "The player " << p2->getName() << " doesn't own this property." << std::endl;
        return;
    }
    if (build->getImprLevel() != 0) {
        std::cout << "There are improvements on this property." << std::endl;
        return;
    }

    string choice;
    while (true) {
        std::cout << p2->getName() << ", do you accept this trade offer? [ YES / NO ]: ";
        std::cin >> choice;

        std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

        if (choice == "yes" || choice == "y") {
            // Proceed with the trade
            for (int i = 0; i < 22; i++) {
                if (OWNABLE[i][0] == build->getName()) {
                    auto acad = std::dynamic_pointer_cast<Academic>(build);
                    if (acad->getOwned()) {
                        acad->setOwned(false);
                    }
                }
            }

            // the transaction occurs if all checks pass
            p1->pay(money);
            p2->removeProp(build);
            p1->addProp(build);
            p2->changeCash(money);
            std::cout << "Transferred " << build->getName() << " from " << p1->getName() << " to " << p2->getName() << std::endl;

            // Update Monopoly blocks of both players
            p1->updateMonopolyBlock();
            p2->updateMonopolyBlock();
            int size = ownedProperties.size();
            for (int i = 0; i < size; i++) {
                if (ownedProperties[i]->getName() == build->getName()) {
                    ownedProperties[i]->setOwner(p1->getSymbol());
                }
            }

            // Set correct pay level and tuition
            if (isGym(build->getName())) {
                build->setGymLevel(p2->getOwnedGyms() - 1);
            } else if (isResidence(build->getName())) {
                build->setResLevel(p2->getOwnedResidences() - 1);
            } else if (isAcademic(build->getName())) {
                if (p1->checkIfInMonopolyBlock(build->getName())) {
                    auto acad = std::dynamic_pointer_cast<Academic>(build);
                    acad->setOwned(true);
                }
            }
            std::cout << "The transaction is completed!" << std::endl;
            break;  
        } else if (choice == "no" || choice == "n") {
            std::cout << "The transaction was rejected!" << std::endl;
            break; 
        } else {
            std::cout << "Please select a valid option [ YES / NO ]!" << std::endl;
        }
    }
}

void Transactions::trade1(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<Building> building1, std::shared_ptr<Building> building2) {
    if (!(p2->ownThisProp(building2->getName()))) {
        std::cout << "The player " << p2->getName() << " doesn't own this property." << std::endl;
        return;
    }

    if (!(p1->ownThisProp(building1->getName()))) {
        std::cout << "The player " << p1->getName() << " doesn't own this property." << std::endl;
        return;
    }
    if (building1->getImprLevel() != 0) {
        std::cout << "There are improvements on this property." << std::endl;
        return;
    }

    if (building2->getImprLevel() != 0) {
        std::cout << "There are improvements on this property." << std::endl;
        return;
    }

    string choice;
    while (true) {
        std::cout << p2->getName() << ", do you accept this trade offer? [ YES / NO ]: ";
        std::cin >> choice;

        // Convert input to lowercase to handle case insensitivity
        std::transform(choice.begin(), choice.end(), choice.begin(), ::tolower);

        if (choice == "yes" || choice == "y") {
            // Proceed with the trade

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

            p2->removeProp(building2);
            p1->addProp(building2);
            p1->removeProp(building1);
            p2->addProp(building1);

            // Update Monopoly blocks of both players
            p1->updateMonopolyBlock();
            p2->updateMonopolyBlock();
            int size = ownedProperties.size();
            for (int i = 0; i < size; i++) {
                if (ownedProperties[i]->getName() == building1->getName()) {
                    ownedProperties[i]->setOwner(p2->getSymbol());
                }
            }
            for (int i = 0; i < size; i++) {
                if (ownedProperties[i]->getName() == building2->getName()) {
                    ownedProperties[i]->setOwner(p1->getSymbol());
                }
            }

            if (isGym(building2->getName())) {
                building2->setGymLevel(p2->getOwnedGyms() - 1);
            } else if (isResidence(building2->getName())) {
                building2->setResLevel(p2->getOwnedResidences() - 1);
            } else if (isAcademic(building2->getName())) {
                if (p2->checkIfInMonopolyBlock(building2->getName())) {
                    auto acad = std::dynamic_pointer_cast<Academic>(building2);
                    acad->setOwned(true);
                }
            }

            if (isGym(building1->getName())) {
                building1->setGymLevel(p1->getOwnedGyms() - 1);
            } else if (isResidence(building1->getName())) {
                building1->setResLevel(p1->getOwnedResidences() - 1);
            } else if (isAcademic(building1->getName())) {
                if (p1->checkIfInMonopolyBlock(building1->getName())) {
                    auto acad = std::dynamic_pointer_cast<Academic>(building1);
                    acad->setOwned(true);
                }
            }
            std::cout << "The transaction is completed!" << std::endl;
            break;  
        } else if (choice == "no" || choice == "n") {
            std::cout << "The transaction was rejected!" << std::endl;
            break;  
        } else {
            // Invalid input, prompt again
            std::cout << "Please select a valid option [ YES / NO ]!" << std::endl;
        }
    }
}

void Transactions::trade2(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, std::shared_ptr<Building> building, double money) {
    Transactions::trade3(p2, p1, money, building); 
}

void Transactions::trade4(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, double money1, double money2) {
    std::cout << "This trade doesn't involve any property exchange. Cant do this" << endl;
}

bool Transactions::payRent(std::shared_ptr<Player> p1, std::shared_ptr<Player> p2, int rent) {
    if(!checkFund(p1, rent)) {
        return false;
    }

    p1->pay(rent);
    p2->changeCash(rent);
    std::cout << "The transaction is completed!" << std::endl;
    return true;
}

bool Transactions::payBank(std::shared_ptr<Player> p1, int rent) {
    if(!checkFund(p1, rent)) {
        std::cout << "doesnt have money!" << std::endl;

        return false;
    }

    p1->pay(rent);
    std::cout << "The transaction is completed!" << std::endl;
    return true;
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
            std::stringstream ss(OWNABLE[i][2]);
            ss >> buycost;
        }
    }
    char owner_symbol = owner->getSymbol();
    if(!checkFund(owner, buycost)) {
        return;
    }


    std::shared_ptr<Building> build;
    if (isGym(property_name)){
        auto production = std::make_shared<Gym>(indexResult, property_name, buycost, owner_symbol);	
        build = std::dynamic_pointer_cast<Building>(production);
    }

    else if (isResidence(property_name)){
	    auto production = std::make_shared<Residence>(indexResult, property_name, buycost, owner_symbol);
        build = std::dynamic_pointer_cast<Building>(production);
    }
    else if (isAcademic(property_name)){
	    auto production = std::make_shared<Academic>(indexResult, property_name, buycost, owner_symbol);
        build = std::dynamic_pointer_cast<Building>(production);
    }

    owner->addProp(build);
    owner->updateMonopolyBlock();
    ownedProperties.push_back(build);
    owner->pay(buycost);
    owner->setGymsOwned();
    owner->setResOwned();


    if (isGym(property_name)){
	    build->setGymLevel(owner->getOwnedGyms());
    } else if (isResidence(property_name)){
	    build->setResLevel(owner->getOwnedResidences());
    } else if (isAcademic(property_name)){
        if (owner->checkIfInMonopolyBlock(property_name)){
	        auto acad = std::dynamic_pointer_cast<Academic>(build);
            acad->setOwned(true);
	    }
    }
    std::cout << "The transaction is completed!" << std::endl;
}

void Transactions::setowned(std::shared_ptr<Building> build) {
    ownedProperties.push_back(build);
}

void Transactions::sellBuilding(std::string property_name, std::shared_ptr<Player> owner) {
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
            std::stringstream ss(OWNABLE[i][2]);
            ss >> buycost;
            break;
        }
    }
    char owner_symbol = owner->getSymbol();
    if(!checkFund(owner, buycost)) {
        return;
    }
    std::shared_ptr<Building> build;
    if (isGym(property_name)){
        auto production = std::make_shared<Gym>(indexResult, property_name, buycost, owner_symbol);	
        build = std::dynamic_pointer_cast<Building>(production);

    }
    else if (isResidence(property_name)){
	    auto production = std::make_shared<Residence>(indexResult, property_name, buycost, owner_symbol);
        build = std::dynamic_pointer_cast<Building>(production);

    }
    else if (isAcademic(property_name)){
	    auto production = std::make_shared<Academic>(indexResult, property_name, buycost, owner_symbol);
        build = std::dynamic_pointer_cast<Building>(production);

    }
    owner->removeProp(build);
    owner->updateMonopolyBlock();

    auto it = std::find_if(ownedProperties.begin(), ownedProperties.end(),
    [&build](const std::shared_ptr<Building>& prop) {
        return prop == build;
    });

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

bool Transactions::buyImprovement(std::shared_ptr<Building> property_name, std::shared_ptr<Player> owner) {
    if (!(owner->ownThisProp(property_name->getName()))) {
        std::cout << "The player " << owner->getName() << " doesn't own this property" << std::endl;
        return false;
    }
    if (isGym(property_name->getName())){
        std::cout << "You can't improve a gym!" << std::endl;
        return false;
    }
    if (isResidence(property_name->getName())){
        std::cout << "You can't improve a Residence!" << std::endl;
        return false;
    }
    int cost = getPropertyCost(property_name->getName());
    if(!checkFund(owner, cost)) {
        return false;
    }
    auto acad = std::dynamic_pointer_cast<Academic>(property_name);
    if (!owner->checkIfInMonopolyBlock(property_name->getName())){
	    std::cout << "You can't improve this academic building because you don't have a monopoly!" << std::endl;
        return false;
    }
    if (acad->getImprLevel() >= 5) {
        std::cout << "you cant do anymore imroves max limit reached" << std::endl;
        return false;
    }
    owner->pay(cost);
    property_name->setImprLevel(property_name->getImprLevel() + 1);
    std::cout << "The transaction is completed!" << std::endl;
    return true;
}

bool Transactions::sellImprovement(std::shared_ptr<Building> property_name, std::shared_ptr<Player> owner) {
    if (property_name->getName() == "PAC" || property_name->getName() == "CIF" || 
        property_name->getName() == "MKV" || property_name->getName() == "UWP" || 
        property_name->getName() == "V1" || property_name->getName() == "REV") {
        std::cout << "this is not a academic building" << std::endl;
        return false;
    } 

    if (!(owner->ownThisProp(property_name->getName()))) {
        std::cout << "The player " << owner->getName() << " doesn't own this property" << std::endl;
        return false;
    }
    if (property_name->getImprLevel() <= 0) {
        std::cout << "there is no improvement to sell" << std::endl;
        return false;
    }
    int cost = getPropertyCost(property_name->getName());
    owner->changeCash(cost * 0.5);
    property_name->setImprLevel(property_name->getImprLevel() - 1);
    std::cout << "The transaction is completed!" << std::endl;
    return true;
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
        if (OWNABLE[i][0] == property_name->getName()) { 
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
        if (OWNABLE[i][0] == property_name->getName()) {
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
            return ownedProperties[i];
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
    
    int buycost = 0;
    char owner = p->getSymbol();
    for (int i = 0; i < 28; i++){
        if (OWNABLE[i][0] == build) {
            std::stringstream ss(OWNABLE[i][2]);
            ss >> buycost;
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
    ownable->setOwner(p->getSymbol());
    int size = ownedProperties.size();
    for (int i = 0; i < size; i++) {
        if (ownedProperties[i]->getName() == build) {
            ownedProperties[i]->setOwner(p->getSymbol());
        }
    }

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
