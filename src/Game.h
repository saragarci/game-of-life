#ifndef GAME_H
#define GAME_H

#include "Grid.h"

#include <iostream>

class Game {
public:
    Game(Grid &grid, int x, int y);
    void startGame();

private:
    Grid _grid;
    int _initialX;
    int _initialY;
};

#endif
