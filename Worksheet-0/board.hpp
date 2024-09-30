#pragma once
#include "tile.hpp"
#include <map>
#include <string>

class Board {
    public:
        Board(bool turn = true);
        void outputBoard(std::map<std::string, Tile>& stdtiles);
        int takeTurn();
        bool getTurn();
        void flipTurnFlag();
    private:
        bool turnFlag;
};