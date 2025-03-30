#include "TimsLine.h"
#include "Player.h"
#include <iostream>
using namespace std;

TimsLine::TimsLine(int ID, std::string name) : nonbuilding(ID, name) {}

TimsLine::~TimsLine() {}

void TimsLine::sendToJail(std::shared_ptr<Player> p) {
    p->setIsInTimsLine(true);
    p->resetTurnsInTims();
    cout << p->getName() << " has been sent to DC Tims Line!" << endl;

    cout << R"(
        ┌─┬─┬─┬─┬─┬─┐
        │ │ │ │ │ │ │
        │(╥_╥)│ │ │ │
        │ │ │ │ │ │ │
        └─┴─┴─┴─┴─┴─┘
           "Let me out!"
          )" << endl;
}

void TimsLine::handleTimsTurn(std::shared_ptr<Player> p, std::shared_ptr<Dice> dice, std::shared_ptr<GameBoard> b) {
    if (!p->getisInTimsLine()) return; 

    cout << "You will roll again. You must roll doubles to escape!"<< endl;
    dice->roll();
    int roll1 = dice->getFirstDie();
    int roll2 = dice->getSecondDie();
    int rollSum = roll1 + roll2;

    cout << "You rolled: " << roll1 << " + " << roll2 << " = " << rollSum << endl;

    if (roll1 == roll2) { 
        cout << "You rolled doubles! You are free to move " << rollSum << " spaces." << endl;
        p->setIsInTimsLine(false);
        p->resetTurnsInTims();
        p->setRollForJail(3);
        p->movePlayer(rollSum);
        b->movePlayer(p->getSymbol(), p->getPosition());
        return;
    }

    p->changeTurnsInTimsLine();

    if (p->getTurnsInTimsLine() == 0) { 
        cout << "This is your third turn. You must leave DC Tims Line." << endl;
        cout << "You have to pay 50 now!" << endl;
        p->changeCash(-50);
        return;
    }
    cout << "You did not roll doubles. You may:" << endl;
    cout << "1. Pay $50 to leave." << endl;
    cout << "2. Use a Roll Up the Rim cup (if available)." << endl;
    cout << "3. Stay in jail (try again next turn)." << endl;

    int choice;
    while (true) {
        cout << "Enter your choice [ 1 / 2 / 3 ]: ";
        cin >> choice;
        
        if (cin.fail() || (choice < 1 || choice > 3)) {
            cout << "Invalid choice. Please enter '1', '2', or '3'." << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            break;
        }
    }

    if (choice == 1) { 
        if (p->getCash() >= 50) {
            p->changeCash(-50);
            cout << "You paid $50 and are free to move!" << endl;
            p->setIsInTimsLine(false);
            p->resetTurnsInTims();
            p->setRollForJail(3);

        } else {
            cout << "You don't have enough money to pay. You must stay in jail. try to sell something in your next turn..." << endl;
        }
    } else if (choice == 2) { 
        if (p->getCups() > 0) {
            p->useCups();
            cout << "You used a Roll Up the Rim cup and are free to move!" << endl;
            p->setIsInTimsLine(false);
            p->resetTurnsInTims();
            p->setRollForJail(3);
        } else {
            cout << "You have no Tim cups. You must stay in jail :(" << endl;
        }
    } else { // Stay in jail
        cout << "You chose to stay in jail. Try again next turn..." << endl;
    }

}



int TimsLine::turns(std::shared_ptr<Player> p) {
    return p->getadd_roll_for_jail();
}

bool TimsLine::jail(std::shared_ptr<Player> p) {
    return p->getisInTimsLine();
}

void TimsLine::add(std::shared_ptr<Player> p){
    p->add_roll_for_jail();
}

