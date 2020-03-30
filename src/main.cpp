#include "Grid.h"
#include "Controller.h"
#include "Game.h"

#include <iostream>

int main(int, char**){
    constexpr std::size_t kScreenWidth{800};
    constexpr std::size_t kScreenHeight{800};
    constexpr std::size_t kCellWidth{20};
    constexpr std::size_t kCellHeight{20};

    Grid grid(kScreenWidth, kScreenHeight, kCellWidth, kCellHeight);
    grid.createCells();
    Controller controller;
    Game game(grid, controller);
    game.startGame();
	return 0;
}
