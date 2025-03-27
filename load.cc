#include "load.h"
#include <sstream>
#include <stdexcept>

using namespace std;

GameState Load::loadGame(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }

    GameState state;
    string line;
    
    // Read number of players
    getline(file, line);
    int numPlayers = stoi(line);
    
    // Read player data
    for (int i = 0; i < numPlayers; ++i) {
        getline(file, line);
        state.players.push_back(parsePlayerLine(line));
    }
    
    // Read building data
    while (getline(file, line)) {
        state.buildings.push_back(parseBuildingLine(line));
    }
    
    return state;
}

PlayerInfo Load::parsePlayerLine(const string& line) {
    istringstream iss(line);
    string token;
    vector<string> tokens;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    if (tokens.size() < 5 || tokens[0] != "player") {
        throw invalid_argument("Invalid player line format");
    }
    
    PlayerInfo info;
    info.playerChar = tokens[1][0];
    info.timsCups = stoi(tokens[2]);
    info.money = stoi(tokens[3]);
    info.position = stoi(tokens[4]);
    info.inDC = false;
    info.turnsInDC = 0;
    
    // Handle DC Tims Line cases
    if (info.position == 10) {
        if (tokens.size() >= 6 && tokens[5] == "1") {
            info.inDC = true;
            info.turnsInDC = stoi(tokens[6]);
        }
    }
    
    return info;
}

BuildingInfo Load::parseBuildingLine(const string& line) {
    istringstream iss(line);
    string name, owner;
    int improvements;
    
    iss >> name >> owner >> improvements;
    
    // Validate improvements
    if (improvements < -1 || improvements > 5) {
        throw invalid_argument("Invalid improvement value for " + name);
    }
    
    return {name, owner, improvements};
}
