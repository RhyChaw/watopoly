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
    static GameState loadGame(const std::string& filename);

private:
    static PlayerInfo parsePlayerLine(const std::string& line);
    static BuildingInfo parseBuildingLine(const std::string& line);
    static void validateGameState(const GameState& state);
};

#endif // LOAD_H
