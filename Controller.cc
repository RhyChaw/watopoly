#include "Controller.h"


Controller::Controller() {}

Controller::~Controller() {}
using namespace std;

void Controller::commandTrade(std::vector<std::shared_ptr<Player>> group, std::shared_ptr<Player> currActingPlayer) {
    char piece;
    
    int groupSize = group.size();  // Renamed variable to avoid redeclaration
    std::cout << "available players to trade with. ";
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
                p = group[i];  // Found the player with the matching symbol
                break;  // Exit the loop once the player is found
            }
            i++;  // Increment i to check the next player
        }
        
        if (i == groupSize) {
            std::cout << "Invalid player symbol" << std::endl;
        } else {
            break;  // Exit the outer loop when a valid player is found
        }
    }

    std::cout << "initiating trading with: " << p->getSymbol() << std::endl;

    // Get what user is offering
    std::cout << "Enter what you want to offer (money or property name): " << std::endl;
    for (const auto &prop : currActingPlayer->getOwnedPropList()) {
        std::cout << prop->getName() << " ";
    }
    string offerStr, wantStr;
    std::cout << std::endl;
    std::cin >> offerStr;
    
    // Get what user wants
    std::cout << "Enter what you want in return (money or property name): " << std::endl;
    for (const auto &prop : p->getOwnedPropList()) {
        std::cout << prop->getName() << " ";
    }


    std::cout << std::endl;
    std::cin >> wantStr;


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
    int cost;
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
        std::cout << "Do you want to (raise) or (withdraw)? ";
        std::cin >> action;
        if (action == "raise") {
            int bidAmount;
            std::cout << "Enter your bid amount: ";
            std::cin >> bidAmount;
            newAuction->place(currentBidder, bidAmount);
        } 
        else if (action == "withdraw") {
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
    std::cin >> prop;

    std::cout << "do you wanna BUY/SELL?" << endl;

    std::cin >> action;

    while (true) {
        if (action == "buy" || action == "sell" || std::cin.fail()) break;
        std::cout << "command not recognized" << endl;
        std::cout << "please select buy or sell" << endl;
        std::cin >> action;
    }
    shared_ptr<Building> p;
    p = Transactions::listProp(prop);
    if (action == "buy") {
        if (Transactions::buyImprovement(p, currActingPlayer)) {
            b->addImpr(p->getName());
            b->drawBoard();
        }
    }
    else if (action == "sell") {
        if(Transactions::sellImprovement(p, currActingPlayer)) {
            b->removeImpr(p->getName());
            b->drawBoard();
        }

    }
}

void Controller::commandMortgage(std::shared_ptr<Player> currActingPlayer) {
    std::cout << currActingPlayer->getSymbol() << "what do you want to mortgage" << endl;
            int size = currActingPlayer->getOwnedPropList().size();
            for (int i = 0; i < size; i++) {
                std::cout << currActingPlayer->getOwnedPropList()[i]->getName() << endl; 
            }
            string item;
            std::cin >> item;

            shared_ptr<Building> p;
            p = Transactions::listProp(item);
            Transactions::mortgage(p, currActingPlayer);
}

void Controller::commandUnmortgage(std::shared_ptr<Player> currActingPlayer) {
    std::cout << currActingPlayer->getSymbol() << "what do you want to unmortgage" << endl;
            int size = currActingPlayer->getOwnedPropList().size();
            for (int i = 0; i < size; i++) {
                std::cout << currActingPlayer->getOwnedPropList()[i]->getName() << endl; 
            }
            string item;
            std::cin >> item;
            shared_ptr<Building> p;
            p = Transactions::listProp(item);
            Transactions::unmortgage(p, currActingPlayer);
}

void Controller::commandBankrupt(std::shared_ptr<Player> currActingPlayer, std::shared_ptr<Player> owner) {
    currActingPlayer->setBankrupt(true);
    owner->changeCash(currActingPlayer->getCash());
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
        std::cout << "why trackingPiece is not in this player group? hmmm..." << endl;
        return result;
    };

    string sq = currActingPlayer->getSquareAtCurrPos();
    bool flag = false;
    int cost;

    for (int i = 0; i < 28; i++) {
        if (sq == OWNABLE[i][0])
        flag = true;
    }
    if (flag) { 
        if (Transactions::isOwned(sq)) { 
            shared_ptr<Building> prop = Transactions::listProp(sq);
            shared_ptr<Player> owner = pointerOfPlayer(prop->getOwner());
            
            for (int i = 0; i < 28; i ++) {
                if (prop->getName() == OWNABLE[i][0]) {
                cost = std::stoi(OWNABLE[i][2]);
                }
            }

            int rollValue = 0;

            if (owner == currActingPlayer) {
                std::cout << "you own this property, no need to pay rent" << endl;
            } else if (owner != currActingPlayer && !prop->getMortStatus()) {
                std::cout << "the property belongs to " << owner->getName();
                if (isGym(prop->getName())) {
                    std::cout << "landed on the gym, you have to roll to see what rent you will have to pay" << endl;
                    auto gym = std::dynamic_pointer_cast<Gym>(prop);
                    int roll = 0;
                    std::cout << "please type roll" << endl;
                    string command;
                    std::cin >> command;
                    while (command != "roll") {
                        std::cout << "Sorry, you have to roll first." << endl;
                        std::cin >> command;
                    }
                    bool overload = false;
                    if (testMode) {
                        std::cout << "first die" << endl;

                        std::string d1;
                        std::string d2;
                        std::cin >> d1;
                        std::cout << "second die" << endl;

                        std::cin >> d2;
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
                int rent;
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
                    cout<<rent <<"rent"<<endl;
                }
                // cout << prop->getGymLevel() << endl;
                // int rent = prop->amountToPay();
                // cout << "rent" << rent <<endl;
                while (!Transactions::payRent(currActingPlayer, owner, rent)) {
                    std::cout << "you must sell or trade something, or declare bankruptcy, you cant continue " << endl;
                    std::cout << "Avaliable commands - trade, mortgage, improve, bankrupt" << endl;
                    string command;
                    std::cin >> command;
                    if (command == "bankrupt" || command == "BANKRUPT") {
                        currActingPlayer->setBankrupt(true);
                        commandBankrupt(currActingPlayer, owner);
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
                    }
                }
                if (!currActingPlayer->getisBankrupt()){
                    std::cout << "rent paid successfully" << endl;
                }
            }
        }
        else { 
            std::cout << "this property is available to buy" << endl;
            std::cout << "type buy or auction to proceed accordingly" << endl;
            string input;
            while (true) {
                std::cin >> input;
                if (input == "buy" || input == "auction") {
                    break;
                } else {
                    std::cout <<"it has to be one of those commands - buy or auction" << endl;
                }
            }
            if (input == "buy"){
                if(currActingPlayer->getCash() < cost) {
                    while (true) {
                        std::cout << "you must auction, trade, mortgage, improve one of your properties, you cant afford it, you cant continue without choosing" << endl;
                        string cand;
                        std::cin >> cand;
                        if (cand == "auction" || cand == "AUCTION") {
                            commandAuction(group, currActingPlayer, sq);
                            break;
                        }
                        else if (cand == "trade" || cand == "TRADE")
                        {
                            commandTrade(group, currActingPlayer);
                            break;

                        }
                        else if (cand == "mortgage" || cand == "MORTGAGE")
                        {
                            commandMortgage(currActingPlayer);
                            break;

                        }
                        else if (cand == "improve" || cand == "IMPROVE")
                        {
                            commandImprove(group, currActingPlayer, b);
                            break;
                        }
                    }
                } else {
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
            SLC::moveeee(currActingPlayer);
            
            b->movePlayer(currActingPlayer->getSymbol(), currActingPlayer->getPosition());
            b->drawBoard();
            CommandRoll(group, currActingPlayer, testMode, b);
        } 
        else if (sq == "DC Tims Line"){
            std::cout << "you are at DC Tim Line" << endl;
        } 
        else if (sq == "GO TO TIMS") {
            std::cout << "Go to TIMS" << endl;
            currActingPlayer->moveToDCTims();	
            std::cout << currActingPlayer->getName() << " is being sent to DC Tims Line!" << endl;
            currActingPlayer->setPos(10);
            currActingPlayer->setIsInTimsLine(true);
            currActingPlayer->resetTurnsInTims();
            b->movePlayer(currActingPlayer->getSymbol(), 10);
            b->drawBoard();
        } else if (sq == "NEEDLES HALL") {
            std::cout << "You are at Needles Hall." << endl;
            NeedlesHall::moveeee(currActingPlayer);
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
        while (true) {
            std::cout<< "you must trade, mortgage, improve one of your properties, you cant continue without choosing" << endl;
            string cand;
            std::cin >> cand;
            if (cand == "trade" || cand == "TRADE")
            {
                commandTrade(group, currActingPlayer);
                break;

            }
            else if (cand == "mortgage" || cand == "MORTGAGE")
            {
                commandMortgage(currActingPlayer);
                break;

            }
            else if (cand == "improve" || cand == "IMPROVE")
            {
                commandImprove(group, currActingPlayer, b);
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
                        b->movePlayer(piece, 10);
                        int turn;
                        f >> turn;
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

            for (int i = 0; i < 28; i++) {  // Outer loop for properties
                string property_name;
                string owner;
                int imp;
                f >> property_name;
                f >> owner;
                f >> imp;

                if (owner != "BANK") {
                    int playerIndex = -1;
                    // Use a different loop variable (playerIndex) to find the player with the matching name
                    for (int j = 0; j < num; j++) {
                        if (group[j]->getName() == owner) {
                            playerIndex = j;
                            break;  // Found the player, no need to continue the loop
                        }
                    }

                    int propertyIndex = -1;
                    // Use a different loop variable (propertyIndex) to find the property
                    for (int k = 0; k < 40; k++) {
                        if (property_name == OWNABLE[k][0]) {
                            propertyIndex = k;
                            break;  // Found the property, no need to continue the loop
                        }
                    }

                    int buycost = 0;
                    // Look for the property in OWNABLE array to get the buy cost
                    for (int l = 0; l < 28; l++) {
                        if (OWNABLE[l][0] == property_name) {
                            std::stringstream ss(OWNABLE[l][2]);
                            ss >> buycost;
                            break;  // Found the buy cost, no need to continue the loop
                        }
                    }

                    char owner_symbol = group[playerIndex]->getSymbol();
                    std::shared_ptr<Building> build;
                    // Create the building object based on the property type
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

                    // Add the property to the player's assets and update the building status
                    group[playerIndex]->addProp(build);
                    Transactions::setowned(build);
                    if (imp == -1) {
                        build->setMortStatus(true);
                    } else {
                        build->setImprLevel(imp); 
                    }
                    b->addImpr(property_name, imp);
                }

                for (auto& player : group) {
                    int gymCount = 0;
                    // First count gyms
                    for (const auto& prop : player->getOwnedPropList()) {
                        if (isGym(prop->getName())) gymCount++;
                    }
                    // Then set the count for each gym
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
            int count = 0;
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
            char piece;
            while (i < num) {
                std::cout << "Player " << i + 1 << " enter your name: ";
                string name;
                std::cin >> name;
            
                while (name == "BANK" || name == "bank") {  // Use || instead of &&
                    std::cout << "This name is not valid, select a different one: ";
                    std::cin >> name;
                }
            
                char piece;
                while (true) {  // Keep asking for a symbol until a valid one is chosen
                    std::cout << "Player " << i + 1 << " enter your symbol: ";
                    std::cout << "Please choose one from the available pieces: ";
                    
                    for (char ch : arr) {
                        std::cout << ch << " ";
                    }
                    std::cout << std::endl;
            
                    std::cin >> piece;
                    auto it = std::find(arr.begin(), arr.end(), piece);
            
                    if (it != arr.end()) {
                        arr.erase(it);
                        pieceCharTaken.push_back(piece);
                        std::cout << piece << " has been taken" << std::endl;
                        break;  // Exit the loop since a valid symbol was chosen
                    } else {
                        std::cout << "Please select a piece from the available ones.\n";
                    }
                }
            
                auto p = std::make_shared<Player>(name, piece, 1500);
                group.push_back(p);
                b->addPlayer(piece);
                i++;  // Move to the next player
            }
        }
    
    } else {
        std::cout << "Please input the number of player for this game" << endl;
        int num;
        int count = 0;
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
        char piece;
        while (i < num) {
            std::cout << "Player " << i + 1 << " enter your name: ";
            string name;
            std::cin >> name;
        
            while (name == "BANK" || name == "bank") {  // Use || instead of &&
                std::cout << "This name is not valid, select a different one: ";
                std::cin >> name;
            }
        
            char piece;
            while (true) {  // Keep asking for a symbol until a valid one is chosen
                std::cout << "Player " << i + 1 << " enter your symbol: ";
                std::cout << "Please choose one from the available pieces: ";
                
                for (char ch : arr) {
                    std::cout << ch << " ";
                }
                std::cout << std::endl;
        
                std::cin >> piece;
                auto it = std::find(arr.begin(), arr.end(), piece);
        
                if (it != arr.end()) {
                    arr.erase(it);
                    pieceCharTaken.push_back(piece);
                    std::cout << piece << " has been taken" << std::endl;
                    break;  // Exit the loop since a valid symbol was chosen
                } else {
                    std::cout << "Please select a piece from the available ones.\n";
                }
            }
        
            auto p = std::make_shared<Player>(name, piece, 1500);
            group.push_back(p);
            b->addPlayer(piece);
            i++;  // Move to the next player
        }
    }

    std::cout << "++++++++++++  GAME START  ++++++++++++" << endl;
    int currIndex = 0;
    
    shared_ptr<Player> currActingPlayer = group[currIndex];
    int numberOfPlayer = group.size();
    auto dicee = make_shared<Dice>();
    bool hasRolled = false;
    b->drawBoard();

    while (true) {
        currActingPlayer = group[currIndex];
        if (currActingPlayer->getisBankrupt()) {
            currIndex = (currIndex + 1) % group.size();
            continue;
        }
        if (numberOfPlayer == 1) {
            std::cout << "Congratulation! The winner is " << currActingPlayer->getName();
            std::cout << " His Properties are " << currActingPlayer->getAsset() << endl;
            break;
        }
        std::cout << "Your turn " << currActingPlayer->getSymbol() << endl;
        std::cout << "Available commands - [ROLL, NEXT, TRADE, IMPROVE, MORTGAGE, UNMORTGAGE, BANKRUPT, ASSETS, ALL, SAVE]" << endl;
        std::cin >> command;

        if (command == "roll" || command == "ROLL") {
            if (hasRolled) {
                std::cout << "you have already rolled once, cant roll again"<< endl;
                continue;
            }
            int rollValue = 0;

            while (!currActingPlayer->getisInTimsLine() && (currActingPlayer->getadd_roll_for_jail() != 0)) {
                bool overload = false;
                std::string d1;
                std::string d2;
                if (testMode) {
                    std::cout << "first die" << endl;
                    
                    // Validate first die is a number
                    while (true) {
                        std::cin >> d1;
                        if (!d1.empty() && std::all_of(d1.begin(), d1.end(), ::isdigit)) {
                            break;
                        }
                        std::cout << "Invalid input. Please enter a number for first die: ";
                    }
                
                    std::cout << "second die" << endl;
                    
                    // Validate second die is a number
                    while (true) {
                        std::cin >> d2;
                        if (!d2.empty() && std::all_of(d2.begin(), d2.end(), ::isdigit)) {
                            break;
                        }
                        std::cout << "Invalid input. Please enter a number for second die: ";
                    }
                
                    rollValue = std::stoi(d1) + std::stoi(d2);
                    overload = true;
                }
                if (!overload) {
                    dicee->roll();
                    std::cout << "Rolling your dice..." << endl;
                    std::cout << dicee->getFirstDie() << " + ";
                    std::cout << dicee->getSecondDie() << " = ";
                    std::cout << dicee->getSum() << "!" << endl;
                }
                if ((dicee->getFirstDie() != dicee->getSecondDie()) || (d1 != d2)){
                    if (!overload) {
                        rollValue = dicee->getSum();
                    }
                    hasRolled = true;
                    currActingPlayer->movePlayer(rollValue);
                    b->drawBoard();
                    b->movePlayer(currActingPlayer->getSymbol(),
                    currActingPlayer->getPosition());
                    b->update();
                    CommandRoll(group, currActingPlayer, testMode, b);
                    break;
                } else {
                    if (!overload) {
                        rollValue = dicee->getSum();
                    }
                    hasRolled = true;
                    currActingPlayer->movePlayer(rollValue);
                    b->movePlayer(currActingPlayer->getSymbol(),
                    currActingPlayer->getPosition());
                    b->update();
                    CommandRoll(group, currActingPlayer, testMode, b);
                    std::cout << currActingPlayer->getadd_roll_for_jail() <<endl;
                    if (!currActingPlayer->getisInTimsLine()) {
                        std::cout << "you rolled doubles! you can roll again" << endl;
                        currActingPlayer->add_roll_for_jail();
                    }
                }
            }
            if (currActingPlayer->getadd_roll_for_jail() == 0) {
                currActingPlayer->setIsInTimsLine(true);
                std::cout << "you got double 3 times in a row, go to Tims Line" << endl;
                currActingPlayer->moveToDCTims();
                currActingPlayer->setPos(10);
                b->movePlayer(currActingPlayer->getSymbol(),currActingPlayer->getPosition());
                b->update();
                std::cout << currActingPlayer->getName() << ", you are in DC Tims Line (Turn " << currActingPlayer->getTurnsInTimsLine() << ")." << endl;
                TimsLine::handleTimsTurn(currActingPlayer, dicee);
                if (currActingPlayer->getisInTimsLine()) {  // there was a not before....
                    std::cout << "You are now free! Moving forward." << endl;
                } else {
                    std::cout << "You are still in DC Tims Line. Your turn is over." << endl;
                    currIndex = (currIndex + 1) % group.size();
                    hasRolled = false;
                    continue; 
                }
            }
        } else if (command == "next" || command == "NEXT") {
            if (!hasRolled) {
                std::cout << "You must roll the dice before ending your turn!" << endl;
                continue;
            }
            currActingPlayer->setRollForJail(3);
            currIndex += 1;
            currIndex = currIndex % group.size();
            std::cout << "turn finished, going to the next player!" << endl;
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
            numberOfPlayer--;
            currActingPlayer->setBankrupt(true);
            vector<shared_ptr<Building>> prop = currActingPlayer->getOwnedPropList();
            int size = prop.size();

            // char piece = owner->getSymbol();

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
        } else if (command == "assets" || command == "ASSETS") {
            if (currActingPlayer->getPosition() != 4)
            {
                currActingPlayer->printAsset();
            }
            else
            {
                std::cout << "You can not check your assets if you are paying tuition ";
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
                std::cout << "You can not check your assets if you are paying tuition ";

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
                f.open(file);
                int size = group.size();
                f << size << endl;
                for (int i = 0; i < size; i++) {
                    f << group[i]->getName() << " ";
                    f << group[i]->getSymbol() << " ";
                    f << group[i]->getCups() << " ";
                    f << group[i]->getCash() << " ";
                    f << group[i]->getPosition();
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
            } else {
                std::cout << "file not saved......" << endl;
            }
        } else {
            std::cout << "Command not found, Please check again" << endl;
        }
    }
}
