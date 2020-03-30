#include "Game.h"

Game::Game(Grid &grid, Controller &controller) : _grid(grid), _controller(controller), _isInitialized(false), _running(true) {
    _grid.drawCells();
    while (!_isInitialized) {
        _controller.getUserInput(_running, _isInitialized, _initialX, _initialY);
        _grid.setAlive(_initialX, _initialY);
        _grid.drawCells();
    }
}

void Game::startGame() {
    std::cout << "Starting Game!" << std::endl;

    int count = 0;
    while (_running) {
        std::cout << "Iteration: " << count << std::endl;
        //SDL_Delay(5000);
        _controller.getUserInput(_running, _isInitialized, _initialX, _initialY);
        _grid.updateCells();
        _grid.drawCells();
        ++count;
    }
}
