#include "Grid.h"

Grid::Grid(const std::size_t screen_width,
           const std::size_t screen_height,
           const std::size_t cell_width,
           const std::size_t cell_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      cell_width(cell_width),
      cell_height(cell_height)
{
    // Initialize the video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
	}
    
    // Create a window
    sdl_window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_CENTERED, 
                                  SDL_WINDOWPOS_CENTERED, screen_width, 
                                  screen_height, SDL_WINDOW_SHOWN);
    if (sdl_window == nullptr){
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
    }

    // Create render to draw to the window
    sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (sdl_renderer == nullptr){
        std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
    }
}

Grid::~Grid()
{
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Grid::createCells()
{
    bool isActive = false;
    for (int i=0; i<Grid::getNumberOfRows(); ++i)
    {
        std::vector<Cell> v;
        for (int j=0; j<Grid::getNumberOfColumns(); ++j)
            v.emplace_back(Cell(i*cell_width, j*cell_height, static_cast<int>(cell_width), static_cast<int>(cell_height), isActive));

        _cells.emplace_back(v);
    }
}

void Grid::drawCells()
{
    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, 1);
    SDL_RenderClear(sdl_renderer);

    
    for (auto row : _cells)
        for (auto cell : row)
            if (cell.isAlive()) {
                SDL_SetRenderDrawColor(sdl_renderer, 0, 0, 0, 1);
                SDL_RenderFillRect(sdl_renderer, cell.getRect());
            } else {
                SDL_SetRenderDrawColor(sdl_renderer, 238, 238, 238, 1);
                SDL_RenderDrawRect(sdl_renderer, cell.getRect());
            }

    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}

void Grid::makeCellAlive(int x, int y)
{
    std::cout << "Cell x: " << x << " y: " << y << std::endl;
    _cells[x/static_cast<int>(cell_width)][y/static_cast<int>(cell_height)].live();
}
