#include "Controller.h"

Controller::Controller() {}

Controller::~Controller() {}

void Controller::loadGame(std::ifstream f) {
    int numPlayers;
    f >> numPlayers;
}

void Controller::letTheGameBegin(int argc, char *argv) {
    cout << "*********************************" << endl;
    cout << "---     WATOPOLY PROJECT      ---" << endl;
    cout << "*********************************" << endl;
    vector<char> pieceCharTaken;
    string command, name, give, receive, property, action, filename;
    auto b = std::make_shared<Board>();
    vector<shared_ptr<Player>> group;

    if (argc > 1) {
        if(argv[1] == "LOAD") {
            cout << "Loading a saved game " << endl;
            std::ifstream f{argv[2]};
            loadGame(f);
        } else if (){
            cout << "Please input the number of player for this game" << endl;
            int num;
            int count = 0;
            while(true) {
                cin >> num;
                if (cin.fail()) break;
                if (num < 2 && num > 6) {
                    cout << "Please input the number between 2 - 6" << endl;
                } else {
                    break;
                }
            }
            cout << "The number of player is " << num << endl;
            std::vector<char> arr = {'G', 'B', 'D', 'P', 'S', '$', 'L', 'T'};
            int i = 0;
            while (i <= num) {
                cout << "Player " << i + 1 << enter your symbol;
                cout << "Please choose one from the available piece char to represent yourself on board ";
                for (char ch : arr) {
                    std::cout << ch << " ";
                }
                char piece = ' ';
                cin >> piece;
                if (std::find(arr.begin(), arr.end(), piece) != arr.end()) {
                    arr.erase[pience];
                    count++;
                    pieceCharTaken[count] == piece;
                    cout << piece << " has been taken" << endl;
                    cout << "Player " << i + 1 << "! Your piece is " << piece << endl;
                    i++;
                } else {
                    cout << "please select a piece from the given pieces, that are available";
                    continue;
                }
                auto p = make_shared<Player>(" ", piece, 1500);
                group.push_back(newPlayer);
            }
        }
    } 
    cout << "++++++++++++  GAME START  ++++++++++++" << endl;
    int currIndex = 0;
    shared_ptr<Player> currActingPlayer = group[currIndex];
    int numberOfPlayer = group.size();
    auto dicee = make_shared<Dice>();
    auto b = std::make_shared<Board>();
    while (true) {
        currActingPlayer = group[currIndex];
        if (currActingPlayer->getisBankrupt()) {
            currIndex = currIndex % group.size();
            continue;
        }
        if (numberOfPlayer == 1) {
            cout << "Congratulation! The winner is " << currActingPlayer->getName();
            cout << " His Properties are " << currActingPlayer->getAssets() << endl;
            break;
        }
        cout << "Your turn " << currActingPlayer->getSymbol() << endl;
        cout << "Available commands - [ROLL, NEXT, TRADE, IMPROVE, MORTGAGE, UNMORTGAGE, BANKRUPT, ASSETS, ALL, SAVE]" << endl;
        cin >> command;
        if (command == "roll" || command == "ROLL") {
            int rollValue = 0;

            while (dicee->getDoubles > 0)
            {
                bool rollOverload = false;
                if (!rollOverload)
                {
                    dicee->rollDice();
                    cout << "Rolling your dice..." << endl;
                    cout << dicee->getDie1() << " + ";
                    cout << dicee->getDie2() << " = ";
                    cout << dicee->diceSum() << "!" << endl;
                }
                if (!dicee->isDoubles())
                {
                    if (!rollOverload)
                    {
                        rollValue = dicee->diceSum();
                    }
                    currActingPlayer->movePlayer(rollValue);
                    b->movePlayer(currActingPlayer->getSymbol(),
                                  currActingPlayer->getPosition());
                    b->drawBoard();
                    commandRoll(group, currActingPlayer, b);
                    break;
                }
                else
                {
                    if (dicee->getDoubles == 1)
                    {
                        cout << "you got double 3 times in a row, go to Tims Line" << endl;
                        currActingPlayer->moveToDCTims();
                        continue;
                    }
                    if (!rollOverload)
                    {
                        rollValue = twoDices->diceSum();
                    }
                    currActingPlayer->movePlayer(rollValue);
                    b->movePlayer(currActingPlayer->getGamePiece(),
                                  currActingPlayer->getCurrPos());
                    b->drawBoard();
                    commandRoll(group, currActingPlayer, b);
                    cout << "you rolled doubles! you can roll again" << endl;
                    dicee->changeDouble;
                }
            }
        } else if (command == "next" || command == "NEXT") {
            currIndex += 1;
            currIndex = currIndex % group.size();
            cout << "turn finished, going to the next player!" << endl;
        } else if (command == "trade" || command == "TRADE") {
            commandTrade(group, currActingPlayer);
        } else if (command == "improve" || command == "IMPROVE") {
            commandImprove(group, currActingPlayer, b);
        } else if (command == "mortgage" || command == "MORTGAGE") {
            commadMortgage(currActingPlayer);
        } else if (command == "unmortgage" || command == "UNMORTGAGE") {
            commadUnmortgage(currActingPlayer);
        } else if (command == "bankrupt" || command == "BANKRUPT") {
            cout << currActingPlayer->getSymbol() << " has declared bankruptcy!!!!" << endl;
            group.erase(group.begin() + currIndex);
            numberOfPlayer--;
            if (numberOfPlayer == 1) {
                cout << "Congratulations! The winner is " << group[0]->getName() << endl;
                cout << "Their properties: " << group[0]->getAssets() << endl;
                break;
            }
            currIndex = currIndex % group.size();
            cout << "Moving to the next player!" << endl;
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
                f << b->getImprLevel(OWNABLE[i][0]) << endl;
            }
        } else {
            cout << "Commad not found, Please check again" << endl;
        }
    }
}
