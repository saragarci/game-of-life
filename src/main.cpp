#include "Grid.h"
#include "Controller.h"

#include <iostream>

int main(int, char**){
    constexpr std::size_t kScreenWidth{640};
    constexpr std::size_t kScreenHeight{640};
    constexpr std::size_t kGridWidth{32};
    constexpr std::size_t kGridHeight{32};

    Grid grid(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
    Controller controller;
    controller.getUserInput();

	return 0;
}
