#include "Game.h"

Game::Game(Grid &grid, Controller &controller) : _grid(grid), _controller(controller), _isInitialized(false), _running(true), _initializing(true) {
    _grid.drawCells();
    while (_initializing) {
        _controller.getUserInput(_initializing, _isInitialized, _initialX, _initialY);
        _grid.setFirstAlive(_initialX, _initialY, _initializing);
        _grid.drawCells();
    }
}

void Game::startGame() {
    std::cout << "Starting Game!" << std::endl;

    while (_running) {
        SDL_Delay(1000);
        _controller.getUserInput(_running, _isInitialized, _initialX, _initialY);
        _grid.setAlive(639, 639);
        _grid.drawCells();
    }
}
