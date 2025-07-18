#pragma once
#include "tile.hpp"
#include <map>
#include <string>

class Board {
    public:
        Board(bool turn = true);
        void outputBoard(std::map<std::string, Tile>& tiles);
        int getPlayer();
        bool getTurn();
        void flipTurnFlag();
        int checkWin(std::map<std::string, Tile>& tiles);
    private:
        bool turnFlag;
        const std::string winConditions[8][3] = {
        {"A1", "A2", "A3"},
        {"B1", "B2", "B3"},
        {"C1", "C2", "C3"},
        {"A1", "B1", "C1"},
        {"A2", "B2", "C2"},
        {"A3", "B3", "C3"},
        {"A1", "B2", "C3"},
        {"C1", "B2", "A3"}
    };
};