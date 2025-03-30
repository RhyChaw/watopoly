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

void SLC::moveeee(std::shared_ptr<Player> p, std::vector<std::shared_ptr<Player>> group) {
    srand(time(NULL));
	int c = 0;
	for (int i = 0; i < group.size(); i++) {
		c += group[i]->getCups();
		cout << c <<endl;
	}
	if (c <= 4) {
		std::cout << "Let's determine if you are the lucky winner to earn a TIMS CUP!!!" << endl;
		std::cout << "WHOAAAA EXCITING ISNT IT!" << endl;
		std::cout << " if you spin a 48 then you win! " << endl;
		int timsRoll = getRandomMovement(100);
		cout << "Your Tims Roll is " << timsRoll << "." << endl;
		if (timsRoll == 48) {
			cout << "Congratulations! You have won a TimsCup" << endl;
			p->addTimsCup();
			return;
		}
		cout << "SAD. You did not recieve it, sad really sad :(" << endl;
		cout << "Let's give you another chance, now we spin again..." << endl;
	} else {
		std::cout << "There are more than 4 cups present at the moment on the table" << endl;
		std::cout << "Cant roll for tims cups!!!!" << endl;
	}
	cout << "You have a 1 in 24 change for something to happen!" << endl;
    //list here what happens
    int  s = getRandomMovement(24);
    cout << "Your spin is " << s << "." << endl;
    int change = 0;
	if (s >= 1 && s <= 3) {	
		cout << "WHOOSH! You move back 3 spaces." << endl;
		change = -3;
	} else if (s >= 4 && s <= 7) {	
		cout << "WHOOSH! You move back 2 spaces." << endl;
		change = -2;
	} else if (s >= 8 && s <= 11) {
		cout << "WHOOSH! You move back 1 space." << endl;
		change = -1;
	} else if (s >= 12 && s <= 14) {
		cout << "WHOOSH! You move forward 1 space." << endl;
		change = 1;
	} else if (s >= 15 && s <= 18) {
		cout << "WHOOSH! You move forward 2 spaces." << endl;
		change = 2;
	} else if (s >= 19 && s <= 22) {
		cout << "WHOOSH! You move forward 3 spaces." << endl;
		change = 3;
    } else if (s == 23) {
		cout << "HAHA! Go to DC Tims Line." << endl;
		p->moveToDCTims();
    } else if (s == 24) {
		p->setPos(0);
		cout << "CONGRATULATIONS! You passed Collect OSAP! you get $200!" << endl;
		p->changeCash(200);
	} 
    int pos = p->getPosition();
	if (s != 24 && s != 23){
	    if (pos + change > 40){
	        p->changeCash(200);
		    cout << "CONGRATULATIONS! You passed Collect OSAP! Enjoy your $200!" << endl;
	    }
	    p->setPos((p->getPosition() + change)); 
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

