#include "Grid.h"
#include "Controller.h"
#include "Game.h"

#include <iostream>

int main(int, char**){
    constexpr std::size_t kScreenWidth{640};
    constexpr std::size_t kScreenHeight{640};
    constexpr std::size_t kCellWidth{20};
    constexpr std::size_t kCellHeight{20};

    Grid grid(kScreenWidth, kScreenHeight, kCellWidth, kCellHeight);
    grid.createCells();
    Game game(grid, 315, 315);
    game.startGame();
    Controller controller;
    controller.getUserInput();
	return 0;
}
