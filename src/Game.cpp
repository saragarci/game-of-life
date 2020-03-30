#include "Game.h"

Game::Game(Grid &grid, int x, int y) : _grid(grid), _initialX(x), _initialY(y) {
    _grid.makeCellAlive(_initialX, _initialY);
    _grid.drawCells();
}

void Game::startGame() {
    std::cout << "Starting Game!" << std::endl;
    
}
