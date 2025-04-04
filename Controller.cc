#include "Controller.h"

Controller::Controller() {}

Controller::~Controller() {}
using namespace std;

void Controller::commandTrade(std::vector<std::shared_ptr<Player>> group, std::shared_ptr<Player> currActingPlayer) {
    char piece;
    
    int groupSize = group.size(); 
    std::cout << "available players to trade with. " << endl;
    for (int i = 0; i < groupSize; i++) {
        if (group[i] == currActingPlayer) continue;
        std::cout << "name: " << group[i]->getName() << " piece: " << group[i]->getSymbol() << endl;
    }

    std::shared_ptr<Player> p;
    while (true) {
        std::cout << "Enter the symbol of the player: ";
        std::cin >> piece;
        
        int i = 0;
        while (i < groupSize) {
            if (group[i]->getSymbol() == piece) {
                p = group[i];
                break;
            }
            i++;
        }
        
        if (i == groupSize) {
            std::cout << "Invalid player symbol" << std::endl;
        } else {
            break;
        }
    }

    std::cout << "initiating trading with: " << p->getSymbol() << std::endl;

    // Get what user is offering
    std::cout << "Enter what you want to offer (money or property name): " << std::endl;
    for (const auto &prop : currActingPlayer->getOwnedPropList()) {
        std::cout << prop->getName() << " ";
    }
    std::cout << std::endl;

    std::string offerStr, wantStr;

    auto isValidOffer = [&](const std::string &str) {
        if (isdigit(str[0])) return true;
        for (const auto &prop : currActingPlayer->getOwnedPropList()) {
            if (prop->getName() == str) return true;
        }
        return false;
    };

    while (true) {
        std::cin >> offerStr;
        if (isValidOffer(offerStr)) break;
        std::cout << "Invalid input. Enter a valid amount or property name: ";
    }

    std::cout << "Enter what you want in return (money or property name): " << std::endl;
    for (const auto &prop : p->getOwnedPropList()) {
        std::cout << prop->getName() << " ";
    }
    std::cout << std::endl;

    auto isValidRequest = [&](const std::string &str) {
        if (isdigit(str[0])) return true;  
        for (const auto &prop : p->getOwnedPropList()) {
            if (prop->getName() == str) return true;
        }
        return false;
    };

    while (true) {
        std::cin >> wantStr;
        if (isValidRequest(wantStr)) break;
        std::cout << "Invalid input. Enter a valid amount or property name: ";
    }


    std::cout << std::endl;


    bool b1 = false;
    bool b2 = false;


    for (int i = 0; i < 28; i++) {
        if (OWNABLE[i][0] == offerStr) {
            b1 = true;
        }
        if (OWNABLE[i][0] == wantStr) {
            b2 = true;
        }
    }

    if (b1 && b2) {
        Transactions::trade1(currActingPlayer, p, Transactions::listProp(offerStr), Transactions::listProp(wantStr));
    } 
    else if (b1) {
        std::shared_ptr<Building> offerProp = Transactions::listProp(offerStr);
        double wantMoney;
        try {
            wantMoney = std::stod(wantStr);
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error: Invalid money input." << std::endl;
            return;
        }
        Transactions::trade2(currActingPlayer, p, offerProp, wantMoney);
    } 
    else if (b2) {
        std::shared_ptr<Building> wantProp = Transactions::listProp(wantStr);
        double offerMoney;
        try {
            offerMoney = std::stod(offerStr);
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error: Invalid money input." << std::endl;
            return;
        }
        Transactions::trade3(currActingPlayer, p, offerMoney, wantProp);
    } 
    else {
        double offerMoney, wantMoney;
        try {
            offerMoney = std::stod(offerStr);
            wantMoney = std::stod(wantStr);
        } catch (const std::invalid_argument &e) {
            std::cerr << "Error: Invalid money input." << std::endl;
            return;
        }
        Transactions::trade4(currActingPlayer, p, offerMoney, wantMoney);
    }
}

//handle when in these code segments the input is invalid.
void Controller::commandAuction(std::vector<std::shared_ptr<Player>> group, std::shared_ptr<Player> currActingPlayer, std::string prop) {
    auto newAuction = std::make_shared<Auction>(group, currActingPlayer, prop);

    std::cout << "========== PROPERTY AUCTION ==========" << endl;
    std::cout << "Auctioning: " << prop << endl;
    int cost = 0;
    for (int i = 0; i < 28; i ++) {
        if (OWNABLE[i][0] == prop) {
            cost = std::stoi(OWNABLE[i][2]);
        }
    }
    std::cout << "Original Price: " << cost << endl;
    std::cout << "Starting auction process..." << endl;
    std::vector<bool> withdrawnPlayers(group.size(), false);
    int currentPlayerIndex = std::find(group.begin(), group.end(), currActingPlayer) - group.begin();
    withdrawnPlayers[currentPlayerIndex] = false;
    int currentBidderIndex = (currentPlayerIndex) % group.size();
    while (true) {
        while (withdrawnPlayers[currentBidderIndex]) {
            currentBidderIndex = (currentBidderIndex + 1) % group.size();
        }
        int activePlayerCount = 0;
        for (bool withdrawn : withdrawnPlayers) {
            if (!withdrawn) activePlayerCount++;
        }
        if (activePlayerCount <= 1) {
            break;
        }
        auto currentBidder = group[currentBidderIndex];
        
        std::cout << "Current bidder: " << currentBidder->getName() << endl;
        std::cout << "Current highest bid: $" << newAuction->getMaxBid() << endl;
        string action;
        std::cout << "Do you want to [ RAISE ] or [ WITHDRAW ]? ";
        std::cin >> action;
        if (action == "raise" || action == "RAISE") {
            int bidAmount;
            std::cout << "Enter your bid amount: ";
            while (true) {
                std::cin >> bidAmount;
                if (std::cin.fail()) {
                    std::cin.clear();
                    std::cin.ignore(10000, '\n');
                    std::cout << "Invalid bid. Enter a valid integer amount: ";
                } else {
                    std::cin.ignore();
                    break;
                }
            }
            newAuction->place(currentBidder, bidAmount);
        } 
        else if (action == "withdraw" || action == "WITHDRAW") {
            withdrawnPlayers[currentBidderIndex] = true;
            newAuction->withdraw(currentBidder);
        } 
        else {
            std::cout << "Invalid action. Please choose 'raise' or 'withdraw'." << endl;
            continue;
        }
        currentBidderIndex = (currentBidderIndex + 1) % group.size();
    }

    int remainingBidders = 0;
    for (bool withdrawn : withdrawnPlayers) {
        if (!withdrawn) remainingBidders++;
    }
    if (remainingBidders == 1) {
        std::cout << "Auction completed successfully!" << endl;
    } else {
        std::cout << "Auction ended without a winner." << endl;
    }
}


void Controller::commandImprove(std::vector<std::shared_ptr<Player>> group, std::shared_ptr<Player> currActingPlayer, std::shared_ptr<GameBoard> b) {
    string prop, action;
    auto isValidProperty = [&](const std::string &str) {
        for (const auto &property : currActingPlayer->getOwnedPropList()) {
            if (property->getName() == str) return true;
        }
        return false;
    };
    int size = currActingPlayer->getOwnedPropList().size();
    if (size == 0) {
        cout << "you dont have any properties to improve" << endl;
        cout << endl;
        return;
    }
    std::cout << currActingPlayer->getSymbol() << " please choose a property to improve" << endl;
    for (int i = 0; i < size; i++) {
        std::cout << currActingPlayer->getOwnedPropList()[i]->getName() << endl; 
    }
    while (true) {
        std::cin >> prop;
        if (isValidProperty(prop)) break;
        std::cout << "Invalid property. Please enter a valid property name: ";
    }

    std::cout << "do you wanna [ BUY ]/[ SELL ]?" << endl;

    std::cin >> action;

    while (true) {
        if (action == "buy" || action == "BUY" || action == "SELL"|| action == "sell" || std::cin.fail()) break;
        std::cout << "command not recognized" << endl;
        std::cout << "please select buy or sell" << endl;
        std::cin >> action;
    }
    shared_ptr<Building> p;
    p = Transactions::listProp(prop);
    if (action == "buy" || action == "BUY") {
        if (Transactions::buyImprovement(p, currActingPlayer)) {
            b->addImpr(p->getName());
            b->drawBoard();
        }
    }
    else if (action == "sell" || action == "SELL") {
        if(Transactions::sellImprovement(p, currActingPlayer)) {
            b->removeImpr(p->getName());
            b->drawBoard();
        }

    }
}

void Controller::commandMortgage(std::shared_ptr<Player> currActingPlayer) {
    auto isValidProperty = [&](const std::string &str) {
        for (const auto &property : currActingPlayer->getOwnedPropList()) {
            if (property->getName() == str) return true;
        }
        return false;
    };
    std::cout << currActingPlayer->getSymbol() << "what do you want to mortgage" << endl;
    int size = currActingPlayer->getOwnedPropList().size();
    for (int i = 0; i < size; i++) {
        std::cout << currActingPlayer->getOwnedPropList()[i]->getName() << endl; 
    }
    string item;
    while (true) {
        std::cin >> item;
        if (isValidProperty(item)) break;
        std::cout << "Invalid property. Please enter a valid property name: ";
    }

    shared_ptr<Building> p;
    p = Transactions::listProp(item);
    Transactions::mortgage(p, currActingPlayer);
}

void Controller::commandUnmortgage(std::shared_ptr<Player> currActingPlayer) {
    auto isValidProperty = [&](const std::string &str) {
        for (const auto &property : currActingPlayer->getOwnedPropList()) {
            if (property->getName() == str) return true;
        }
        return false;
    };
    std::cout << currActingPlayer->getSymbol() << "what do you want to unmortgage" << endl;
    int size = currActingPlayer->getOwnedPropList().size();
    for (int i = 0; i < size; i++) {
        std::cout << currActingPlayer->getOwnedPropList()[i]->getName() << endl; 
    }
    string item;
    while (true) {
        std::cin >> item;
        if (isValidProperty(item)) break;
        std::cout << "Invalid property. Please enter a valid property name: ";
    }
    shared_ptr<Building> p;
    p = Transactions::listProp(item);
    Transactions::unmortgage(p, currActingPlayer);
}

void Controller::commandBankrupt(std::shared_ptr<Player> currActingPlayer, std::shared_ptr<Player> owner, std::vector<std::shared_ptr<Player>> group) {
    currActingPlayer->setBankrupt(true);
    owner->changeCash(currActingPlayer->getCash());
    currActingPlayer->changeCash(-(currActingPlayer->getCash()));
    vector<shared_ptr<Building>> prop = currActingPlayer->getOwnedPropList();
    int size = prop.size();
    char piece = owner->getSymbol();
    for (int i = 0; i < size; i++){
        owner->addProp(prop[i]);
        prop[i]->setOwner(piece);
    }
}

void Controller::CommandRoll(std::vector<std::shared_ptr<Player>> group, std::shared_ptr<Player> currActingPlayer, bool testMode, std::shared_ptr<GameBoard> b) {
    
    auto pointerOfPlayer = [group](char trackingPiece) {
        int sizeGroup = group.size();
        shared_ptr<Player> result;
        for (int i = 0; i < sizeGroup; i++)
        {
            if (group[i]->getSymbol() == trackingPiece)
            {
                return group[i];
            }
        }
        return result;
    };

    string sq = currActingPlayer->getSquareAtCurrPos();
    bool flag = false;

    for (int i = 0; i < 28; i++) {
        if (sq == OWNABLE[i][0])
        flag = true;
    }
    if (flag) { 
        if (Transactions::isOwned(sq)) { 
            shared_ptr<Building> prop = Transactions::listProp(sq);
            shared_ptr<Player> owner = pointerOfPlayer(prop->getOwner());

            int rollValue = 0;

            if (owner == currActingPlayer) {
                std::cout << "you own this property, no need to pay rent" << endl;
            } else if (owner != currActingPlayer && !prop->getMortStatus()) {
                std::cout << "the property belongs to " << owner->getName() << endl;
                if (isGym(prop->getName())) {
                    std::cout << "landed on the gym, you have to roll to see what rent you will have to pay" << endl;
                    auto gym = std::dynamic_pointer_cast<Gym>(prop);
                    std::cout << "please type roll" << endl;
                    string command;
                    std::cin >> command;
                    while (command != "roll" || command != "ROLL") {
                        std::cout << "Sorry, you have to roll first." << endl;
                        std::cin >> command;
                    }
                    bool overload = false;
                    if (testMode) {
                        std::cout << "First die: " << std::endl;
                        std::string d1, d2;
                        auto isValidNumber = [](const std::string &str) {
                            return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
                        };

                        while (true) {
                            std::cin >> d1;
                            if (isValidNumber(d1)) break;
                            std::cout << "Invalid input. Enter a valid number for the first die: ";
                        }

                        std::cout << "Second die: " << std::endl;

                        while (true) {
                            std::cin >> d2;
                            if (isValidNumber(d2)) break;
                            std::cout << "Invalid input. Enter a valid number for the second die: ";
                        }

                        rollValue = std::stoi(d1) + std::stoi(d2);
                        overload = true;
                        gym->setRoll(rollValue);
                    }
                    if (!overload) {
                        auto twoDices = make_unique<Dice>();
                        twoDices->roll();
                        std::cout << "Rolling your dice..." << endl;
                        std::cout << twoDices->getFirstDie() << " + ";
                        std::cout << twoDices->getSecondDie() << " = ";
                        std::cout << twoDices->getSum() << "!" << endl;
                        gym->setRoll(twoDices->getSum());
                    }
                }
                int rent = 0;
                if (isGym(prop->getName())) {
                    auto gym = std::dynamic_pointer_cast<Gym>(prop);
                    int gymsOwned = owner->countGymsOwned();
                    rent = (gymsOwned == 1) ? (rollValue * 4) : (rollValue * 10);
                    cout << "Rent for " << gym->getName() << ": $" << rent << endl;
                }
                if (isResidence(prop->getName())) {
                    auto res = std::dynamic_pointer_cast<Residence>(prop);
                    int resOwned = owner->countResOwned();
                    rent = 25;
                    for (int i = 0; i < resOwned - 1;i ++) {
                        rent*=2;
                    }
                    cout << "Rent for " << res->getName() << ": $" << rent << endl;
                }
                if (isAcademic(prop->getName())) {
                    rent = prop->amountToPay();
                    cout << "Rent for " << prop->getName() << ": $" << rent << endl;
                }
                while (!Transactions::payRent(currActingPlayer, owner, rent)) {
                    std::cout << "you must sell or trade something, or declare bankruptcy, you cant continue " << endl;
                    std::cout << "Avaliable commands - [ TRADE , MORTGAGE, IMPROVE, BANKRUPT ]" << endl;
                    std::cout << "you can write, [ALL] to see your net worth" << endl;
                    std::cout << endl;
                    string command;
                    std::cin >> command;
                    if (command == "bankrupt" || command == "BANKRUPT") {
                        currActingPlayer->setBankrupt(true);
                        commandBankrupt(currActingPlayer, owner, group);
                        break;
                    }
                    else if (command == "trade" || command == "TRADE")
                    {
                        commandTrade(group, currActingPlayer);
                    }
                    else if (command == "mortgage" || command == "MORTGAGE")
                    {
                        commandMortgage(currActingPlayer);
                    }
                    else if (command == "improve" || command == "IMPROVE")
                    {
                        commandImprove(group, currActingPlayer, b);
                    } else if (command == "all" || command == "ALL") {
                        currActingPlayer->printAsset();
                    } else {
                        std::cout << "invalid command, please try again" << endl; 
                    }
                }
                if (!currActingPlayer->getisBankrupt()){
                    std::cout << "rent paid successfully" << endl;
                }
            }
        }
        else { 
            int howMuch = 0;
            for (int i = 0; i < 28; i ++) {
                if (OWNABLE[i][0] == sq) {
                    howMuch = std::stoi(OWNABLE[i][2]);
                }
            }
            std::cout << "You have landed on " << sq << endl;
            std::cout << "this property is available to buy, it costs: $" << howMuch << endl;
            std::cout << "type [ BUY ] or [ AUCTION ] to proceed accordingly" << endl;
            string input;
            while (true) {
                std::cin >> input;
                if (input == "buy" || input == "auction" || input == "BUY" || input == "AUCTION") {
                    break;
                } else {
                    std::cout <<"it has to be one of those commands - [ BUY ] or [ AUCTION ]" << endl;
                }
            }
            if (input == "buy" || input == "BUY"){
                while (currActingPlayer->getCash() < howMuch) {
                    std::cout << "you must auction, trade, mortgage, improve one of your properties, you cant afford it, you cant continue without choosing" << endl;
                    std::cout << "Available commands: [AUCTION, TRADE, MORTGAGE, IMPROVE, ALL]" << endl;
                    string cand;
                    std::cin >> cand;
                    if (cand == "auction" || cand == "AUCTION") {
                        commandAuction(group, currActingPlayer, sq);
                        break;
                    }
                    else if (cand == "trade" || cand == "TRADE")
                    {
                        commandTrade(group, currActingPlayer);

                    }
                    else if (cand == "mortgage" || cand == "MORTGAGE")
                    {
                        commandMortgage(currActingPlayer);

                    }
                    else if (cand == "improve" || cand == "IMPROVE")
                    {
                        commandImprove(group, currActingPlayer, b);
                    } else if (cand == "all" || cand == "ALL") {
                        cout <<endl;
                        currActingPlayer->printAsset();
                        cout <<endl;
                    }
                }
                if (currActingPlayer->getCash() > howMuch) {
                    Transactions::buyBuilding(sq, currActingPlayer);
                }
            }
            else {
                commandAuction(group, currActingPlayer, sq);
            }
        }
    }
    else { 
        if (sq == "SLC"){
            std::cout << "You are at SLC" << endl;
            SLC::moveeee(currActingPlayer, group);
            b->movePlayer(currActingPlayer->getSymbol(), currActingPlayer->getPosition());
            b->drawBoard();
            CommandRoll(group, currActingPlayer, testMode, b);
        } 
        else if (sq == "DC Tims Line"){
            std::cout << "you are at DC Tim Line" << endl;
        } 
        else if (sq == "GO TO TIMS") {
            GetInTim::goToJail(currActingPlayer);
            b->movePlayer(currActingPlayer->getSymbol(), 10);
            b->update();
        } else if (sq == "NEEDLES HALL") {
            std::cout << "You are at Needles Hall." << endl;
            NeedlesHall::moveeee(currActingPlayer, group);
        } else {  
            if (sq == "TUITION"){
                Tuition::pay(currActingPlayer);
            } else if (sq == "COOP FEE"){
                CoopFee::pay(currActingPlayer);
            } else if (sq == "Goose Nesting"){
                GooseNesting::nesting(currActingPlayer);
            } 
        } 
    }
    if (currActingPlayer->getCash() < 0) {
        std::cout<< "your cash after the move is in negative now" << endl;
        while (currActingPlayer->getCash() < 0) {
            std::cout<< "you must trade, mortgage, improve one of your properties, you cant continue without choosing" << endl;
            std::cout<< "you can write, [ALL] to see your net worth " << endl;
            std::cout<< "you can write, [BANKRUPT] to get out " << endl;

            string cand;
            std::cin >> cand;
            if (cand == "trade" || cand == "TRADE")
            {
                commandTrade(group, currActingPlayer);

            }
            else if (cand == "mortgage" || cand == "MORTGAGE")
            {
                commandMortgage(currActingPlayer);

            }
            else if (cand == "improve" || cand == "IMPROVE")
            {
                commandImprove(group, currActingPlayer, b);
            } else if (cand == "all" || cand == "ALL") {
                cout <<endl;
                currActingPlayer->printAsset();
                cout <<endl;
            } else if (cand == "bankrupt" || cand == "BANKRUPT") {
                currActingPlayer->setBankrupt(true);
                auto it = std::remove_if(group.begin(), group.end(),
                    [currActingPlayer](const std::shared_ptr<Player>& p) {
                        return p == currActingPlayer;
                    });
                group.erase(it, group.end());
                vector<shared_ptr<Building>> props = currActingPlayer->getOwnedPropList();
                for (auto& prop : props) {
                    if (!group.empty()) {
                        // Start auction with 1st valid player here...
                        commandAuction(group, group[0], prop->getName()); 
                    }
                }

                b->removePlayer(currActingPlayer->getSymbol());
                std::cout << "Moving to next player!" << endl;
                break;
            }
        }
    } 
}

void Controller::letTheGameBegin(int argc, char **argv) {
    std::cout << "*********************************" << endl;
    std::cout << "---     WATOPOLY PROJECT      ---" << endl;
    std::cout << "*********************************" << endl;
    vector<char> pieceCharTaken;
    string command, name, give, receive, property, action, filename;
    auto b = std::make_shared<GameBoard>();
    bool testMode = false;
    vector<shared_ptr<Player>> group;
    if (argc > 1) {

        if(std::string(argv[1]) == "LOAD" || std::string(argv[1]) == "load") {
            std::cout << "loading a saved game " << endl;
            std::ifstream f{std::string(argv[2])};

            int num;
            f >> num;

            for (int i = 0; i < num; i++) {
                string name;
                char piece;
                int cup;
                int cash;
                int pos;
                f >> name;
                f >> piece;
                f >> cup;
                f >> cash;
                f >> pos;
                auto p = std::make_shared<Player>(name, piece, cash);
                p->setCups(cup);
                b->addPlayer(piece);
                if (pos == 10) {
                    bool in;
                    f >> in;
                    if (in) {
                        int turn;
                        f >> turn;
                        p->setTurnsInTims(turn);
                        b->movePlayer(piece, 10);
                        p->moveToDCTims();
                    } else {
                        p->movePlayer(pos); 
                        b->movePlayer(piece, pos);
                    }
                } else {
                    p->movePlayer(pos); 
                    b->movePlayer(piece, pos);
                }
                group.push_back(p);
            }

            for (int i = 0; i < 28; i++) {
                string property_name;
                string owner;
                int imp;
                f >> property_name;
                f >> owner;
                f >> imp;

                if (owner != "BANK") {
                    int playerIndex = -1;
                    for (int j = 0; j < num; j++) {
                        if (group[j]->getName() == owner) {
                            playerIndex = j;
                            break;
                        }
                    }

                    int propertyIndex = -1;
                    for (int k = 0; k < 40; k++) {
                        if (property_name == OWNABLE[k][0]) {
                            propertyIndex = k;
                            break;
                        }
                    }

                    int buycost = 0;
                    for (int l = 0; l < 28; l++) {
                        if (OWNABLE[l][0] == property_name) {
                            std::stringstream ss(OWNABLE[l][2]);
                            ss >> buycost;
                            break;
                        }
                    }

                    char owner_symbol = group[playerIndex]->getSymbol();
                    std::shared_ptr<Building> build;
                    if (isGym(property_name)) {
                        auto production = std::make_shared<Gym>(propertyIndex, property_name, buycost, owner_symbol);	
                        build = std::dynamic_pointer_cast<Building>(production);
                        group[playerIndex]->setGymsOwned();
                    } else if (isResidence(property_name)) {
                        auto production = std::make_shared<Residence>(propertyIndex, property_name, buycost, owner_symbol);
                        build = std::dynamic_pointer_cast<Building>(production);
                        group[playerIndex]->setResOwned();
                    } else if (isAcademic(property_name)) {
                        auto production = std::make_shared<Academic>(propertyIndex, property_name, buycost, owner_symbol);
                        build = std::dynamic_pointer_cast<Building>(production);
                    }

                    group[playerIndex]->addProp(build);
                    Transactions::setowned(build);
                    if (imp == -1) {
                        build->setMortStatus(true);
                    } else {
                        build->setImprLevel(imp); 
                    }
                    b->addImpr(property_name, imp);
                }

                // gym stuff
                for (auto& player : group) {
                    int gymCount = 0;
                    for (const auto& prop : player->getOwnedPropList()) {
                        if (isGym(prop->getName())) gymCount++;
                    }
                    for (auto& prop : player->getOwnedPropList()) {
                        if (isGym(prop->getName())) {
                            prop->setGymLevel(gymCount);
                        }
                    }
                }

                // Update every player's monopoly block and the amount they need to pay
                for (int m = 0; m < num; m++) {
                    group[m]->updateMonopolyBlock();
                    group[m]->loadUpdateAmountToPay();
                }

                // Display assets of every player
                std::cout << "Displaying assets of every player, so everyone is on track" << std::endl;
                for (int m = 0; m < num; m++) {
                    group[m]->getAsset();
                }

                // Draw the game board
                b->drawBoard();
            }
            if (argc > 3 && (std::string(argv[3]) == "TEST" || std::string(argv[3]) == "test")) {
                testMode = true;
                std::cout << "currently playing in test mode" << endl;
            }

        }
        if (std::string(argv[1]) == "TEST" || std::string(argv[1]) == "test"){
            testMode = true;
            std::cout << "currently playing in test mode" << endl;
        } 
        if(std::string(argv[1]) != "LOAD" && std::string(argv[1]) != "load") {
            std::cout << "Please input the number of player for this game" << endl;
            int num;
            while(true) {
                std::cin >> num;
                if (std::cin.fail()) break;
                if (num < 2 || num > 6) {
                    std::cout << "Please input the number between 2 - 6" << endl;
                } else {
                    break;
                }
            }
            std::cout << "The number of player is " << num << endl;
            std::vector<char> arr = {'G', 'B', 'D', 'P', 'S', '$', 'L', 'T'};
            int i = 0;
            while (i < num) {
                std::cout << "Player " << i + 1 << " enter your name: ";
                string name;
                std::cin >> name;
            
                while (name == "BANK" || name == "bank") {
                    std::cout << "This name is not valid, select a different one: ";
                    std::cin >> name;
                }
            
                char piece;
                while (true) {
                    std::cout << "Player " << i + 1 << " enter your symbol: ";
                    std::cout << "Please choose one from the available pieces: ";
                    
                    std::cout << "[ " ;
                    for (char ch : arr) {
                        std::cout << ch << " ";
                    }
                    std::cout << " ]" << std::endl;
            
                    std::cin >> piece;
                    auto it = std::find(arr.begin(), arr.end(), piece);
            
                    if (it != arr.end()) {
                        arr.erase(it);
                        pieceCharTaken.push_back(piece);
                        std::cout << "You just took " << piece << std::endl;
                        break;
                    } else {
                        std::cout << "Please select a piece from the available ones.\n";
                    }
                }
            
                auto p = std::make_shared<Player>(name, piece, 1500);
                group.push_back(p);
                b->addPlayer(piece);
                i++;
            }
        }
    
    } else {
        std::cout << "Please input the number of players for this game" << endl;
        int num;
        while (true) {
            std::cin >> num;
            if (std::cin.fail()) {
                std::cout << "That's not a number! Please try again: ";
                std::cin.clear();
                std::cin.ignore(10000, '\n');
            }
            else if (num < 2 || num > 6) {
                std::cout << "Please enter a number between 2-6: ";
            }
            else {
                break;  
            }
        }
        std::cout << "The number of players is " << num << endl;
        std::vector<char> arr = {'G', 'B', 'D', 'P', 'S', '$', 'L', 'T'};
        int i = 0;
        while (i < num) {
            std::cout << "Player " << i + 1 << " enter your name: ";
            string name;
            std::cin >> name;
        
            while (name == "BANK" || name == "bank") {
                std::cout << "This name is not valid, select a different one: ";
                std::cin >> name;
            }
        
            char piece;
            while (true) {
                std::cout << "Player " << i + 1 << " enter your symbol: ";
                std::cout << "Please choose one from the available pieces: ";
                
                std::cout << "[ ";
                for (char ch : arr) {
                    std::cout << ch << " ";
                }
                std::cout << std::endl;
                std::cout << "]";
        
                std::cin >> piece;
                auto it = std::find(arr.begin(), arr.end(), piece);
        
                if (it != arr.end()) {
                    arr.erase(it);
                    pieceCharTaken.push_back(piece);
                    std::cout << piece << " has been taken" << std::endl;
                    break;
                } else {
                    std::cout << "Please select a piece from the available ones.\n";
                }
            }
        
            auto p = std::make_shared<Player>(name, piece, 1500);
            group.push_back(p);
            b->addPlayer(piece);
            i++;
        }
    }

    std::cout << "++++++++++++  GAME START  ++++++++++++" << endl;

    int currIndex = 0;
    
    shared_ptr<Player> currActingPlayer = group[currIndex];
    int numberOfPlayer = group.size();
    auto dicee = make_shared<Dice>();
    bool hasRolled = false;
    string c;
    cout << "do you want light or dark mode (defaults to dark) ?" << endl;
    cin >> c;
    if (c == "light") {
        b->setBoardColor("light");
    } else {
        b->setBoardColor("dark");
    }
    b->drawBoard();

    while (true) {
        currActingPlayer = group[currIndex];

        numberOfPlayer = group.size();

        if (currActingPlayer->getisBankrupt()) {
            cout << currActingPlayer->getName() << "has declared bankruptcy" << endl;
            group.erase(group.begin() + currIndex);
            b->removePlayer(currActingPlayer->getSymbol());
            b->update();
            currIndex = (currIndex + 1) % group.size();
            hasRolled = false;
            continue;
        }
        numberOfPlayer = group.size();
        if (numberOfPlayer == 1) {
            std::cout << "Congratulation! The winner is " << currActingPlayer->getName();
            std::cout << " His Properties worth are: " << currActingPlayer->getAsset() << endl;
            break;
        }
        b->printBoard();
        std::cout << "Your turn " << currActingPlayer->getSymbol() <<" " << currActingPlayer->getName() <<  endl;
        std::cout << "Available commands - [ROLL, NEXT, TRADE, IMPROVE, MORTGAGE, UNMORTGAGE, BANKRUPT, ASSETS, ALL, SAVE]" << endl;
        std::cin >> command;

        if (command == "roll" || command == "ROLL") {
            if (hasRolled) {
                std::cout << "you have already rolled once, cant roll again" << endl;
                continue;
            }
            int rollValue = 0;
        
            // Handle jail turn first
            if (currActingPlayer->getisInTimsLine() || (currActingPlayer->getadd_roll_for_jail() == 0)) {
                std::cout << "Processing DC Tims Line turn..." << endl;
                TimsLine::handleTimsTurn(currActingPlayer, dicee, b);
                
                if (!currActingPlayer->getisInTimsLine()) {
                    // Player got out - move normally
                    CommandRoll(group, currActingPlayer, testMode, b);
                }
                
                hasRolled = false;
                currIndex = (currIndex + 1) % group.size();
                std::cout << "Moving to the next player!" << endl;
                std::cout << endl;
                continue;
            }
        
            // Normal roll handling
            while (currActingPlayer->getadd_roll_for_jail() != 0) {
                bool overload = false;
                std::string d1, d2;
                
                if (testMode) {
                    std::cout << "first die" << endl;
                    while (true) {
                        std::cin >> d1;
                        if (!d1.empty() && std::all_of(d1.begin(), d1.end(), ::isdigit)) break;
                        std::cout << "Invalid input. Please enter a number for first die: ";
                    }
                    
                    std::cout << "second die" << endl;
                    while (true) {
                        std::cin >> d2;
                        if (!d2.empty() && std::all_of(d2.begin(), d2.end(), ::isdigit)) break;
                        std::cout << "Invalid input. Please enter a number for second die: ";
                    }
                    
                    rollValue = std::stoi(d1) + std::stoi(d2);
                    overload = true;
                }
                
                if (!overload) {
                    dicee->roll();
                    std::cout << "Rolling your dice..." << endl
                              << dicee->getFirstDie() << " + "
                              << dicee->getSecondDie() << " = "
                              << dicee->getSum() << "!" << endl;
                }
        
                bool isDouble = overload ? (d1 == d2) : (dicee->getFirstDie() == dicee->getSecondDie());
                
                if (!isDouble) {
                    if (!overload) rollValue = dicee->getSum();
                    
                    currActingPlayer->movePlayer(rollValue);
                    b->drawBoard();
                    b->movePlayer(currActingPlayer->getSymbol(), currActingPlayer->getPosition());
                    b->update();
                    CommandRoll(group, currActingPlayer, testMode, b);
                    currActingPlayer->setRollForJail(3);
                    hasRolled = true;
                    break;
                }
                else {
                    if (!overload) rollValue = dicee->getSum();
                    
                    currActingPlayer->movePlayer(rollValue);
                    b->movePlayer(currActingPlayer->getSymbol(), currActingPlayer->getPosition());
                    b->update();
                    CommandRoll(group, currActingPlayer, testMode, b);
                    
                    currActingPlayer->add_roll_for_jail();
                    std::cout << "Double roll count: " << currActingPlayer->getadd_roll_for_jail() << endl;
                    
                    if (currActingPlayer->getadd_roll_for_jail() == 0) {
                        currActingPlayer->setIsInTimsLine(true);
                        currActingPlayer->moveToDCTims();
                        currActingPlayer->setPos(10);
                        b->movePlayer(currActingPlayer->getSymbol(), 10);
                        b->update();
                        std::cout << "Three doubles! Sent to DC Tims Line." << endl;
                        cout << R"(
                            ┌─┬─┬─┬─┬─┬─┐
                            │ │ │ │ │ │ │
                            │(╥_╥)│ │ │ │
                            │ │ │ │ │ │ │
                            └─┴─┴─┴─┴─┴─┘
                               "Let me out!"
                              )" << endl;
                        currIndex += 1;
                        currIndex = currIndex % group.size();
                        hasRolled = false;
                        break;
                    }
                    else {
                        std::cout << "you rolled doubles! you can roll again" << endl;
                    }
                }
            }
        } else if (command == "next" || command == "NEXT") {
            if (!hasRolled) {
                std::cout << "You must roll the dice before ending your turn!" << endl;
                continue;
            }
            if (!currActingPlayer->getisInTimsLine())  {
                currActingPlayer->setRollForJail(3);
            }
            currIndex += 1;
            currIndex = currIndex % group.size();
            std::cout << "turn finished, going to the next player!" << endl << endl;
            hasRolled = false;
        } else if (command == "trade" || command == "TRADE") {
            commandTrade(group, currActingPlayer);
        } else if (command == "improve" || command == "IMPROVE") {
            commandImprove(group, currActingPlayer, b);
        } else if (command == "mortgage" || command == "MORTGAGE") {
            commandMortgage(currActingPlayer);
        } else if (command == "unmortgage" || command == "UNMORTGAGE") {
            commandUnmortgage(currActingPlayer);
        } else if (command == "bankrupt" || command == "BANKRUPT") {
            std::cout << currActingPlayer->getSymbol() << " has declared bankruptcy!!!!" << endl;
            group.erase(group.begin() + currIndex);
            numberOfPlayer = group.size();
            currActingPlayer->setBankrupt(true);
            vector<shared_ptr<Building>> prop = currActingPlayer->getOwnedPropList();
            int size = prop.size();
            if (numberOfPlayer == 1) {
                std::cout << "Congratulations! The winner is " << group[0]->getName() << endl;
                std::cout << "Their properties: " << group[0]->getAsset() << endl;
                break;
            }
            for (int i = 0; i < size; i++){
                commandAuction(group, currActingPlayer, prop[i]->getName());
            }
            currIndex = currIndex % group.size();
            std::cout << "Moving to the next player!" << endl;
            b->removePlayer(currActingPlayer->getSymbol());
            b->update();
            hasRolled = false;
        } else if (command == "assets" || command == "ASSETS") {
            if (currActingPlayer->getPosition() != 4)
            {
                currActingPlayer->printAsset();
            }
            else
            {
                std::cout << "You can not check your assets if you are paying tuition " << endl;
            }
        } else if (command == "all" || command == "ALL") {
            if (currActingPlayer->getPosition() != 4)
            {   
                std::cout << "Displaying assets of every player in the game." << endl;
                for (unsigned int i = 0; i < group.size(); ++i)
                {
                    group[i]->printAsset();

                    std::cout << "========================================" << endl;
                }
            }
            else
            {
                std::cout << "You can not check your assets if you are paying tuition " << endl;

            }
        } else if (command == "save" || command == "SAVE") {
            std::cout << "saving the game. are you sure?(y/n)" << endl;
            char c;
            std::cin >> c;
            std::ofstream f;
            if(c == 'y') {
                std::cout << "enter the name of the file you want to save in" << endl;
                string file;
                std::cin >> file;
                file+=".txt";
                f.open(file);
                int size = group.size();
                f << size << endl;
                for (int i = 0; i < size; i++) {
                    f << group[i]->getName() << " ";
                    f << group[i]->getSymbol() << " ";
                    f << group[i]->getCups() << " ";
                    f << group[i]->getCash() << " ";
                    f << group[i]->getPosition() << " ";
                    if (group[i]->getPosition() == 10) {
                        f << group[i]->getisInTimsLine()<< " ";
                        if (group[i]->getisInTimsLine()) {
                            f << group[i]->getTurnsInTimsLine()<< " ";
                        }
                    }
                    if (group[i]->getPosition() == 4) {
		                f << " " << 0 << endl;
                    }
                    else {
                        f << endl;
                    }
                }
                for (int i = 0; i < 28; i++) {
                    f << OWNABLE[i][0] << " ";
                    int size = group.size();
                    bool owned = false;
                    for (int j = 0; j < size; j++)
                    {
                        if (group[j]->ownThisProp(OWNABLE[i][0]))
                        {
                            f << group[j]->getName() << " ";
                            owned = true;
                            break;
                        }
                    }

                    if (!owned)
                    {
                        f << "BANK" << " ";
                    }
                    f << b->getSquareImprovements(OWNABLE[i][0]) << endl;
                }
                return;
            } else {
                std::cout << "file not saved......" << endl;
            }
        } else {
            std::cout << "Command not found, Please check again" << endl;
        }
    }
}
