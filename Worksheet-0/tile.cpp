#include "tile.hpp"

Tile::Tile(int val){
    state = val;
} 

int Tile::getState(){
    return state;
}

void Tile::setState(int val){
    state = val;
}

char Tile::getStateStr(){
    switch(state){
        case 0:
            return ' ';
            break;
        case 1:
            return 'X';
            break;
        case 2:
            return 'O';
            break;
        default:
            return ' ';
            break;
    }
}