#include "load.h"
#include <sstream>
#include <stdexcept>
#include <iostream>

using namespace std;

GameState Load::loadGame(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Could not open file: " + filename);
    }

    GameState state;
    string line;
    
    if (!getline(file, line)) {
        throw runtime_error("Save file is empty or missing player count.");
    }
    
    int numPlayers;
    try {
        numPlayers = stoi(line);
    } catch (exception& e) {
        throw invalid_argument("Invalid number of players.");
    }

    for (int i = 0; i < numPlayers; ++i) {
        if (!getline(file, line)) {
            throw runtime_error("Unexpected end of file while reading players.");
        }
        state.players.push_back(parsePlayerLine(line));
    }
    
    while (getline(file, line)) {
        state.buildings.push_back(parseBuildingLine(line));
    }

    validateGameState(state);

    return state;
}

PlayerInfo Load::parsePlayerLine(const string& line) {
    istringstream iss(line);
    vector<string> tokens;
    string token;
    
    while (iss >> token) {
        tokens.push_back(token);
    }
    
    if (tokens.size() < 5 || tokens[0] != "player") {
        throw invalid_argument("Invalid player line format: " + line);
    }
    
    PlayerInfo info;
    info.playerChar = tokens[1][0];
    info.timsCups = stoi(tokens[2]);
    info.money = stoi(tokens[3]);
    info.position = stoi(tokens[4]);
    info.inDC = false;
    info.turnsInDC = 0;
    
    if (info.position == 10 && tokens.size() == 7) {
        if (tokens[5] != "1") {
            throw invalid_argument("Invalid DC Tims Line flag: " + tokens[5]);
        }
        info.inDC = true;
        info.turnsInDC = stoi(tokens[6]);
        if (info.turnsInDC < 0 || info.turnsInDC > 2) {
            throw invalid_argument("Invalid turns in DC Tims Line: " + tokens[6]);
        }
    } else if (info.position == 10 && tokens.size() != 5) {
        throw invalid_argument("Malformed DC Tims Line player entry: " + line);
    }

    return info;
}

BuildingInfo Load::parseBuildingLine(const string& line) {
    istringstream iss(line);
    string name, owner;
    int improvements;

    if (!(iss >> name >> owner >> improvements)) {
        throw invalid_argument("Invalid building line format: " + line);
    }

    if (improvements < -1 || improvements > 5) {
        throw invalid_argument("Invalid improvement value for " + name + ": " + to_string(improvements));
    }

    return {name, owner, improvements};
}

void Load::validateGameState(const GameState& state) {
    int totalTimsCups = 0;
    for (const auto& player : state.players) {
        totalTimsCups += player.timsCups;
    }
    if (totalTimsCups > 4) {
        throw runtime_error("Invalid game state: Exceeded max Tims Cups.");
    }
}
