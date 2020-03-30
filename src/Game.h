#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "Controller.h"

#include <iostream>

class Game {
public:
    Game(Grid &grid, Controller &controller);
    void startGame();

private:
    Grid _grid;
    Controller _controller;
    int _initialX;
    int _initialY;
    bool _isInitialized;
    bool _running;
    bool _initializing;
};

#endif
