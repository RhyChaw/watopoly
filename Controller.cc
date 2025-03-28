#include "Controller.h"

Controller::Controller() {}

Controller::~Controller() {}

//handle when in these code segments the input is invalid.
void Controller::commandTrade(std::vector<std::shared_ptr<Player>> group, std::shared_ptr<Player> currActingPlayer) {
    auto newAuction = std::make_shared<Auction>(group, currActingPlayer, prop);

    cout << "========== PROPERTY AUCTION ==========" << endl;
    cout << "Auctioning: " << prop << endl;
    cout << "Starting auction process..." << endl;
    std::vector<bool> withdrawnPlayers(group.size(), false);
    int currentPlayerIndex = std::find(group.begin(), group.end(), curPlayer) - group.begin();
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
        
        cout << "Current bidder: " << currentBidder->getName() << endl;
        cout << "Current highest bid: $" << newAuction->maxBid << endl;
        string action;
        cout << "Do you want to (raise) or (withdraw)? ";
        cin >> action;
        if (action == "raise") {
            int bidAmount;
            cout << "Enter your bid amount: ";
            cin >> bidAmount;
            newAuction->place(currentBidder, bidAmount);
        } 
        else if (action == "withdraw") {
            withdrawnPlayers[currentBidderIndex] = true;
            newAuction->withdraw(currentBidder);
        } 
        else {
            cout << "Invalid action. Please choose 'raise' or 'withdraw'." << endl;
            continue;
        }
        currentBidderIndex = (currentBidderIndex + 1) % group.size();
    }

    int remainingBidders = 0;
    for (bool withdrawn : withdrawnPlayers) {
        if (!withdrawn) remainingBidders++;
    }
    if (remainingBidders == 1) {
        cout << "Auction completed successfully!" << endl;
    } else {
        cout << "Auction ended without a winner." << endl;
    }
}


void Controller::commandImprove(std::vector<std::shared_ptr<Player>> group, std::shared_ptr<Player> currActingPlayer, std::shared_ptr<GameBoard> b) {
    string prop, action;
            cout << currActingPlayer->getSymbol() << " please choose a property to improve" << endl;
            int size = currActingPlayer->getOwnedPropList().size();
            for (int i = 0; i < size; i++) {
                cout << currActingPlayer->getOwnedPropList()[i]->getName() << endl; 
            }
            cin >> prop;

            cout << "do you wanna BUY/SELL?" << endl;

            cin >> action;

            while (true) {
                if (action == "buy" || action == "sell" || cin.fail()) break;
                cout << "command not recognized" << endl;
                cout << "please select buy or sell" << endl;
                cin >> action;
            }
            shared_ptr<Building> p;
            p = Transactions::listProp(prop);
            if (action == "buy") {
                Transactions::buyImprovement(p, currActingPlayer);
                b->addImpr(p->getName());
                b->drawBoard();

            }
            else if (action == "sell") {
                Transactions::sellImprovement(p, currActingPlayer);
                b->removeImpr(p->getName());
                b->drawBoard();

            }
}

void Controller::commandMortgage(std::shared_ptr<Player> currActingPlayer) {
    cout << currActingPlayer->getSymbol() << "what do you want to mortgage" << endl;
            int size = currActingPlayer->getOwnedPropList().size();
            for (int i = 0; i < size; i++) {
                cout << currActingPlayer->getOwnedPropList()[i]->getName() << endl; 
            }
            string item;
            cin >> item;

            shared_ptr<Building> p;
            p = Transactions::listProp(property);
            Transactions::mortgage(p, currActingPlayer);
}

void Controller::commandUnmortgage(std::shared_ptr<Player> currActingPlayer) {
    cout << currActingPlayer->getSymbol() << "what do you want to unmortgage" << endl;
            int size = currActingPlayer->getOwnedPropList().size();
            for (int i = 0; i < size; i++) {
                cout << currActingPlayer->getOwnedPropList()[i]->getName() << endl; 
            }
            string item;
            cin >> item;
            shared_ptr<Building> p;
            p = Transactions::listProp(property);
            Transactions::unmortgage(p, currActingPlayer);
}

void Controller::commandBankrupt(std::shared_ptr<Player> currActingPlayer, std::shared_ptr<Player> owner) {
    currActingPlayer->setBankrupt(true);
    owner->changeCash(currActingPlayer->getCash());
    vector<shared_ptr<Building>> prop = currActingPlayer->getSymbol();
    int size = prop.size();
    char piece = owner->getGamePiece();
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
            if (group[i]->getGamePiece() == trackingPiece)
            {
                return group[i];
            }
        }
        cout << "why trackingPiece is not in this player group? hmmm..." << endl;
        // this will return empty share_ptr of player
        return result;
    };

    string sq = currActingPlayer->getSquareAtCurrPos();
    bool flag;
    for (int i = 0; i < 28; i++) {
        if (sq == OWNABLE[i][0])
        flag = true;
    }
    if (flag) { 
        if (Transactions::isOwned(sq)) { 
            shared_ptr<Building> prop = Transactions::pointerOfProp(sq);
            shared_ptr<Player> owner = pointerOfPlayer(prop->getOwner());
            int cost;
            for (int i = 0; i < 28; i ++) {
                if (prop->getName() == OWNABLE[i][0]) {
                cost = std::stoi(OWNABLE[i][2]);
                }
            }
            if (owner == currActingPlayer) {
                cout << "you own this property, no need to pay rent" << endl;
            } else if (owner != currActingPlayer && !prop->getMortStatus()) {
                cout << "the property belongs to " << owner->getName();
                if (isGym(prop->getName())) {
                    cout << "landed on the gym, you have to roll to see what rent you will have to pay" << endl;
                    auto gym = std::dynamic_pointer_cast<Gym>(propPointer);
                    int roll = 0;
                    cout << "please type roll" << endl;
                    string command;
                    cin >> command;
                    while (command != "roll") {
                        cout << "Sorry, you have to roll first." << endl;
                        cin >> command;
                    }
                    bool overload = false;
                    if (testMode) {
                        std::string d1;
                        std::string d1;
                        cin >> die1;
                        cin >> die2;
                        rollValue = std::stoi(die1) + std::stoi(die2);
                        overload = true;
                    }
                    if (!overload) {
                        auto twoDices = make_unique<Dice>();
                        dicee->rollDice();
                        cout << "Rolling your dice..." << endl;
                        cout << dicee->getDie1() << " + ";
                        cout << dicee->getDie2() << " = ";
                        cout << dicee->diceSum() << "!" << endl;
                        gym->setRoll(twoDices->diceSum());
                    }
                }
                while (!Transactions::payPlayer(currActingPlayer, prop, prop->amountToPay())) {
                    cout << "you must sell or trade something, or declare bankruptcy, you cant continue " << endl;
                    cout << "Avaliable commands - trade, mortgage, improve, bankrupt" << endl;
                    string command;
                    cin >> command;
                    if (command == "bankrupt" || command == "BANKRUPT") {
                        currActingPlayer->setBankruptStatus(true);
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
                    cout << "rent paid successfully" << endl;
                }
            }
        }
        else { 
            cout << "this property is available to buy" << endl;
            cout << "type buy or auction to proceed accordingly" << endl;
            string input;
            cin >> input;
            while (true) {
                if (input == "buy" || input == "auction") {
                    break;
                } else {
                    cout <<"it has to be one of those commands - buy or auction" << endl;
                }
            }
            if (input == "buy"){
                if(currActingPlayer->getCash < cost) {
                    while (true) {
                        cout << "you must auction, trade, mortgage, improve one of your properties, you cant afford it, you cant continue without choosing" << endl;
                        string cand;
                        cin >> cand;
                        if (command == "auction" || command == "AUCTION") {
                            commandAuction(group, currActingPlayer, sq);
                            break;
                        }
                        else if (command == "trade" || command == "TRADE")
                        {
                            commandTrade(group, currActingPlayer);
                            break;

                        }
                        else if (command == "mortgage" || command == "MORTGAGE")
                        {
                            commandMortgage(currActingPlayer);
                            break;

                        }
                        else if (command == "improve" || command == "IMPROVE")
                        {
                            commandImprove(group, currActingPlayer, b);
                            break;
                        }
                    }
                } else {
                    Transactions::buyBuilding(sq, currActingPlayer)
                }
            }
            else {
                commandAuction(group, currActingPlayer, sq);
            }
        }
    }
    else { 
        if (sq == "SLC"){
            cout << "You are at SLC" << endl;
            SLC::moveeee(currActingPlayer);
            b->move(currActingPlayer->getSymbol(), currActingPlayer->getPosition());
            b->drawBoard();
        } 
        else if (sq == "DC Tims Line"){
            cout << "you are at DC Tim Line" << endl;
        } 
        else if (sq == "GO TO TIMS") {
            cout << "Go to TIMS" << endl;
            currActingPlayer->moveToDCTims();	
            cout << curPlayer->getName() << " is being sent to DC Tims Line!" << endl;
            currActingPlayer->setPosition(10);
            currActingPlayer->setIsInTimsLine(true);
            currActingPlayer->resetTurnsInTims();
            b->move(currActingPlayer->getSymbol(), 10);
            b->drawBoard();
        } else if (sq == "NEEDLES HALL") {
            cout << "You are at Needles Hall." << endl;
            NeedlesHall::moveee(currActingPlayer);
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
        cout<< "your cash after the move is in negative now" << endl;
        while (true) {
            cout<< "you must trade, mortgage, improve one of your properties, you cant continue without choosing" << endl;
            string cand;
            cin >> cand;
            if (command == "trade" || command == "TRADE")
            {
                commandTrade(group, currActingPlayer);
                break;

            }
            else if (command == "mortgage" || command == "MORTGAGE")
            {
                commandMortgage(currActingPlayer);
                break;

            }
            else if (command == "improve" || command == "IMPROVE")
            {
                commandImprove(group, currActingPlayer, b);
                break;
            }
        }

    } 
}

void Controller::letTheGameBegin(int argc, char *argv) {
    cout << "*********************************" << endl;
    cout << "---     WATOPOLY PROJECT      ---" << endl;
    cout << "*********************************" << endl;
    vector<char> pieceCharTaken;
    string command, name, give, receive, property, action, filename;
    auto b = std::make_shared<GameBoard>();
    bool testMode = false;
    vector<shared_ptr<Player>> group;

    if (argc > 1) {
        if(argv[1] == "LOAD") {
            cout << "loading a saved game " << endl;
            std::ifstream f{argv[2]};

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
                        b->move(piece, 10);
                        int turn;
                        f >> turn;
                        p->moveToDCTims();
                    } else {
                        p->movePlayer(pos); 
                        b->move(piece, pos);
                    }
                } else {
                    p->movePlayer(sqr); 
                    b->move(piece, pos);
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
                    int index = 0;
                    for (int i = 0; i < num; i++) {
                        if (group[i]->getName() == owner) {
                            index = i;
                        }
                    }
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
                    char owner_symbol = group[i]->getSymbol();
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
                    group[i]->addProp(build);
                    if (imp == -1) {
                        build->setMortStatus(true);
                    } else {
                        build->setImprLevel(imp + 1); 
                    }
                    b->addImpr(property_name, imp);
                }
                for (int i = 0; i < num; i++) {}
                    group[i]->updateMonopolyBlock();
                    group[i]->loadUpdateAmountToPay();
                }
                cout << "Displaying assets of every player, so everyone is on track" << endl;
                for (int i = 0; i < num; i++) {
                    group[i]->getAsset();
                }
                b->drawBoard();
            }
        } else if (argv[1] == "TEST"){
            testMode = true;
            cout << "currently playing in test mode" << endl;
        } else {
            cout << "Please input the number of player for this game" << endl;
            int num;
            int count = 0;
            while(true) {
                cin >> num;
                if (cin.fail()) break;
                if (num < 2 || num > 6) {
                    cout << "Please input the number between 2 - 6" << endl;
                } else {
                    break;
                }
            }
            cout << "The number of player is " << num << endl;
            std::vector<char> arr = {'G', 'B', 'D', 'P', 'S', '$', 'L', 'T'};
            int i = 0;
            while (i <= num) {
                cout << "Player " << i + 1 << "enter your name";
                string name;
                cin >> name;
                while (name == "BANK" && name == "bank") {
                    cout << "this name is not valid, select a different one" << endl;
                    cin >> name;
                }
                cout << "Player " << i + 1 << "enter your symbol";
                cout << "Please choose one from the available piece char to represent yourself on board ";
                for (char ch : arr) {
                    std::cout << ch << " ";
                }
                char piece = ' ';
                cin >> piece;
                if (std::find(arr.begin(), arr.end(), piece) != arr.end()) {
                    arr.erase[piece];
                    count++;
                    pieceCharTaken[count] == piece;
                    cout << piece << " has been taken" << endl;
                    i++;
                } else {
                    cout << "please select a piece from the given pieces, that are available";
                    continue;
                }
                auto p = make_shared<Player>(name , piece, 1500);
                group.push_back(newPlayer);
                char piece = ' ';
            }
        } 
    } 
    cout << "++++++++++++  GAME START  ++++++++++++" << endl;
    int currIndex = 0;
    shared_ptr<Player> currActingPlayer = group[currIndex];
    int numberOfPlayer = group.size();
    auto dicee = make_shared<Dice>();
    auto b = std::make_shared<GameBoard>();
    bool hasRolled = false;
    while (true) {
        currActingPlayer = group[currIndex];
        if (currActingPlayer->getisBankrupt()) {
            currIndex = (currIndex + 1) % group.size();
            continue;
        }
        if (numberOfPlayer == 1) {
            cout << "Congratulation! The winner is " << currActingPlayer->getName();
            cout << " His Properties are " << currActingPlayer->getAssets() << endl;
            break;
        }
        if (currActingPlayer->getIsInTimsLine()) {
            cout << currActingPlayer->getName() << ", you are in DC Tims Line (Turn " << currActingPlayer->getTurnsInTims() + 1 << ")." << endl;
            TimsLine::handleTimsTurn(currActingPlayer, dicee);
            if (!currActingPlayer->getIsInTimsLine()) { 
                cout << "You are now free! Moving forward." << endl;
            } else {
                cout << "You are still in DC Tims Line. Your turn is over." << endl;
            }
            currIndex = (currIndex + 1) % group.size();
            continue;
        }
        cout << "Your turn " << currActingPlayer->getSymbol() << endl;
        cout << "Available commands - [ROLL, NEXT, TRADE, IMPROVE, MORTGAGE, UNMORTGAGE, BANKRUPT, ASSETS, ALL, SAVE]" << endl;
        cin >> command;
        if (command == "roll" || command == "ROLL") {
            if (hasRolled) {
                cout << "you have already rolled once, cant roll again"<< endl;
                continue;
            }
            int rollValue = 0;

            while (dicee->getDoubles > 0)
            {
                bool overload = false;
                if (testMode) {
                    std::string d1;
                    std::string d1;
                    cin >> die1;
                    cin >> die2;
                    rollValue = std::stoi(die1) + std::stoi(die2);
                    overload = true;
                }
                if (!overload) {
                    dicee->rollDice();
                    cout << "Rolling your dice..." << endl;
                    cout << dicee->getDie1() << " + ";
                    cout << dicee->getDie2() << " = ";
                    cout << dicee->diceSum() << "!" << endl;
                }
                if (!dicee->isDoubles()){
                    if (!overload) {
                        rollValue = dicee->diceSum();
                    }
                    hasRolled = true;
                    currActingPlayer->movePlayer(rollValue);
                    b->move(currActingPlayer->getSymbol(),
                                  currActingPlayer->getPosition());
                    b->drawBoard();
                    CommandRoll(group, currActingPlayer, testMode, b);
                    break;
                } else {
                    if (dicee->getDoubles == 0) {
                        cout << "you got double 3 times in a row, go to Tims Line" << endl;
                        currActingPlayer->moveToDCTims();
                        break;
                    }
                    if (!overload) {
                        rollValue = twoDices->diceSum();
                    }
                    currActingPlayer->movePlayer(rollValue);
                    b->move(currActingPlayer->getGamePiece(),
                                  currActingPlayer->getCurrPos());
                    b->drawBoard();
                    CommandRoll(group, currActingPlayer, testMode, b);
                    cout << "you rolled doubles! you can roll again" << endl;
                    dicee->changeDouble;
                }
            }
        } else if (command == "next" || command == "NEXT") {
            if (!hasRolled) {
                cout << "You must roll the dice before ending your turn!" << endl;
                continue;
            }
            currIndex += 1;
            currIndex = currIndex % group.size();
            cout << "turn finished, going to the next player!" << endl;
        } else if (command == "trade" || command == "TRADE") {
            commandTrade(group, currActingPlayer);
        } else if (command == "improve" || command == "IMPROVE") {
            commandImprove(group, currActingPlayer, b);
        } else if (command == "mortgage" || command == "MORTGAGE") {
            commandMortgage(currActingPlayer);
        } else if (command == "unmortgage" || command == "UNMORTGAGE") {
            commandUnmortgage(currActingPlayer);
        } else if (command == "bankrupt" || command == "BANKRUPT") {
            cout << currActingPlayer->getSymbol() << " has declared bankruptcy!!!!" << endl;
            group.erase(group.begin() + currIndex);
            numberOfPlayer--;
            currActingPlayer->setBankrupt(true);
            vector<shared_ptr<Building>> prop = currActingPlayer->getOwnedPropList();
            int size = prop.size();
            char piece = owner->getSymbol();
            if (numberOfPlayer == 1) {
                cout << "Congratulations! The winner is " << group[0]->getName() << endl;
                cout << "Their properties: " << group[0]->getAssets() << endl;
                break;
            }
            for (int i = 0; i < size; i++){
                commandAuction(group, currActingPlayer, prop->getName());
            }
            currIndex = currIndex % group.size();
            cout << "Moving to the next player!" << endl;
            b->removeplayer(currActingPlayer->getSymbol());
        } else if (command == "assets" || command == "ASSETS") {
            if (currActingPlayer->getPosition() != 4)
            {
                currActingPlayer->printAsset();
            }
            else
            {
                cout << "You can not check your assets if you are paying tuition ";
            }
        } else if (command == "all" || command == "ALL") {
            if (currActingPlayer->getPosition() != 4)
            {   
                cout << "Displaying assets of every player in the game." << endl;
                for (unsigned int i = 0; i < group.size(); ++i)
                {
                    group[i]->printAsset();
                    cout << "========================================" << endl;
                }
            }
            else
            {
                cout << "You can not check your assets if you are paying tuition ";

            }
        } else if (command == "save" || command == "SAVE") {
            cout << "saving the game. are you sure?(y/n)" << endl;
            char c;
            cin >> c;
            if(c == 'y') {
                cout << "enter the name of the file you want to save in" << endl;
                string file;
                cin >> file;
                std::ofstream f{file};
                int size = group.size();
                f << size << endl;
                for (int i = 0; i < size; i++) {
                    f << group[i]->getName() << " ";
                    f << group[i]->getSymbol() << " ";
                    f << group[i]->getCups() << " ";
                    f << group[i]->getCash() << " ";
                    f << group[i]->getPosition();
                    if (group[i]->getCurrPos() == 4) {
		                f << " " << 0 << endl;
                    }
                    else {
                        f << endl;
                    }
                }
            }
            for (int i = 0; i < 28; i++)
            {
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
                f << b->getImpr(OWNABLE[i][0]) << endl;
            }
        } else {
            cout << "Command not found, Please check again" << endl;
        }
    }
}
