#pragma once

class Tile {
    public:
        Tile(int val = 0);
        int getState();
        bool setState(int state);
        char getStateChar();
    private:
        int state;
};