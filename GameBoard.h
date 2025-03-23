// GameBoard.h
class GameBoard {
private:
    std::vector<std::vector<std::string>> boardCells;
    std::vector<Player*> players;
    int totalCups;
    bool gameWon;
    Player* winner;
    
    void initializeBoard();

public:
    GameBoard();
    ~GameBoard(); // Need a proper destructor to clean up pointers
    
    // Getters
    Player* getPlayer(int index) const;
    Cell* getCell(int index) const;
    int getTotalCups() const;
    Player* getWinner() const;
    bool isWon() const;
    
    // Game actions
    void roll(Player* player);
    void next();
    void trade(Player* p1, Player* p2, std::string give, std::string receive);
    void improve(Player* player, std::string property, bool buy);
    void mortgage(Player* player, std::string property);
    void unmortgage(Player* player, std::string property);
    void bankrupt(Player* player);
    void auction(Cell* property);
    void addCup();
    void removeCup();
    void checkWinCondition();
};