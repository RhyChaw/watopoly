#ifndef LOAD_H
#define LOAD_H

#include <string>
#include <vector>
#include <fstream>

struct PlayerInfo {
    char playerChar;
    int timsCups;
    int money;
    int position;
    bool inDC;
    int turnsInDC;
};

struct BuildingInfo {
    std::string name;
    std::string owner;
    int improvements;
};

struct GameState {
    std::vector<PlayerInfo> players;
    std::vector<BuildingInfo> buildings;
};

class Load {
public:
    // Load game state from file
    static GameState loadGame(const std::string& filename);
    
private:
    // Parse a player line from the save file
    static PlayerInfo parsePlayerLine(const std::string& line);
    
    // Parse a building line from the save file
    static BuildingInfo parseBuildingLine(const std::string& line);
};

#endif // LOAD_H
