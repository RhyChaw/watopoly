#include "SLC.h"
#include "Player.h"
#include <iostream>
using namespace std;

SLC::SLC(int ID, std::string name) : nonbuilding(ID, name) {}

SLC::~SLC() {}

int SLC::getRandomMovement(int n) {
    int spin = rand() % n + 1;
    return spin;
}

void SLC::moveeee(std::shared_ptr<Player> p) {
    srand(time(NULL));
    std::cout << "we will determine first if you are the lucky winner to earn a TIMS CUP " << endl;
    std::cout << "WHOAAAA EXCITING" << endl;
    std::cout << " if you spin a "<< "48" << "then you win" << endl;
    int timsRoll = getRandomMovement(100);
    cout << "Your Tims Roll is " << timsRoll << "." << endl;
    if (timsRoll == 48) {
		cout << "Congratulations! You have won a TimsCup" << endl;
		p->addCup();
		return;
	}
	cout << "you did not recive, sad really sad" << endl;
	cout << "now we spin again" << endl;
	cout << "you have a 1 in 24 change for something to happen" << endl;
    //list here what happens
    int  s = getRandomMovement(24);
    cout << "Your spin is " << s << "." << endl;
    int change = 0;
	if (s >= 1 && s <= 3) {	
		cout << "You move back 3 spaces." << endl;
		change = -3;
	} else if (s >= 4 && s <= 7) {	
		cout << "You move back 2 spaces." << endl;
		change = -2;
	} else if (s >= 8 && s <= 11) {
		cout << "You move back 1 space." << endl;
		change = -1;
	} else if (s >= 12 && s <= 14) {
		cout << "You move forward 1 space." << endl;
		change = 1;
	} else if (s >= 15 && s <= 18) {
		cout << "You move forward 2 spaces." << endl;
		change = 2;
	} else if (s >= 19 && s <= 22) {
		cout << "You move forward 3 spaces." << endl;
		change = 3;
    } else if (s == 23) {
		cout << "Go to DC Tims Line." << endl;
		p->moveToTimsLine();
    } else if (s == 24) {
		p->setPosition(0);
		cout << "You passed Collect OSAP! you get $200!" << endl;
		p->changeCash(200);
	} 
    int pos = p->getPosition();
	if (s != 24 && s != 23){
	    if (pos + change > 40){
	        p->changeCash(200);
		    cout << "You passed Collect OSAP! Enjoy your $200!" << endl;
	    }
	    p->setPosition((p->getPosition() + change)); 
	}
	return;
}

    // int movement = getRandomMovement();
    // std::cout << player->getName() << " landed on SLC and drew a card." << std::endl;
    
    // if (movement == 10) {
    //     // Special case: Advance to OSAP
    //     std::cout << player->getName() << " advances to OSAP." << std::endl;
    //     player->setIndex(0); // OSAP is at position 0
    //     // The GameBoard should handle calling doEvent on the new cell
    // } else {
    //     // Regular movement
    //     int newPos = (player->getIndex() + movement) % 40;
    //     if (newPos < 0) newPos += 40; // Handle negative positions
        
    //     std::cout << player->getName() << " moves " 
    //               << (movement > 0 ? "forward " : "backward ")
    //               << abs(movement) << " spaces." << std::endl;
        
    //     player->setIndex(newPos);
    //     // The GameBoard should handle calling doEvent on the new cell
    // }

