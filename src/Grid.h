#ifndef GRID_H
#define GRID_H

#include "Cell.h"

#include <SDL.h>
#include <vector>
#include <iostream>

class Grid {
public:
    Grid(const std::size_t screen_width, const std::size_t screen_height,
         const std::size_t grid_width, const std::size_t grid_height);
    ~Grid();

private:
    void CreateCells();
    void DrawCells();

    std::vector<Cell> _cells;
    
    SDL_Window *sdl_window;
    SDL_Renderer *sdl_renderer;

    const std::size_t screen_width;
    const std::size_t screen_height;
    const std::size_t grid_width;
    const std::size_t grid_height;
};

#endif
