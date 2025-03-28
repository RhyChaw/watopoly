#include "NeedlesHall.h"
#include "Player.h"
#include <iostream>
using namespace std;

NeedlesHall::NeedlesHall(int ID, std::string name) : nonbuilding(ID, name) {}

NeedlesHall::~NeedlesHall() {}

int NeedlesHall::getRandomMovement(int n) {
    int spin = rand() % n + 1;
    return spin;
}

void NeedlesHall::moveeee(std::shared_ptr<Player> p) {
    srand(time(NULL));
    std::cout << "we will determine first if you are the lucky winner to earn a TIMS CUP " << endl;
    std::cout << "WHOAAAA EXCITING" << endl;
    std::cout << " if you spin a "<< "48 " << "then you win" << endl;
    int timsRoll = getRandomMovement(100);
    cout << "Your Tims Roll is " << timsRoll << "." << endl;
    if (timsRoll == 48) {
		cout << "Congratulations! You have won a TimsCup" << endl;
		p->addTimsCup();
		return;
	}
	cout << "you did not recive, sad really sad" << endl;
	cout << "now we spin again" << endl;
	cout << "you have a 1 in 18 change for something to happen" << endl;
    //list here what happens
    int  s = getRandomMovement(18);
    cout << "Your spin is " << s << "." << endl;
    if (s == 1) {
		cout << "You lose $200!" << endl;
		p->changeCash(-200);
	} else if (s >= 2 && s <= 3) {
		cout << "You lose $100!" << endl;
        p->changeCash(-100);

	} else if (s >= 4 && s <= 6) {
		cout << "You lose $50!" << endl;
        p->changeCash(-50);

	} else if (s >= 7 && s <= 12) {
		cout << "You win $25!" << endl;
        p->changeCash(25);

	} else if (s >= 13 && s <= 15) {
		cout << "You win $50!" << endl;
		p->changeCash(-50);
	} else if (s >= 16 && s <= 17) {
		cout << "You win $100!" << endl;
	    p->changeCash(-100);
	} else if (s == 18) {
		cout << "Your win $200!" << endl;
		p->changeCash(200);
	} 
}

// void NeedlesHall::idkkkk(Player* player) {
//     int moneyChange = getRandomOutcome();
    
//     std::cout << player->getName() << " landed on Needles Hall and drew a card." << std::endl;
    
//     if (moneyChange > 0) {
//         std::cout << player->getName() << " receives " << moneyChange << " dollars." << std::endl;
//         player->addMoney(moneyChange);
//     } else if (moneyChange < 0) {
//         std::cout << player->getName() << " pays " << -moneyChange << " dollars." << std::endl;
//         player->removeMoney(-moneyChange); // Convert negative to positive for removeMoney
//     } else {
//         std::cout << "No change in funds." << std::endl;
//     }
// }

