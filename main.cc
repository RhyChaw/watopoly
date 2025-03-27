#include "Controller.h"
#include <iostream>

int main(int argc, char *argv[]) {
    Controller cont;
    cont->letTheGameBegin(int argc, char *argv);
}



if (argc > 1 && argv[1] == LOAD)
    {

        for (int i = 0; i < numPlayers; i++)
        {
            string name;
            char gamepiece;
            int numTimsCups;
            int funds;
            int sqrPos;

            inf >> name;
            inf >> gamepiece;
            inf >> numTimsCups;
            inf >> funds;
            inf >> sqrPos;

            auto p = std::make_shared<Player>(name, gamepiece, funds);
            p->setTimsCups(numTimsCups);
            b->addPlayer(gamepiece);

            if (sqrPos == DC_TIMS_POS)
            {
                bool inLine;
                inf >> inLine;
                if (inLine)
                {
                    b->movePlayer(gamepiece, DC_TIMS_POS);
                    int turnsInLine;
                    inf >> turnsInLine;
                    p->moveToDCTims();
                }
                else
                {
                    p->movePlayer(sqrPos); //but without collecting Go money
                    b->movePlayer(gamepiece, sqrPos);
                }
            }
            else
            {
                p->movePlayer(sqrPos); //but without collecting Go money
                b->movePlayer(gamepiece, sqrPos);
            }

            group.push_back(p);
        }

        for (int i = 0; i < OWNABLE_SIZE; i++)
        {
            string propName;
            string owner;
            int imprLevel;
            inf >> propName;
            inf >> owner;
            inf >> imprLevel;

            if (owner != "BANK")
            {
                int playerIndex = 0;
                for (int i = 0; i < numPlayers; i++)
                {
                    if (group[i]->getName() == owner)
                    {
                        playerIndex = i;
                    }
                }
                LoadSave::loadProperty(propName, group[playerIndex], imprLevel);
            }
        }

        for (int i = 0; i < numPlayers; i++)
        {
            group[i]->updateMonopolyBlock();
            group[i]->loadUpdateAmountToPay();
        }

        cout << "Here are the current assets of all players, and the state of the board.\n " << endl;
        for (int i = 0; i < numPlayers; i++)
        {
            group[i]->displayAssets();
            cout << "\n" << endl;
        }

        b->drawBoard();
    }