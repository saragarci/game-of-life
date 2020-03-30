#ifndef GRID_H
#define GRID_H

#include "Cell.h"

#include <SDL.h>
#include <vector>
#include <iostream>
#include <memory>

class Grid {
public:
    Grid(const std::size_t screen_width, const std::size_t screen_height,
         const std::size_t cell_width, const std::size_t cell_height);
    ~Grid();
    void createCells();
    void drawCells();
    std::vector<std::vector<Cell>> getCells() { return _cells; }
    int getNumberOfRows() { return static_cast<int>(screen_height/cell_height); }
    int getNumberOfColumns() { return static_cast<int>(screen_width/cell_width); }
    void setAlive(int x, int y);
    void updateCells();

private:
    int getAliveNeighbours(int i, int j, std::vector<std::vector<Cell>> cellsPresentState);
    int getNeighbour(int x, int y, std::vector<std::vector<Cell>> cellsPresentState);
    
    std::vector<std::vector<Cell>> createCellsCopy();

    std::vector<std::vector<Cell>> _cells;
    
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t cell_width;
    const std::size_t cell_height;
};

#endif
