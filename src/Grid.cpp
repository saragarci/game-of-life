#include "Grid.h"

Grid::Grid(const std::size_t screen_width,
           const std::size_t screen_height,
           const std::size_t grid_width,
           const std::size_t grid_height)
    : screen_width(screen_width),
      screen_height(screen_height),
      grid_width(grid_width),
      grid_height(grid_height)
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

    CreateCells();
    DrawCells();
}

Grid::~Grid()
{
    SDL_DestroyRenderer(sdl_renderer);
    SDL_DestroyWindow(sdl_window);
    SDL_Quit();
}

void Grid::CreateCells()
{
    bool isActive = false;
    for(int i=0; i<screen_width; i+=grid_width)
    {
        for(int j=0; j<screen_height; j+=grid_height)
        {
            _cells.emplace_back(Cell(i, j, static_cast<int>(grid_width), static_cast<int>(grid_height), isActive));
        }
    }
}

void Grid::DrawCells()
{
    // Clear screen
    SDL_SetRenderDrawColor(sdl_renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(sdl_renderer);

    SDL_SetRenderDrawColor(sdl_renderer, 238, 238, 238, 1);
    for (auto cell : _cells)
        SDL_RenderDrawRect(sdl_renderer, cell.getRect());

    // Update Screen
    SDL_RenderPresent(sdl_renderer);
}
